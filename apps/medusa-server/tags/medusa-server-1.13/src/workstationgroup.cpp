/***************************************************************************
 *   Copyright (C) 2004 by Junta de Andalucía                              *
 *   medusa@juntadeandalucia.es                                            *
 *									   *
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

//
// $Id$
// $Author$
#include <qtimer.h>
#include <qdatetime.h>
#include <qdom.h>
#include <qfile.h>
#include <iostream>
#include <qapplication.h>
#include <qprogressbar.h>
#include <qmessagebox.h>

#include "mainwindow.h"
#include "workstationgroup.h"
#include "workstation.h"
#include "stationlist.h"
#include "waitingdialog.h"


using namespace std;

WorkStationGroup::WorkStationGroup()
{
	nstation = 0;
	tickTimer = new QTimer();	
	tickTimer->start(1 * 1000, false);
	//computers = new WorkStationList(this);
	computers.setAutoDelete(TRUE);
	waitingTimer = new QTimer();
	waitingTimeoutTimer = new QTimer();
	askStatusTimer = new QTimer();
	
	
	
	connect (waitingTimeoutTimer, SIGNAL(timeout()), this, SLOT(killTimeoutDialog()));
 	connect (waitingTimer, SIGNAL(timeout()), this, SLOT(continueWaiting()));	
	//connect (tickTimer, SIGNAL(timeout()), this, SLOT(askStatus()));
	connect (askStatusTimer, SIGNAL(timeout()), this, SLOT(askStatus()));
	
	
	askStatusTimer->start(1 * 1000, true);
	
	//wDialog = new WaitingDialog();
}

WorkStationGroup::~WorkStationGroup()
{
	delete tickTimer;
	/*
	if (wDialog != NULL)
		delete wDialog;
	*/
}

/// Would delete all workstations
void WorkStationGroup::deleteAll()
{
	computers.clear();
	qDebug("WorkStationGroup::deleteAll() - All items deleted");
	
}


void WorkStationGroup::askStatus()
{
	//	
	MainWindow *main = static_cast<MainWindow *>(qApp->mainWidget());
	
	/*m_time = QTime::currentTime();
	int secs = m_time.second();
	*/
	// do we have to check status?
	if (main == NULL )
		return;
	if (main->getAskStatus() ){
		statusAll();
	}
	int time = main->getAskStatusTime();
	qDebug("Calling askStatus() %d seconds", time);
	askStatusTimer->start(time * 1000, true);
	
}


void WorkStationGroup::statusAll()
{
	WorkStationListIterator itr(computers);
	for (itr.toFirst(); itr.current(); ++itr){
		//qDebug ("WorkStationGroup::blockAll() blocking workstation: %d", itr.current()->getId());
		itr.current()->status();
	}
}

// returns the ID in which the WorkStation was inserted
int WorkStationGroup::addStation(QString IP, QString name, QString mac)
{
	WorkStation *ws;
	Q_UINT8 nextId;
	
	if ( findHost(IP) != 0 ) {
		// Already inserted
		//qDebug("WorkStationGroup::addStation() IP " + IP + " already inserted");
		return -1;
	}
	
	nextId = computers.count();
	// TODO substitue 10000 by the port
	ws = new WorkStation(this, IP, IP, nextId);
	ws->setName(name);
	ws->setMac(mac);
	connect (tickTimer, SIGNAL(timeout()),
		 ws, SLOT(updateTimer()));

	// Doing SIGNAL forwarding 
	connect (ws, SIGNAL(wsTimeChanged(QString, long )),
		this, SIGNAL(updateView(QString, long)));
	connect (ws, SIGNAL(wsConnError(QString , QString)),
		 this, SIGNAL(wsSocketErrorSignal(QString, QString )) );
	connect (ws, SIGNAL(wsStatusChanged(QString, int )),
		 this, SIGNAL(wsStatusChangedSignal(QString, int ) ) );
	connect (ws, SIGNAL(userChanged(const QString&, const QString& )),
		 this, SIGNAL(userChangedSignal(const QString&, const QString& )) );
	connect (ws, SIGNAL(loginUserChanged(const QString&, const QString& )),
		 this, SIGNAL(loginUserChangedSignal(const QString&, const QString& ) ) );
	
	computers.append(ws);
	
	// want to know if we can connect
	ws->status();
	
	return nextId;

}

/// \return the a pointer to the WorkStation to operate with.
/// Now it does it with a list iteration, but other methods would 
/// preferred
WorkStation * WorkStationGroup::findHost(QString host)
{
	WorkStationListIterator itr(computers);
	//qDebug(tr("WorkStationGroup::findHost() looking for host: " + host));
	for (itr.toFirst(); itr.current(); ++itr){		
		//qDebug("WorkStationGroup::find  - getHostIP() = " + itr.current()->getHostIP() );
		
		if (itr.current()->getHostIP() == host){
			return itr.current();
		}
	}
	return 0;
		
}

void WorkStationGroup::unblockAll()
{
	WorkStationListIterator itr(computers);
	for (itr.toFirst(); itr.current(); ++itr){
		//itr.current()->unblockStation();
		unblockStation(itr.current()->getHostIP());
	}
}

void WorkStationGroup::shutdownAll()
{
	WorkStationListIterator itr(computers);
	for (itr.toFirst(); itr.current(); ++itr){
		shutdownStation(itr.current()->getHostIP());
	}
}


void WorkStationGroup::blockAll()
{
		
	WorkStationListIterator itr(computers);
	for (itr.toFirst(); itr.current(); ++itr){
		//qDebug ("WorkStationGroup::blockAll() blocking workstation: %d", itr.current()->getId());
		blockStation(itr.current()->getHostIP());
		//itr.current()->unblockStation();
	}
	
}

bool WorkStationGroup::save(const QString & fileName, long seconds)
{
	QDomDocument xmlDoc("Test");

	QDomElement root = xmlDoc.createElement("configuration");
	xmlDoc.appendChild(root);
	
	QDomElement workstationList = xmlDoc.createElement("workstation_list");
	root.appendChild(workstationList);

	WorkStationListIterator itr(computers);
	for (itr.toFirst(); itr.current(); ++itr) {
		QDomElement workstation = xmlDoc.createElement("workstation");
		workstation.setAttribute("ip", itr.current()->getHostIP());
    
		QDomElement hostName = xmlDoc.createElement("hostname");
		hostName.appendChild(xmlDoc.createTextNode(itr.current()->getHostName()));

		QDomElement mac = xmlDoc.createElement("mac");
		mac.appendChild(xmlDoc.createTextNode(itr.current()->getMac()));
    
		workstation.appendChild(hostName);
		workstation.appendChild(mac);
    
		workstationList.appendChild(workstation);
	}
	
	QDomElement session = xmlDoc.createElement("session");
	root.appendChild(session);
	
	QDomElement initialTime = xmlDoc.createElement("initial_time");
	initialTime.setAttribute("seconds", seconds);
	session.appendChild(initialTime);

	// Save initial session time
//	QDomElement timeRoot = xmlDoc.createElement("initial_time");
//	xmlDoc.appendChild(timeRoot);
//	QDomElement initialTime = xmlDoc.createElement("seconds");
//	initialTime.setAttribute("number", 1000);
//	timeRoot.appendChild(initialTime);

//	QDomElement root = xmlDoc.createElement("workstation_list");
//	xmlDoc.appendChild(root);

//	WorkStationListIterator itr(computers);
//	for (itr.toFirst(); itr.current(); ++itr) {
//		printf("hola");
//		QDomElement workstation = xmlDoc.createElement("workstation");
//		workstation.setAttribute("ip", itr.current()->getHostIP());
//    
//		QDomElement hostName = xmlDoc.createElement("hostname");
//		hostName.appendChild(xmlDoc.createTextNode(itr.current()->getHostName()));
//
//		QDomElement mac = xmlDoc.createElement("mac");
//		mac.appendChild(xmlDoc.createTextNode(itr.current()->getMac()));
//    
//		workstation.appendChild(hostName);
//		workstation.appendChild(mac);
//    
//		root.appendChild(workstation);
//	}


	//xmlDoc.appendChild(root);
	// QDomElement time = xmlDoc.createElement("

	QFile f(fileName);
	if(!f.open(IO_WriteOnly)) {
		return false;
	}

	QTextStream data(&f);
	data << xmlDoc.toString();

	f.close();

	return true;
}


bool WorkStationGroup::load(const QString & fileName, StationList *stationList, long &seconds)
{
	QDomDocument xmlDoc;
	QString ip;
	QString hostname;
	QString mac;
  
	QFile f(fileName);
	if(!f.open(IO_ReadOnly)) {
		return false;
	}
 
	xmlDoc.setContent(&f);
	f.close();
 	
	
	QDomElement root = xmlDoc.documentElement();

	QDomElement workstationList = root.firstChild().toElement();
	QDomElement workstation = workstationList.firstChild().toElement();
	//QDomElement workstation = root.nextSibling().toElement();
	while(!workstation.isNull()) {
		QDomElement workstationChild = workstation.firstChild().toElement();
		ip = workstation.attribute("ip");    
		qDebug ("ip: " + ip );
    
		while(!workstationChild.isNull()) {
			if (workstationChild.tagName() == "mac") {
				mac = workstationChild.text();    
				qDebug("mac: " + mac);
			}
			else if (workstationChild.tagName() == "hostname") {
				hostname = workstationChild.text();    
				qDebug("hostname: " + hostname );
			}
			workstationChild = workstationChild.nextSibling().toElement();
		}
		addStation(ip, hostname, mac);
		workstation = workstation.nextSibling().toElement();
		//QListViewItem *element = new QListViewItem(stationList, "", ip, hostname);
		stationList->addHostView(ip, hostname);
	}	

	QDomElement session = workstationList.nextSibling().toElement();
	QDomElement initialTime = session.firstChild().toElement();
	QString secondsString = initialTime.attribute("seconds");
	seconds = secondsString.toInt();
	qDebug("seconds: %d", seconds);	

	return true;
}

/// block the station with QString::host
void WorkStationGroup::blockStation(QString host)
{
	WorkStation *temp;
	
	temp = findHost(host);
	if (temp != 0){
		temp->blockStation();
		emit updateView(host, -2);
	}
	else{
		qDebug("WorkStationGroup::blockStation(). findHost did not find anything");
	}
	
}


int WorkStationGroup::getState(const QString &host)
{
	WorkStation *temp;
	
	temp = findHost(host);
	
	if (temp != 0){
		return temp->getState();
		
	}
	else
		return -1;
}

QString WorkStationGroup::getUserFromHost(const QString &host)
{
	WorkStation *temp;
	
	temp = findHost(host);
	
	if (temp != 0){
		return temp->getUser();
		
	}
	else
		return "";
	
	
}


/// unblock the station id
void WorkStationGroup::unblockStation(QString host)
{
	WorkStation *temp;
	
	temp = findHost(host);
	if (temp != 0){
		temp->unblockStation();
		emit updateView(host, -2);
	}
	else{
		qDebug("WorkStationGroup::unblockStation(). findHost did not find anything");
	}
}

/// shuts down the station id
void WorkStationGroup::shutdownStation(QString host)
{
	WorkStation *temp;
	
	temp = findHost(host);
	if (temp != 0){
		temp->shutdownStation();
		emit updateView(host, -2);
	}
	else{
		qDebug("WorkStationGroup::shutdownStation(). findHost did not find anything");
	}
}


bool WorkStationGroup::getLoginUser(QString host)
{
	WorkStation *temp;
	
	temp = findHost(host);
	if (temp != 0){
		temp->user();
	}
	else{
		qDebug("WorkStationGroup::unblockStation(). findHost did not find anything");
	}
}



void WorkStationGroup::startTimerSession(const QString &host, long seconds, QString user, bool reset)
{
	WorkStation *ws;
	
	
	ws = findHost(host);
	if (ws != 0){
		if (!reset){
			qDebug(tr("WorkStationGroup::startTimerSession() - host: %1, user: %2, secs: %3").arg(host)
				.arg(user).arg(seconds) );
			ws->stopSession();
			ws->setUser(user);
			ws->startSession(seconds);
		}
		else{
			// Should disable the askStatus ?
			int rc;
			waitingWS = new WorkStation(this, host, host, 0);
			waitingWS->endSession();
			connect( waitingWS, SIGNAL(wsConnError(QString , QString )),
				 this, SLOT(continueWaiting())) ;
			connect( waitingWS, SIGNAL(wsStatusChanged(QString, int ) ),
				 this, SLOT(killDialog())) ;
			//waitingWS->status();
			waitingTimer->start(2000, true);
			
			
			// TODO adjust the seconds for the timeout. 30s is ok?
			waitingTimeoutTimer->start(30 * 1000, true);
			
			// We need to wait until it restart.
			//ws->endSession();
			wDialog = new WaitingDialog();
			
			rc = wDialog->exec();
			
			switch(rc){
				case 0:   // Cancel pressed	
					break;
					
				case 1:   //Station found
					waitingTimer->stop();
					ws->stopSession();
					ws->setUser(user);
					ws->startSession(seconds);
					break;
					
				case 2:  // Dialog Timeout. Showing error
					QMessageBox::warning(0, tr("Warning"), 
							tr("The workstation did timeout. This means that it "
							"might have some problems.\nPlease, check workstation %1 has "
									"no problems").arg(host),
							tr("Ok") );
					break;
					
			}
			waitingTimer->stop();
			delete wDialog;
			delete waitingWS;
		}
	}
	else{
		qDebug("WorkStationGroup::unblockStation(). findHost did not find anything");
	}
}


void WorkStationGroup::continueWaiting()
{
	waitingWS->status();
	waitingTimer->stop();
	waitingTimer->start(5 * 1000, true);
}

void WorkStationGroup::killDialog()
{
	waitingTimer->stop();
	qDebug("Stopping waitingTimer");
	wDialog->close(1);
	waitingTimeoutTimer->stop();
}

void WorkStationGroup::killTimeoutDialog()
{
	waitingTimer->stop();
	qDebug("Stopping waitingTimer");
	wDialog->close(2);
	waitingTimeoutTimer->stop();
}



/// Would find a host by it's IP address
bool WorkStationGroup::deleteHost(QString host)
{
	WorkStation *elem;
	bool rc;
	
	elem = findHost(host);
	if (elem == 0 )
		return false;
	
	rc = computers.remove(elem);
	
	if (rc){
		emit workstationDeleted(host);
		return true;
	}
	else 
		return false;	
}

