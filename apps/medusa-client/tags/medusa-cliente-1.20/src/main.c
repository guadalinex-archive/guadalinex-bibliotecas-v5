/***************************************************************************
 *   Copyright (C) 2004 by Junta de Andalucía and Christian Töpp           *
 *   medusa@juntadeandalucia.es                                            *
 *									   *
 *   Jesús Roncero Franco						   *
 *   Daniel Carrión Reinoso						   *
 *   Coordinación: Rafael Martín de Agar Tirado				   *
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
#include <getopt.h>
#include <stdlib.h>
#include <signal.h>

#include "medusa.h"
#include "log.h"
#include "conf.h"
#include "window.h"
#include "network.h"

/*! @brief Executed automaticaly at exit 
 * 
 *  This function is executed whenever the program finished, so
 *  its good to do some finalization code here.
 */
void f_atexit(void)
{
 close_network();
 fflush(stdout);
 write_log_fmt("Closing app\n");
 close_log();
}

/*! @brief Handles Control-C 
 *
 * This function is executed when the SIGINT signal is sent to the program
 */
void sig_ctrlc(void)
{
	write_log_fmt("<< CTRL-C >> pressed. Exiting...\n");
	f_atexit();
	exit(0);
}

/*! @brief Show command line options */
void print_usage(void)
{
	fprintf(stdout, "Usage: mdclient options\n");
	fprintf(stdout, "  -h  --help		Shows this help.\n"
			"  -L  --logfile 	Specify the log file to use.\n"
			"  -c  --config		Specify the config file to use.\n"
			"  -s  --server		Specify the server host IP.\n"
			"  -b  --background	Specify the background image to use.\n"
			"  -f  --foreground	Specify the foreground image to use.\n"
			"  -l  --logo		Specify the logo image to use.\n"
			"  -x  --blocked	Start blocked.\n"
			"  -p  --port		Specify the port to use (default %s)\n.", PORT);
}

int main(int argc, char *argv[])
{
	/* getopt */
	int next_option;

	int ret;
	int will_block = 0;

	/*! short options. See man getopt */
	const char *const short_options = "hc:l:L:b:f:xp:s:";
	/*! the array for the long options. */
	const struct option long_options[] = {
		{"help", 0, NULL, 'h'},
		{"config", 1, NULL, 'c'},
		{"logfile", 1, NULL, 'L'},
		{"background", 1, NULL, 'b'},
		{"foreground", 1, NULL, 'f'},
		{"logo", 1, NULL, 'l'},
		{"blocked", 0, NULL, 'x'},
		{"port", 1, NULL, 'p'},
		{"server", 1, NULL, 's'},
		{NULL, 0, NULL, 0}
	};

	/* Initializing exit function */
	if (atexit(f_atexit) != 0) {
		fprintf(stderr, "failed to register f_atexit() exit function\n");
		exit(EXIT_FAILURE);
	}
	if (signal(SIGINT, sig_ctrlc) == SIG_ERR) {
		fprintf(stderr, "Warning - Could not set CTRL-C handler\n");
	}

	/* First, set defaults */
	set_listen_port(PORT);
	set_foreground(FOREGROUND_IMAGE);
	set_logo(LOGO_IMAGE);
	/* Second, read entries from default config file. 
	 * They will eventually be replaced by command line settings. */
	read_config_file(CONFIGFILE);

	/* Then, overwrite with command line options... */
	do {
		next_option = getopt_long(argc, argv, short_options, long_options, NULL);
		switch (next_option) {
		case 'h':	/* -h or --help */
			print_usage();
			exit(1);

		case 'c':/* -c or --config */
			/* Things like "mdclient -p 7000 -c /etc/mymedusa.conf" 
			 * when port is set to a different value in /etc/mymedusa.conf
			 * may result in an unpredictable value for listen_port. Just don't do that. */
			read_config_file(strdup(optarg));
			break;

		case 'p': /* -p or --port */
			set_listen_port(strdup(optarg));
			break;

		case 'x': /* -x or --blocked */
			will_block = 1;
			break;

		case 'b': /* -b or --background */
			set_background(strdup(optarg));
			break;

		case 'l': /* -l or --logo */
			set_logo(strdup(optarg));
			break;

		case 'f': /* -f or --foreground */
			set_foreground(strdup(optarg));
			break;

		case 'L': /* -L or --logfile */
			close_log();
			open_log(strdup(optarg));
			break;
		case 's': /* -s or --server */
			ret = set_server(strdup(optarg));
			if (ret) {
				/* error */
				fflush(stderr);
				fflush(stdout);
				fprintf(stderr, "Server IP unknown.\n");
				exit(1);
			}
			break;

		case '?':/* The user specified an invalid option */
			/* Write usage info on the screen   */
			print_usage();
			exit(1);

		case -1: /* No more options */
			break;

		default: /* Garbage */
			abort();
		}
 } while (next_option != -1);

 if (will_block) {
  if (lockScreen() < 0) {
   write_log_fmt("Could not open display.\n");
			exit(EXIT_FAILURE);
		}
	}
				
	write_log_fmt("Starting...\n");
	listen_network();
	close_log();
	return 0;
}
