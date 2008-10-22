/***************************************************************************
 *   Copyright (C) 2004 by Junta de Andaluc�                              *
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

#include <qsocket.h>
#include <qstring.h>
#include <qtextstream.h>
#include <qsocketdevice.h>
#include <qhostaddress.h>
#include <qtimer.h>
#include <qapplication.h>

// TODO: This only works on Linux
// We should use #ifdef and the such
#include <sys/types.h>
#include <sys/socket.h>

#include "protocol.h"
#include "workstation.h"
#include "mainwindow.h"
#include "mlog/logitem.h"
#include "mlog/layout.h"
#include "mlog/output.h"

using namespace mlog;

Syslog system_log;
File station_log;
Layout simple_layout;
Layout datetime_layout;

/// Base constructor. It specifies the hostname on creation
WorkStation::WorkStation(QObject * parent, const char * name, QString host, int i ):
	QObject (parent, name),
	hostIP(host)
{
	socket = new QSocket(this);
	socketsec=new QSocket(this);
	connectionTimer = new QTimer();
	timeoutTimer = new QTimer();	
	statusTimer = new QTimer();
	userTimer = new QTimer();

	// timeout for connections
	timeout = 3;
	// Time to wait to start a delayedStatus
	statusTimeout = 4;
	//int count=1; //adrian: vamos a probar esto
	
	
	// connections
	connect(socket, SIGNAL(connected()),
		 SLOT(sendCommand()) );	
	connect(socketsec, SIGNAL(connected()),
		 SLOT(sendCommandTime()) );	
	connect(socket, SIGNAL(connectionClosed()),
		 SLOT(connectionClosedByClient()) );
	connect(socket, SIGNAL(readyRead()),
		this, SLOT(readFromClient()) );
	connect(socket, SIGNAL(error(int)),
		SLOT(socketError(int)) );
	connect(connectionTimer, SIGNAL(timeout()),
		this, SLOT(connectionTimeout()));
	connect(timeoutTimer, SIGNAL(timeout()), this, SLOT(blockSlot()));
	
	connect(statusTimer, SIGNAL(timeout()), 
		this, SLOT(status()) );
	
	connect(userTimer, SIGNAL(timeout()),
		this, SLOT(user()) );
		
	remainingSecs = 0;
	sessionSecs=0; //adrian
	count=1;
	
	messageNum = 0;
	blocked = false;
	active = false;
	state = WorkStation::INACTIVE;
	connStatus = WorkStation::CONN1;

	// log init
	simple_layout.setType(simple);
	datetime_layout.setType(timestamp);
	system_log.assignLayout(simple_layout);
	station_log.assignLayout(datetime_layout);
	ws_log.attachOutput(&system_log);
	ws_log.attachOutput(&station_log);
	
	errorCount = 0;
}

/** Destructor. Have to delete the timers
 */
WorkStation::~WorkStation()
{
	delete timeoutTimer;
	delete connectionTimer;
	delete statusTimer;
	delete userTimer;
}


// We start the timer which, on timeout() will
// would activate the corresponding slot defined
// in the constructor, read: it will block the 
// workstation
void WorkStation::delayBlocked()
{
	// Start of the timer to block the app
	// 10 seconds
	timeoutTimer->start(10 * 1000, true);
}

void WorkStation::blockSlot()
{
	block();
}

void WorkStation::unblock()
{	
	//blocked = false;
	//state = WorkStation::CONN1;	
	messageNum = Protocol::StartCommand;	
	sendMessage();
	
	//statusTimer->start(4 * 1000, true);
}

void WorkStation::endSession()
{
	messageNum = Protocol::EndSessionCommand;
	sendMessage();
}

void WorkStation::user()
{
	messageNum = Protocol::UserCommand;
	sendMessage();
}


void WorkStation::block()
{	
	//state = WorkStation::CONN1;
	messageNum = Protocol::StopCommand;
	sendMessage();
	//emit wsBlocked(0);
	//statusTimer->start(4 * 1000, true);
}

void WorkStation::status()
{	
	messageNum = Protocol::StatusCommand;
	connStatus = WorkStation::CONN1;

	// In case it is not running a timer
	if ( state != WorkStation::ACTIVE) {
		state = WorkStation::CONNECTING ;
	}
	sendMessage();

	
}

/// sends a message to host
void WorkStation::sendMessage()
{
	Q_UINT16 lport=0;
	MainWindow *main = static_cast<MainWindow *>(qApp->mainWidget());

	if (main != NULL)
		lport = main->getControlPort();
	
	if ( hostIP != 0 && lport != 0 ){
		
		socket->connectToHost(hostIP, lport);
		// In case it doesn't connect, abort after 
		// 10 seconds
		//state = WorkStation::CONNECTING ;
		connectionTimer->start(2 * 1000, true);
	}	
}

void WorkStation::sendMessageTime()
{
	Q_UINT16 lport=0;
	MainWindow *main = static_cast<MainWindow *>(qApp->mainWidget());

	if (main != NULL)
		lport = main->getControlPort();
	
	if ( hostIP != 0 && lport != 0 ){
		
		socketsec->connectToHost(hostIP, lport);
		// In case it doesn't connect, abort after 
		// 10 seconds
		//state = WorkStation::CONNECTING ;
		connectionTimer->start(2 * 1000, true); 
	}	
}

QString WorkStation::getHost()
{
	return hostIP;
}

QString WorkStation::getMac()
{
  return mac;
}

QString WorkStation::getHostName()
{
  return hostName;
}

QString WorkStation::getHostIP()
{
	return hostIP;
}


/// sends what variable message has.
void WorkStation::sendCommand()
{
	QTextStream os(socket);	
	Protocol prot;
	
	os << prot.getCommand(messageNum) <<  "\n";

}
void WorkStation::sendCommandTime()
{
	QTextStream os(socketsec);	
	
	
	os << "<MD><TIME" <<remainingSecs << "/></MD>\n";

}



/// close the socket when the remote machine closes the connection
void WorkStation::connectionClosedByClient()
{
	closeConnection();
}

/// \brief reads data from clients
// 
// This slot is executed when the client 
// writes in the socket. It reads the first line,
// as expected, and then discards the rest of the Data
// so If another data is coming, a new signal is 
// produced.
void WorkStation::readFromClient()
{
	QString msg;
	// previous state
		
	if (socket->canReadLine()){
		msg = socket->readLine();
	}
	
	// should read the rest of the socket.
	// Only one line is expected
	while(socket->canReadLine() ) {
              socket->readLine();
	}
	
	qDebug("WorkStation::readFromClient()  read: " + msg );	
	
	int a;
	
	// I need to check it against -1 to make sure it has found it 
	if ( msg.find("<STATUS>") != -1 ) {
		if (  msg.find("UNBLOCKED") != -1){
			emit wsStatusChanged(hostIP, WorkStation::INACTIVE);
			
			// In case it is not running on a timer
			if ( state != WorkStation::ACTIVE )
				state = WorkStation::INACTIVE;
			
		}
		else if ( msg.find("BLOCKED") != -1){
			qDebug("WS blocked status: %d", WorkStation::BLOCKED);
			emit wsStatusChanged(hostIP, WorkStation::BLOCKED);
			
			// In case it is not running on a timer
			if ( state != WorkStation::ACTIVE )
				state = WorkStation::BLOCKED;
		}
		// We check the login user
		delayUser();
		
		// reseting the error count
		errorCount = 0;
	}
	else if ( (a = msg.find("<USER>" )) != -1 ) {	
		QString user = msg.remove("<USER>").remove("</USER>");
		qDebug("Read: " + user );
		
		emit loginUserChanged(hostIP, user);	
	}
	else{
		qDebug("WS error Not a medusa client");
		QString err(tr("Not a medusa client"));
		if (errorCount < 5){
			errorCount++;
		}
		else{
			state = WorkStation::ERROR;
			emit wsConnError(hostIP, err);
		}
	}
	closeConnection();
}

void WorkStation::setUser(QString name)
{
	actualUser = name;
	// emit signal
	emit userChanged(hostIP, name);
}

QString WorkStation::getUser()
{
	return actualUser;
}

// Emits a signal with the specified socket error
// TODO
void WorkStation::socketError(int errorno)
{
	qDebug("socket error with  " + hostIP);
	QString err("Error: ");
	
	switch(errorno) {
	case QSocket::ErrConnectionRefused:
        	err += tr("the connection was refused. ");
        	break;
	case QSocket::ErrHostNotFound:
		err += tr("the host was not found. ");
		break;
	case QSocket::ErrSocketRead:
		err += tr("a read from the socket failed. ");
		break;
	default:
        	break;
	}

	// Should emit some more info to indicate the host failing?
	emit wsConnError(hostIP, err);
	
	// Put the Error state only when it is repeated 
	// we just want to make sure it is an real error and
	//not a transient error
	
	qDebug("WorkStation::socketError host: " + hostIP + " ErrorCount: %d", errorCount);
	
	if (errorCount < 5 ){
		errorCount++;
	}
	else{
		state = WorkStation::ERROR;
		//errorCount = 0;
	}
	closeConnection();


}



/// this function is executed on the connectionTimer Timeout
/// If I'm in the process of sending a block or unblock command
/// I would not put the error state. Only if it is a status command
/// which is due to happen afterwards the block or unblock command
void WorkStation::connectionTimeout()
{
	QString err;
	//qDebug("WorkStation::connectionTimeout() on host: "+ hostIP);
	
	if (messageNum == Protocol::StopCommand || messageNum == Protocol::StartCommand){
		closeConnection();
	}
	else{
		err = "Error: Connection timeout on %1!";
		err = err.arg(hostIP);
		emit wsConnError(hostIP, err);

		qDebug("WorkStation::connectionTimeout host: " + hostIP + " ErrorCount: %d", errorCount);
		if ( errorCount < 5 ){
			errorCount ++;
		}
		else{
			state = WorkStation::ERROR;
		}
		closeConnection();
	}
}

/// delayed status in offset seconds
void WorkStation::delayStatus(int offset)
{
	if (offset == 0){
		statusTimer->start(statusTimeout * 1000, true);
	}
	else{
		qDebug("delayStatus con %d d�imas de segundos", offset);
		statusTimer->start(offset * 50, true);
	}
		
}

//
void WorkStation::closeConnection()
{
	socket->close();
	connectionTimer->stop();
	//connectionTimer->stop();
}


//! broadcasts a wake on lan frame with this station's mac
// This doesn't work at the moment. TODO
// TODO: MAC must be stored in a QString item (whole method commented out until then)
void WorkStation::wakeUp()
{
/*	QSocketDevice *qsd;
	QHostAddress *address;
	char payload[102];
	int one = 1, i;

	qsd = new QSocketDevice(QSocketDevice::Datagram);
	setsockopt(qsd->socket(), SOL_SOCKET, SO_BROADCAST, &one, sizeof(one));

	// TODO: This broadcast address should be taken from the application's settings
	address = new QHostAddress();
	address->setAddress("192.168.1.255");

	// If MAC address is 0x01:0x02:0x03:0x04:0x05:0x06, WorkStation::mac="\x01\x02\x03\x04\x05\x06"
	std::memcpy(payload, "\xff\xff\xff\xff\xff\xff", 6);
	for (i = 0; i < 16; ++i)
  	std::memcpy(&payload[6 * i], mac, 6);

	// TODO: Port should be taken from the application's settings
	qsd->writeBlock(payload, 102, *address, 10000);

	qsd->close();*/
}

void WorkStation::setMac(QString mac)
{
	WorkStation::mac = mac;
}

void WorkStation::setName(QString name)
{
	hostName = name;
}

bool WorkStation::isActive()
{
	return active;
}


int WorkStation::getState()
{
	return state;
}



//void WorkStation::updateTimer(Q_UINT8 offset)
void WorkStation::updateTimer()
{
	//qDebug("Entrando en updateTimer para estacion id: %d ", id);
	//qDebug("state: %d, remainingSecs: %d", state, remainingSecs);
	


	switch (state){
		case WorkStation::ACTIVE :	
			if (remainingSecs <= 0){
				// We need to block the workstation	
				blockStation();
				
				// should emit a signal indicating we blocked the station
				// maybe in the blocked function
				
				// emiting a -1 time. Just to indicate on screen the timer finished
				emit wsTimeChanged(hostIP, -1);
				
			}
			if (remainingSecs <= sessionSecs/2 && count == 1){
				//halfTimeNotify(); 
				timeNotify(); //adrian
				status();
				count=2; 
				remainingSecs -= 1;
				// emit workstation changed
				emit wsTimeChanged(hostIP, remainingSecs);
				if ((remainingSecs % 30 ) == 0 ){
					delayUser();		
				}
			}
			if (remainingSecs <= sessionSecs/4 && count ==2){
				//quarterTimeNotify(); 
				timeNotify();//adrian
				status();
				count=3;
				remainingSecs -= 1;
				// emit workstation changed
				emit wsTimeChanged(hostIP, remainingSecs);
				if ((remainingSecs % 30 ) == 0 ){
					delayUser();	
				 }
			}
			if (remainingSecs<=120 && remainingSecs>60 && count != 4){
				//twoMinutesNotify(); 
				timeNotify();
				status();
				count=4; 
				remainingSecs -= 1;
				//printf("(<2m)Segundos que quedan: %d \n",remainingSecs);
				// emit workstation changed
				emit wsTimeChanged(hostIP, remainingSecs);
				if ((remainingSecs % 30 ) == 0 ){
					delayUser();	
				}
			}
			if (remainingSecs<=60 && remainingSecs >0 && count != 5){
				//oneMinuteNotify();
				timeNotify();
				status();
				count=5;	
				remainingSecs -= 1;
				//printf("(<1m)Segundos que quedan: %d \n",remainingSecs);
				// emit workstation changed
				emit wsTimeChanged(hostIP, remainingSecs);
				if ((remainingSecs % 30 ) == 0 ){ 
					delayUser();	
				
				  }
			}
			else{		//Check if we have to change this ¿?
				remainingSecs -= 1;
				// emit workstation changed
				emit wsTimeChanged(hostIP, remainingSecs);
				
				if ((remainingSecs % 30 ) == 0 ){
					delayUser();	
				}
				
			}
			break;
		case WorkStation::CONNECTING:
			switch(connStatus){
				case WorkStation::CONN1:
					emit wsStatusChanged(hostIP, WorkStation::CONN1);
					connStatus = WorkStation::CONN2;
					break;
				case WorkStation::CONN2:
					emit wsStatusChanged(hostIP, WorkStation::CONN2);
					connStatus = WorkStation::CONN3;
					break;
				case WorkStation::CONN3:
					emit wsStatusChanged(hostIP, WorkStation::CONN3);
					connStatus = WorkStation::CONN4;
					break;
				case WorkStation::CONN4:
					emit wsStatusChanged(hostIP, WorkStation::CONN4);
					connStatus = WorkStation::CONN1;
					break;
			}
			break;
	}
	
}

/// This starts a new session on the remote workstation
void WorkStation::startSession(long nsecs)
{
	//qDebug("Entramos en startSession()");
	
	if (state == WorkStation::ACTIVE) {
		// We are in the middle of a session. Logging the last one
		ws_log.log("End session for user " + getUser() + " from IP " + getHostIP() + ".");
		emit userChanged(hostIP, "");
	}
	state=WorkStation::ACTIVE;
	qDebug("WorkStation::startSession() - trying to start timer for %ld seconds", nsecs);
	ws_log.log("Start session for user " + getUser() + " from IP " + getHostIP() + ".");
	unblock(); 
	delayStatus();
	unblock(); //a
	remainingSecs = nsecs;
	sessionSecs=nsecs;
	timeNotify();
	unblock();//a
	
}

/// Would stop a running timer
void WorkStation::stopSession()
{
	if (state == WorkStation::ACTIVE) {
		// We are in the middle of a session. Logging the last one
		ws_log.log("End session for user " + getUser() + " from IP " + getHostIP() + ".");
		//emit userChanged(hostIP, "");
	}
	state = WorkStation::INACTIVE;
	active = false;
	//ws_log.log("Stop session1 count on user " + getUser() + ".");
	// Not blocking the workstation because we may want it to be
	// this way.
	
}


/// high level function to block the workstation and
/// send a status delayed command
void WorkStation::blockStation()
{
	if (state == WorkStation::ACTIVE) {
		// We are in the middle of a session. Logging the last one
		ws_log.log("End session for user " + getUser() + " from IP " + getHostIP() + ".");
		emit userChanged(hostIP, "");
	}
	block();
	state = WorkStation::BLOCKED;
	//delayStatus();
	
}

/// high level function to unblock the workstation and
/// send a status delayed command
void WorkStation::unblockStation()
{
	if (state == WorkStation::ACTIVE) {
		// We are in the middle of a session. Logging the last one
		ws_log.log("End session for user " + getUser() + " from IP " + getHostIP() + ".");
		emit userChanged(hostIP, "");
	}
	
	unblock();
	state = WorkStation::INACTIVE;
	//delayStatus();
}
	
void WorkStation::pauseSession()
{
	
}

void WorkStation::continueSession()
{
	
}

/// checks the login user on the client
void WorkStation::delayUser()
{
	qDebug("WorkStation::delayUser activated");
	//if (state != WorkStation::ERROR )
		userTimer->start(5 * 1000, true);
}

/// shuts down 
void WorkStation::shutdown()
{	
	messageNum = Protocol::ShutdownCommand;	
	sendMessage();
}
void WorkStation::timeNotify()
{

	messageNum=Protocol::timeCommand;
	sendMessageTime();
}
void WorkStation::halfTimeNotify()
{
	messageNum=Protocol::halfTimeCommand;
	sendMessageTime();
}
void WorkStation::quarterTimeNotify()
{
	messageNum=Protocol::quarterTimeCommand;
	sendMessageTime();
}
void WorkStation::twoMinutesNotify()
{
	messageNum=Protocol::twoMinutesCommand;
	sendMessageTime();
}
void WorkStation::oneMinuteNotify()
{
	messageNum=Protocol::oneMinuteCommand;
	sendMessage();
}

/// high level function to shut down the workstation
void WorkStation::shutdownStation()
{
	if (state != WorkStation::ERROR || state != WorkStation::CONNECTING || state != WorkStation::SHUTTINGDOWN) {
		// We can connect to the workstation
		ws_log.log("Shutting down IP " + getHostIP() + ".");
		state = WorkStation::SHUTTINGDOWN;
		shutdown();
	}
}
