/***************************************************************************
 *   Copyright (C) 2004 by Emergya, S.C.A.                                   *
 *   info@emergya.info                                                     *
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

#ifndef WORKSTATION_H
#define WORKSTATION_H

#include <qsocket.h>
#include <qstring.h>
#include <qdatetime.h>

#include "mlog/logitem.h"

/// \brief this class models a workstation and should
/// provide all the functionality to operate with each
/// of the workstations
/// @author Jesús Roncero
/// @author Daniel Carrión
class WorkStation : public QObject 
{
	Q_OBJECT

public:
	//WorkStation(QObject * parent = 0, const char * name = 0);
	WorkStation(QObject * parent = 0, const char * name = 0, QString host = "0", int i = 0);
	~WorkStation();
	

	enum StateFlags { 
		ACTIVE, 	// The workstation is on and timer is on
		BLOCKED, 	// the WS is blocked
		PAUSED, 	// the WS is paused
		INACTIVE, 	// the WS is unblocked and timer isn't on
		ERROR,		// could not connect to it
		CONNECTING,	// trying to connecto to the client	
      SHUTTINGDOWN   // shutting down
	};
	
	enum ConnectionState {
		CONN1 = 100,   // I need to do this to avoid conflicting with StateFlags	
		CONN2,		// Quick Hack    TODO
		CONN3,
		CONN4
	};

	mlog::LogItem ws_log;

	void sendMessage();
	void block();
	void unblock();
	
	QString getHost(); // Should be deprecated???
	QString getHostIP();
	QString getHostName();
	QString getMac();
	void setName(QString name);
	void setMac(QString mac);
	bool isActive();
	void setUser(QString name);
	QString getUser();
	int getState();

   void shutdown();
	
	// This would update the remaining time
	void startSession(long nsecs);
	void stopSession();
	// higher level functions
	void blockStation();
	void unblockStation();
	void endSession();
   void shutdownStation();	
	void pauseSession();
	void continueSession();
	void delayStatus(int offset=0);
	
	
signals:
	void wsConnError(QString host, QString message);
	void wsTimeChanged(QString host, long rsecs);
	void wsBlocked(Q_UINT8 id);
	void wsStatusChanged(QString host, int state);
	void userChanged(const QString &host, const QString &user);
	void loginUserChanged(const QString &host, const QString &user);

public slots:	
	void updateTimer();
	//void updateTimer(Q_UINT8 offset);
	void status();
	void user();	
	

private slots:
	
	void connectionClosedByClient();
	void readFromClient();
	void socketError(int errorno);
	void sendCommand();
	void blockSlot();
	void delayBlocked();
	void wakeUp();
	void connectionTimeout();

	
private:
	
	void closeConnection();
	void delayUser();
	
	
	const QString hostIP;
	// If MAC address is 0x01:0x02:0x03:0x04:0x05:0x06, WorkStation::mac="\x01\x02\x03\x04\x05\x06"
	QString mac;
	// right now it's only a QString
	QString actualUser;	
	QString logName;
	QString hostName;
	
	QSocket *socket;
	
	QTimer *connectionTimer;
	QTimer *timeoutTimer;
	QTimer *statusTimer;
	QTimer *userTimer;
	
	QTime initHour;
	
	// indicates the state of the station TODO 
	Q_UINT8 state;	
	Q_UINT8 messageNum;
	Q_UINT16 port;
	// used to access the lists and emit signals
	Q_UINT8 id;
	// remaining seconds until block
	long remainingSecs;
		
	bool active;
	bool blocked;
	
	// I need to do this here because I must track the ip on wich the state changes
	int connStatus;
	
	int statusTimeout;
	int timeout;
	
	// we count the errors
	int errorCount;

};

#endif

