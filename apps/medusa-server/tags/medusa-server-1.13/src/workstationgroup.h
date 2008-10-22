/***************************************************************************
 *   Copyright (C) 2004 by Junta de Andalucía                              *
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

// $Id$
// $Author$
#ifndef WORKSTATIONGROUP_H
#define WORKSTATIONGROUP_H

#include <qobject.h>
#include <qptrlist.h>
#include <qptrdict.h>
#include <qtimer.h>

#include "workstation.h"
#include "stationlist.h"



/// We define a specific type to hold a list
/// of workstations
typedef QPtrList<WorkStation> WorkStationList;
typedef QPtrListIterator<WorkStation> WorkStationListIterator;
//typedef QPtrDict<WorkStation> WorkStationList;
//typedef QPtrDictIterator<WorkStation> WorkStationListIterator;

/**
An object of this class would have a list/group/dictionary with 
all the workstations we are going to work with
 
@author Jesús Roncero
*/

class QTime;
class WaitingDialog;

class WorkStationGroup : public QObject
{
  Q_OBJECT
public:
	WorkStationGroup();
	~WorkStationGroup();
	
	
	int addStation(QString IP = "0.0.0.0", QString name = "noname", QString MAC = "00:00:00:00:00:00");
	void blockStation(QString host);
	void unblockStation(QString host);
	void blockAll();
	void unblockAll();
	void shutdownStation(QString host);
	void shutdownAll();
	
	WorkStation * findHost(QString host);
	void startTimerSession(QString const &host, long seconds, QString user, bool reset = false);
			
	bool save(const QString & fileName, long seconds);
	bool load(const QString & fileName, StationList *stationList, long &seconds);
	bool deleteHost(QString host);
	bool getLoginUser(QString host);
	void statusAll();
	void deleteAll();
	int getState(const QString &host);
	QString getUserFromHost(const QString &host);
	
	
signals:	
	void updateView(QString id, long time);
	void wsSocketErrorSignal(QString host, QString msg);
	void wsStatusChangedSignal(QString host, int status);
	void workstationDeleted(QString host);
	void userChangedSignal(const QString &host, const QString &user);
	void loginUserChangedSignal(const QString &host, const QString &user);

private slots:	

	void askStatus();
	void killDialog();
	void killTimeoutDialog();
	void continueWaiting();
private:
	
	
	QString key;

	QTimer *tickTimer;
	// testing timer
	QTimer *waitingTimer;
	QTimer *waitingTimeoutTimer;
	QTimer *askStatusTimer;
	
	WorkStationList computers;
	int nstation;
	
	QTime m_time;
	
	WaitingDialog *wDialog;
	WorkStation *waitingWS;

};

#endif
