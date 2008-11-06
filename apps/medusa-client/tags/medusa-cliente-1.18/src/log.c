/***************************************************************************
 *   Copyright (C) 2004 by Junta de Andalucía and Christian Töpp           *
 *   medusa@juntadeandalucia.es						   *
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
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <string.h>
#include <stdarg.h>

#include "conf.h"
#include "medusa.h"

static FILE *log_file = NULL;
int MSG_ERROR = 0;

void write_log(char *msg)
{
 struct tm *date;
 time_t now;
 char buffer[BIGBUF];
 char string_date[50];

 if (log_file == NULL)
  return;

	now = time(NULL);
	date = localtime(&now);

	strftime(string_date, 50, "[%d/%m/%Y %T %Z] - ", date);

	snprintf(buffer, BIGBUF - 1, "%s%s", string_date, msg);

	fprintf(log_file, "%s", buffer);
	fflush(log_file);

}

void write_log_fmt(char *fmt, ...)
{
	va_list args;
	char buffer[BIGBUF];

	va_start(args, fmt);
	vsnprintf(buffer, BIGBUF - 1, fmt, args);
	va_end(args);

	write_log(buffer);
}


int open_log(char *log_filename)
{
	fprintf(stderr, "Trying to open %s\n", log_filename);
	log_file = fopen(log_filename, "a");
	if (log_file == NULL) {
  fprintf(stderr, "Warning: I couldn't open the log file\n");
  return -1;
 }
 return 0;
}

void close_log(void)
{
	if (log_file != NULL)
		fclose(log_file);
	log_file = NULL;
}
