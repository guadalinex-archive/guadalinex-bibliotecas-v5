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

#ifndef LOG_H
#define LOG_H

#define BIGBUF 1024

/*! @brief writes a message to a log file
 *
 * This functions allows to write a message to the log file
 * if it is opened. If the FILE pointer is not initialiced
 * it would do nothing.
 * Ends with no \n.
 *
 *  Example:
 *  "[18/12/2002 18:18:18] - Message"
 *
 * @param msg string to write.
 */
void write_log(char *);

/*! @brief open log file
 *
 * @param log_filename Complete path to log file, as a string.
 * @return -1 if it couldn't open it
 * @return  0 if everything went ok
 */
int open_log(char *log_filename);

/*! @brief Closes the log file if it was opened
 *
 */
void close_log(void);

/*! @brief Writes a formated log entry
 *
 * It allows you to write a log entry like
 * 
 * @code
 * write_log_fmt("The error is %s\n", error);
 * @endcode
 * 
 * @param fmt string to write
 */
void write_log_fmt(char *, ...);

#endif
