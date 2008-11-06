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

#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "log.h"
#include "conf.h"
#include "medusa.h"
#include "window.h"

static struct in_addr server;
static int listen_port;

int set_server(char *hostname)
{
 int ret;

 ret = inet_aton(hostname, &server);

 if (ret == 0)
  return 1;
	else
		return 0;
}

struct in_addr get_server(void)
{
	return server;
}

int read_config_file(char *config_filename)
{
	FILE *fd;
	char *p;
	char textline[LINEBUFFER];
	int ret;

	if ((fd = fopen(config_filename, "r")) == NULL)
		return 1;

	while (fgets(textline, LINEBUFFER - 1, fd) != NULL) {
		/* We ignore blank lines and comments */
		if (textline[0] == '\n' || textline[0] == '#')
			continue;	

		p = strtok(textline, " \t\n");

		if (strncasecmp("server", p, 4) == 0) {
			int ret;
			p = strtok(NULL, " \t\n");
			ret = set_server(p);
			if (ret) {
				/* error */
				fflush(stderr);
				fflush(stdout);
				fprintf(stderr, "Server IP unknown.\n");
				exit(1);
			}
		} else if (strncasecmp("logfile", p, 7) == 0) {
			p = strtok(NULL, " \t\n");
			open_log(p);
		} else if (strncasecmp("background", p, 10) == 0) {
			p = strtok(NULL, " \t\n");
			set_background(p);
		} else if (strncasecmp("logo", p, 4) == 0) {
			p = strtok(NULL, " \t\n");
			set_logo(p);
		} else if (strncasecmp("foreground", p, 10) == 0) {
			p = strtok(NULL, " \t\n");
			set_foreground(p);
		} else if (strncasecmp("port", p, 4) == 0) {
			p = strtok(NULL, " \t\n");
			set_listen_port(p);
		}
	}
	ret = fclose(fd);
	return ret;

}

void set_listen_port(char *port)
{
	int n_port;

 n_port = atoi(port);
 if (n_port <= 0) {
  n_port = atoi(PORT);
 }
 listen_port = n_port;
}

int get_listen_port(void)
{
	return listen_port;
}
