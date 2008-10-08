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

#ifndef WINDOW_H
#define WINDOW_H

#include <X11/Xlib.h>
#include <sys/types.h>

#define MAX_USER_LENGTH 16
#define MAX_FILENAME_LENGTH 256

/*! @brief Locks the display.
 * @return 0 if success, -1 if not.
 */
int lockScreen(void);

/*! @brief Unlocks the display.
 * @return 0 if success, -1 if not.
 */
int unlockScreen(void);

/*! @brief Tells whether the display is blocked or not
 *
 * @return 1 if blocked, 0 if not.
 */
int is_blocked(void);

/*! @brief Tells which user is currenlty logged to display :0.
 * @param String buffer to hold user's name.
 */
pid_t get_user(char *user);

/*! @brief Mark display as blocked/unblocked.
 * @param yes Whether to block it (1) or unblock it (0).
 * @return 1 if blocked, 0 if not.
 */
int set_blocked(int yes);

/*! @brief Sets the background image to this file
  *
  * @param Complete path to background image file, as a string.
  */
void set_background(char *);

/*! @brief Sets the foreground image to this file
  *
  * @param Complete path to foreground image file, as a string.
  */
void set_foreground(char *);

/*! @brief Sets the logo image to this file
  *
  * @param Complete path to logo image file, as a string.
  */
void set_logo(char *);

/*! @brief Terminate user's X window session (display :0).
 */
void end_session(void);

/*! @brief Terminate user's X window session (display :0).
 */
void shut_down(void);

#endif
