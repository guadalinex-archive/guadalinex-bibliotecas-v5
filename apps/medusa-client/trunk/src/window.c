/***************************************************************************
 *   Copyright (C) 2004 by Junta de Andalucía and Christian Töpp           *
 *   medusa@juntadeandalucia.es                                            *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <utmp.h>
#include <X11/Xlib.h>
#include <X11/xpm.h>
#include <signal.h>
#include <sys/types.h>

#include "log.h"
#include "window.h"

/* Static variables used */
static Window root, wnd, logo, logo2;
static int x, y, dW, dH;
static char background_filename[MAX_FILENAME_LENGTH];
static char foreground_filename[MAX_FILENAME_LENGTH];
static char logo_filename[MAX_FILENAME_LENGTH];
static Display *dsp;
static Window wnd1;

/* Blocked or not */
static int blocked = 0;

void set_background(char *local_background_filename)
{
	strncpy(background_filename, local_background_filename,
					MAX_FILENAME_LENGTH);
}

void set_foreground(char *local_foreground_filename)
{
	strncpy(foreground_filename, local_foreground_filename,
					MAX_FILENAME_LENGTH);
}

void set_logo(char *local_logo_filename)
{
	strncpy(logo_filename, local_logo_filename,
					MAX_FILENAME_LENGTH);
}

int is_blocked(void)
{
	return blocked;
}

int set_blocked(int yes)
{
	if (yes)
		blocked = 1;
	else
		blocked = 0;

	return yes;
}

int lockScreen(void)
{
	XSetWindowAttributes attr, attr1, attr2;
	Pixmap shape, pic, lock, shp, bg_pic, bg_shp;
	int screen_number = 0;
	long win_mask = CWBackPixel | CWBorderPixel | CWOverrideRedirect;

	if (is_blocked())
		return 0;


	set_blocked(1);

	x = 5;
	y = 35;
	(dsp) = XOpenDisplay(":0.0");

	if ((dsp) == NULL) {
		write_log("Could not open Display 0:0\n");
		return (-1);
	}
	dW = XDisplayWidth(dsp, screen_number);
	dH = XDisplayHeight(dsp, screen_number);
	root = XRootWindow(dsp, screen_number);

	/* If a extern XPM background file specified on the command line */
	if (background_filename != NULL) {
		if (XpmReadFileToPixmap
				(dsp, root, background_filename, &bg_pic, &bg_shp,
				 NULL) != XpmOpenFailed)
			win_mask = CWBackPixmap | CWBorderPixel | CWOverrideRedirect;
	}

	attr.background_pixel = 700;
	attr.background_pixmap = bg_pic;
	attr.border_pixel = 100;
	attr.override_redirect = True;

	(wnd1) = XCreateWindow(dsp, root, 0, 0, dW, dH, 0, CopyFromParent, 
			       CopyFromParent, CopyFromParent, win_mask, &attr);
	XMapRaised(dsp, wnd1);

	if (logo_filename != NULL) {
		XpmReadFileToPixmap(dsp, root, logo_filename, &pic, &shape, NULL);
	}

	attr1.background_pixmap = pic;
	logo = XCreateWindow(dsp, wnd1, dW - 150, 0, 150, 30, 0, 
			CopyFromParent, CopyFromParent,
			CopyFromParent, CWBackPixmap, &attr1);
	XMapWindow(dsp, logo);
	logo2 = XCreateSimpleWindow(dsp, wnd1, 0, 0, dW - 150, 30, 0, 0, 300);
	XMapWindow(dsp, logo2);

	if (foreground_filename != NULL) {
		XpmReadFileToPixmap(dsp, root, foreground_filename, &lock, &shp, NULL);
	}

	attr2.background_pixmap = lock;
	wnd = XCreateWindow(dsp, wnd1, dW / 2 - 150, dH / 2 - 100, 300, 200, 0,
			CopyFromParent, CopyFromParent,
			CopyFromParent, CWBackPixmap, &attr2);
	//wnd = XCreateSimpleWindow(dsp, wnd1, x, y, 200, 200, 1, 0, 400);
	XMapWindow(dsp, wnd);

	XGrabPointer(dsp, wnd1, False,
			ButtonPressMask | ButtonReleaseMask |
			PointerMotionMask, GrabModeAsync, GrabModeAsync, None,
			None, CurrentTime);
	XGrabKeyboard(dsp, wnd1, False, GrabModeAsync, 
			GrabModeAsync, CurrentTime);
	XSelectInput(dsp, wnd1, KeyPressMask | KeyReleaseMask | 
			ButtonPressMask | ButtonReleaseMask | 
			PointerMotionMask | ShiftMask |
			LockMask | ControlMask | Mod1Mask 
			| Mod2Mask | Mod3Mask | Mod4Mask | Mod5Mask);

	write_log_fmt("locking screen\n");

	return (0);
}

int unlockScreen(void)
{
	if (dsp == NULL)
		return -1;
	if (is_blocked()) {
		write_log_fmt("Unlocking Screen\n");
		XDestroyWindow(dsp, wnd1);
		XCloseDisplay(dsp);
		set_blocked(0);
	}
	return (0);
}

void end_session(void)
{
	system("/usr/sbin/guadalinfo-kill-sessions &");
//	char user[MAX_USER_LENGTH];
//	pid_t pid;
//
//	pid = get_user(user);
//	write_log_fmt("Try to end session for user %s (PID %d).\n", user, pid);
//	if (pid > 0)
//		kill(pid, SIGTERM);
}

void shut_down(void)
{
	system("poweroff");
}

pid_t get_user(char *user)
{
	struct utmp *utmp_rec;
	char tty[13];
	int i;

	/* Look at utmp for users entries and see which one matches... */
	setutent();
	while ((utmp_rec = getutent())) {
		if (utmp_rec->ut_type == USER_PROCESS) {
   strncpy(user, utmp_rec->ut_user, MAX_USER_LENGTH);
   for (i = 0; (utmp_rec->ut_line[i] > 32) && (i < 6); i++)
    tty[i] = utmp_rec->ut_line[i];
   tty[i] = '\0';
		}
		if (!strcmp((const char *) tty, ":0"))
			return utmp_rec->ut_pid;
	}
	/* user not found: returns user "---" */
	strcpy(user,"---");
	return 0;
}
