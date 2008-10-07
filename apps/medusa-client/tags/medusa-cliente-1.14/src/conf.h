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

#ifndef CONF_H
#define CONF_H

/*! @brief Reads the config file an store it in the configuration variables.
 *
 * @param config_filename Complete path to config file, as a string.
 * @return 0 If everything went OK
 * @return 1 If we couldn't open the file. In that case, the parameters can be read from the command line.
 * @return -1 If any kind of error happen.
 */
int read_config_file(char *config_filename);

/*! @brief Returns server's IP.
 * @return Server's IP.
 */
struct in_addr get_server(void);

/*! @brief Allow server's IP to connect to socket.
 *
 * @return 1 on error
 * @return 0 on success
 */
int set_server(char *);

/*! @brief Gets the port for the socket
 * @return Port as an integer
 */
int get_listen_port(void);

/*! @brief Sets the port for the socket
 * @param Port (as a string)
 */
void set_listen_port(char *);
#endif
