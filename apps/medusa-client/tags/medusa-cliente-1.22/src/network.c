/***************************************************************************
 *   Copyright (C) 2004 by Junta de Andaluc� and Christian T�p           *
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
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <netdb.h>
#include <string.h>
#include <signal.h>
#include <arpa/inet.h>
#include <X11/Xlib.h>
#include <X11/xpm.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>
#include <getopt.h>

#include "log.h"
#include "window.h"
#include "network.h"
#include "conf.h"

static int sock;
xmlChar * message;
char * tam;

int parseCommand(const char *cmd)
{
	xmlDocPtr doc;
	xmlNodePtr cur;
	COMMAND mode;

	write_log_fmt("String received:  %s \n", cmd);
	printf("String received: %s \n",cmd); //adrian, vamos a mostrar en pantalla el n sec
	doc = xmlParseMemory(cmd, strlen(cmd));
	if (doc == NULL)
		return (-1);
	cur = xmlDocGetRootElement(doc);
	if (cur == NULL) {
		write_log_fmt("empty document\n");
		xmlFreeDoc(doc);
		return (-2);
	}
	/* Case sensitive search */
	if (xmlStrcmp(cur->name, (const xmlChar *) INITTAG))
		return (-3);
	write_log_fmt("Rootelement: '%s'\n", cur->name);
	cur = cur->xmlChildrenNode;
	while (cur != NULL) {
		if (!xmlStrcmp(cur->name, (const xmlChar *) STARTCMD)) {
			write_log_fmt("START command received\n");
			mode = start;
			/*break; */
		} else if (!xmlStrcmp(cur->name, (const xmlChar *) STOPCMD)) {
			write_log_fmt("STOP Command received\n");
			mode = stop;
			/*break; */
		} else if (!xmlStrcmp(cur->name, (const xmlChar *) STATUSCMD)) {
			write_log_fmt("STATUS Command received\n");
			mode = status;
			/*break; */
		} else if (!xmlStrcmp(cur->name, (const xmlChar *) USERCMD)) {
			write_log_fmt("USER Command received\n");
			mode = user;
			/*break; */
		} else if (!xmlStrcmp(cur->name, (const xmlChar *) ENDSESSIONCMD)) {
			write_log_fmt("ENDSESSION Command received\n");
			mode = endsession;
			/*break; */
		} else if (!xmlStrcmp(cur->name, (const xmlChar *) SHUTDOWNCMD)) {
			write_log_fmt("SHUTDOWN Command received\n");
			mode = sdown;
			/*break; */
		} else if (!xmlStrcmp(cur->name, (const xmlChar *) MESSAGECMD)) {
			write_log_fmt("MESSAGE Command received\n");
         message = xmlNodeGetContent(cur);
         write_log_fmt("Mensaje: %s\n",message);
         tam = xmlGetProp(cur, "lengh");
			mode = rcvmessage;
			/*break; */
		} else if (!xmlStrcmp(cur->name, (const xmlChar *) HALFTIMECMD)) {
			write_log_fmt("HALFTIME Command received\n");
			//mode = halftime;
			mode=unknown;
			//Llamada al system que corresponda o a la libreria
		} else if (!xmlStrcmp(cur->name, (const xmlChar *) QUARTERTIMECMD)) {
			write_log_fmt("QUARTERTIME Command received\n");
			//mode = quartertime;
			mode=unknown;
		} else if (!xmlStrcmp(cur->name, (const xmlChar *) TWOMINUTESCMD)) {
			write_log_fmt("TWOMINUTES Command received\n");
			mode = twominutes;
			//Llamada al system que corresponda o a la libreria
		} else if (!xmlStrcmp(cur->name, (const xmlChar *) ONEMINUTECMD)) {
			write_log_fmt("ONEMINUTE Command received\n");
			mode = oneminute; //O podemos definir una accion en read_from_client
			//Llamada al system que corresponda o a la libreria	
		} else if (!xmlStrcmp(cur->name, (const xmlChar *) TIMECMD)) {
			write_log_fmt("TIME Command received\n");
			//printf("TIME command received curname %s\n",cur->name);
			mode = times;
		} else {
			write_log_fmt("Ambiguous Command\n");
			//printf("Es el tiempo? : %s\n",cur->name);
			mode = unknown;
		}
		cur = cur->next;
	}
	/* Free the memory */
	xmlFreeDoc(doc);
	return (mode);
}

int send_status(int socket_con)
{
	char buffer[BIGBUF];
	int nbytes;
	char frame[MAX_FRAME_SIZE];
	int status;

	assert(socket_con > 0);

	status = is_blocked();
	nbytes = build_frame(STATUSCMD, (status ? BLOCKED : UNBLOCKED), frame,
							MAX_FRAME_SIZE);
  if (nbytes <= 0) return -1;
	snprintf(buffer, sizeof(buffer) - 1, frame);

	nbytes = strlen(buffer);
  if (nbytes <= 0) return -1;
	/* writing to the socket */
	if (write(socket_con, buffer, nbytes) < 0) {
		perror("Socket write failure.");
		return -1;
	}
	return 0;
}

int send_user(int socket_con)
{
	char buffer[BIGBUF];
	int nbytes;
	char frame[MAX_FRAME_SIZE];
	char user[MAX_USER_LENGTH];

	assert(socket_con > 0);

	get_user(user);
	nbytes = build_frame(USERCMD, (const char *) user, frame, MAX_FRAME_SIZE);
  if (nbytes <= 0) return -1;
	snprintf(buffer, sizeof(buffer) - 1, frame);

	nbytes = strlen(buffer);
  if (nbytes <= 0) return -1;
	/* writing to the socket */
	if (write(socket_con, buffer, nbytes) < 0) {
		perror("Socket write failure");
		return -1;
	}
	return 0;
}

int make_socket(uint16_t port)
{
	int new_socket;
	u_int yes = 1;

	struct sockaddr_in name;
	/* Create the socket. */
	new_socket = socket(PF_INET, SOCK_STREAM, 0);

	if (new_socket < 0) {
		perror("socket");
		write_log_fmt("Socket Error\n");
		exit(EXIT_FAILURE);
	}

	/* Give the socket a name. */
	name.sin_family = AF_INET;
	name.sin_port = htons(port);
	name.sin_addr.s_addr = htonl(INADDR_ANY);

	if (setsockopt(new_socket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) < 0) {
		perror("Reusing ADDR failed");
		exit(1);
	}

	if (bind(new_socket, (struct sockaddr *) &name, sizeof(name)) < 0) {
		perror("bind");
		write_log_fmt("Bind Error.\n");
		exit(EXIT_FAILURE);
	}

	return new_socket;
}

int read_from_client(int filedes)
{
	char buffer[MAX_FRAME_SIZE];
	int nbytes;
	int secs;
	int horas=0,minutos=0,minutosRes=0,segRes=0;
	COMMAND rc;
	char cadena[100];

	nbytes = read(filedes, buffer, MAX_FRAME_SIZE);

	if (nbytes < 0) {
		/* Read error. */
		perror("read error. Read <0 bytes");
		//exit(EXIT_FAILURE);
		return -1;
	} else if (nbytes == 0) {
		/* End-of-file. */
		//write_log_fmt("end of file __LINE__\n");
		return -1;
	} else {
		buffer[nbytes - 1] = '\0';
		rc = parseCommand(buffer);
		switch (rc) {
		case start:
			unlockScreen();
			/* Should do a check on the return type */
			send_status(filedes);
			break;
		case stop:
         /* Not needed for bibliotecas */
			//end_session();
			if (lockScreen() < 0) {
				write_log_fmt("Could not open display.\n");
				exit(EXIT_FAILURE);
			}
			send_status(filedes);
			break;
		case status:
			if (send_status(filedes) < 0 )
				return -1;
			return 0;
			break;
		case endsession:
			end_session();
			// If I do not exit, the program would be killed anyway when
			// the X server restarts, right?
			//exit(0);
			break;
		case user:
			send_user(filedes);
			return 0;
			break;
		case sdown:
			shut_down();
			break;
		case rcvmessage:
			recive_message(atoi(tam), message);
			break;
		case halftime:
			printf("Le queda la mitad del tiempo\n");
			//system("guadalinfo-notify-send 60000 'Le queda la mitad del tiempo'");
			break;
		case quartertime:
			printf("Le queda un cuarto del tiempo\n");
			//system("guadalinfo-notify-send 60000 'Le queda un cuarto del tiempo'");
			break;
		case twominutes:
			printf("Le quedan dos minutos\n");
			//system("guadalinfo-notify-send 60000 'Le quedan 2 minutos'");
			break;
		case oneminute:
			printf("Le queda un minuto\n");
			//system("guadalinfo-notify-send 60000 'Le queda 1 minuto\n'");
			break;
		case times:
//			printf("Comando Time\n");
		//	printf("se le pasará el parseador para devolver el tiempo en %s\n",buffer);
			break;
		case unknown: /* unknown command. Not an error. Ignore at the moment */
		//	printf(" Puede ser que contenga el tiempo %s\n",buffer);
			secs= bufferparser(buffer);
			if (secs == 0)
			{
				break;
			} //si no es una cadena correcta
		//	printf("Numero de segundos: %d \n",secs);	
			horas = secs / 3600;
   			minutos = secs / 60; 
   			minutosRes = minutos % 60; 
    			segRes = secs % 60;
			if (horas >0)
			{
			snprintf(cadena,sizeof(cadena),"guadalinfo-notify-send 60000 Le quedan %d Horas y %d Minutos \n",horas,minutosRes);
			system(cadena);
			}
			else
			{
				if (minutosRes<1)
				{
					snprintf(cadena,sizeof(cadena),"guadalinfo-notify-send 60000 Le queda menos de un minuto, por favor, guarde todos sus trabajos \n",minutosRes);
					system(cadena);
				}
				else{			
					snprintf(cadena,sizeof(cadena),"guadalinfo-notify-send 60000 Le quedan  %d Minutos %d segundos\n",minutosRes, segRes);
					system(cadena);
				}
			}
			printf("Numero de horas: %d \n",horas);
			printf("Numero de minutos: %d \n",minutosRes);
			printf("Numero de segundos: %d \n",segRes);
			return 0;
			break;
		default: /* ERROR */
			return 0;
		}
		return 0;
	}
}

int bufferparser(char *buffer)
{
int secs=0;
int i,n=0;
char cad[12];

for (i=0;i<=strlen(buffer);i++)
{
   if (buffer[i]=='<' && buffer[i+1]== 'T'  && buffer[i+2]=='I' && buffer[i+3]=='M' && buffer[i+4]=='E')
        {
        i=i+5;
        if(isdigit(buffer[i]))
        {
                while(isdigit(buffer[i]))
                {
                cad[n]=buffer[i];
                n++;
                i++;
		if (n>9)
		{
		printf("Numero fuera de rango\n");
		break;
		}
                }
                cad[n]='\n';
		break;

        }

}

}
secs=atoi(cad);

return secs;
}


void close_network(void)
{
	close(sock);
}

void listen_network(void)
{
	fd_set active_fd_set, read_fd_set;
	int i;
	struct sockaddr_in clientname;
	size_t size;
	int rc;

	struct in_addr allowed_host;
	struct in_addr actual_host;

	/* Create the socket and set it up to accept connections. */
	sock = make_socket(get_listen_port());

	if (listen(sock, 1) < 0) {
		perror("listen");
		write_log("Could not create socket - listen.\n");
		exit(EXIT_FAILURE);
	}
	/* Initialize the set of active sockets. */
	FD_ZERO(&active_fd_set);
	FD_SET(sock, &active_fd_set);
	while (1) {
		/* Block until input arrives on one or more active sockets. */
		read_fd_set = active_fd_set;
		if (select(FD_SETSIZE, &read_fd_set, NULL, NULL, NULL) < 0) {
			write_log("Could not create socket - select.\n");
			exit(EXIT_FAILURE);
		}
		/* Service all the sockets with input pending. */
		for (i = 0; i < FD_SETSIZE; ++i) {
			if (FD_ISSET(i, &read_fd_set)) {
				if (i == sock) {
					/* Connection request on original socket. */
					int new;
					size = sizeof(clientname);
					new = accept(sock, (struct sockaddr *) &clientname, &size);
					if (new < 0) {
						perror("accept");
						write_log("Could not create socket - accept.\n");
						//exit(EXIT_FAILURE);
					} else {
						/* Connection checking here */
						actual_host = (struct in_addr) clientname.sin_addr;
						allowed_host = get_server();

						if (actual_host.s_addr != allowed_host.s_addr) {
							write_log_fmt("Connection from disallowed host %s.\n",
									inet_ntoa((struct in_addr) clientname.sin_addr));
						} else {
							write_log_fmt("Server: connect from host %s, port %hd.\n",
									inet_ntoa((struct in_addr) clientname.sin_addr),
									ntohs(clientname.sin_port));
							FD_SET(new, &active_fd_set);
						}
					}
				} else {
					/* Data arriving on an already-connected socket. */

					/* compruebo
					 * leo y guardo resultado 
					 * si no error
					 *  	proceso lectura
					 *  	y actuo
					 * entonces
					 *      error
					 * */

					
					rc = read_from_client(i);
					if (rc < 0) {
						close(i);
						/*printf(stderr, "Error en la lectura\n");*/
						FD_CLR(i, &active_fd_set);
					} /*else if (rc == 2000) {
						// Sending Data
						//send_status(i);
						close(i);
					}*/
				}
			}
		}
	}
}

int build_frame(const char *command, 
		const char *payload, char *frame, size_t frame_size)
{
	int i = 0;

	frame[i++] = '<';
	if (strlen(command) > (frame_size - i))
		return -1;
	strncpy(&frame[i], command, strlen(command));
	i += strlen(command);
	frame[i++] = '>';
	if (strlen(payload) > (frame_size - i))
		return -1;

	strncpy(&frame[i], payload, strlen(payload));

	i += strlen(payload);
	frame[i++] = '<';
	frame[i++] = '/';
	if (strlen(command) > (frame_size - i))
		return -1;
	strncpy(&frame[i], command, strlen(command));
	i += strlen(command);
	frame[i++] = '>';
	frame[i++] = '\n';
	frame[i] = '\0';
	
	return i;
}

