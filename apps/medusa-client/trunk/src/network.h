#ifndef NETWORK_H
#	define NETWORK_H

#include <stdint.h>

#define INITTAG "MD"
#define ENDTAG "MD"
#define STARTCMD "START"
#define STOPCMD "STOP"
#define STATUSCMD "STATUS"
#define ENDSESSIONCMD "ENDSESSION"
#define USERCMD "USER"
#define SHUTDOWNCMD "SHUTDOWN"
#define MESSAGECMD "MESSAGE"
#define HALFTIMECMD "HALFTIME"
#define QUARTERTIMECMD "QUARTERTIME"
#define TWOMINUTESCMD "TWOMINUTES"
#define ONEMINUTECMD "ONEMINUTE"
#define BLOCKED "BLOCKED"
#define UNBLOCKED "UNBLOCKED"
#define TIMECMD "TIME"

#define MAX_FRAME_SIZE 512

typedef enum {
	start,
	stop,
	status,
	unknown,
	endsession,
	user,
	halftime,
	quartertime,
	twominutes,
	oneminute,
	times,
        rcvmessage,
	sdown
} COMMAND;

#endif

/*! @brief Parse the XML stream comming from the socket.
 *
 * It receives a XML stream with some commands/data and
 * parses it. Go through each element, examining it.
 * It returns a value depending on the data received.
 *  
 * @return unknown  Ambiguous command
 * @return status  Status Command
 * @return stop  Stop command
 * @return start  Start Command
 * @return endssesion End session command
 * @return user User request command
 * @return -1 error
 * @return -2 empty document
 * @return -3 no valid init document
 * @return -4 Could not open display
 */
int parseCommand(const char *cmd);

/*! @brief Read data from the server and take actions as needed.
 *  
 * @param filed Connection's file descriptor.
 * @return 0 on success. -1 if error.
 */
int read_from_client(int filedes);

/*! @brief Sends client status to server.
 *  
 *  @param socket_con The socket.
 */
int send_status(int socket_con);

/*! @brief Sends client user to server.
 *  
 *  @param socket_con The socket.
 */
int send_user(int socket_con);

/*! @brief Builds protocol frame.
 *  
 * @param command
 * @param payload
 * @param frame Buffer that holds the frame. Should be big enough.
 * @param frame_size Buffer size.
 * @return 0 on success. -1 if buffer isn't big enough.
 */
int build_frame(const char *command, const char *payload, char *frame,
								size_t frame_size);

/*! @brief This function creates the socket
 * 
 * @param port Bind socket to this port.
 * @return The socket.
 *
 */
int make_socket(uint16_t port);

/*! @brief Polls the net for incoming frames.
 * 
 * @return 0 on success. -1 if error.
 *
 */
void listen_network(void);

/*! @brief Close network socket.
 */
void close_network(void);
