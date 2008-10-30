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
#include <qpixmap.h>
#include <qstring.h>
 
#include "stationlist.h"
#include "workstation.h"



/// Constructor function
StationList::StationList(QWidget *parent, const char *name)
	: QListView(parent, name)
{
	initialized = false;
	createLabels();
	setSelectionMode(QListView::Single);
	setAllColumnsShowFocus( true );
	setColumnAlignment(StationList::IPColumn, Qt::AlignRight);
	setColumnAlignment(StationList::RemainingTimeColumn, Qt::AlignRight);
	
	//it = new QListViewItemIterator( this );
}

void StationList::createLabels(void)
{
	addColumn(tr("S")); // Status
	addColumn(tr("Host IP"));
	addColumn(tr("Host Name"));
	addColumn(tr("Remaining Time"));
	addColumn(tr("User"));
	addColumn(tr("Login User"));
	addColumn(tr("Comments"));
	setResizeMode(LastColumn);
			
}	

/// Find and returns the selected host
///
/// \return QString::hostIP if found
/// \return QString::null if not found
QString StationList::findSelected()
{
	QListViewItem * elem;
		
	elem = selectedItem();			
	if (elem == 0){
		//qDebug("No such element selected");
		return QString::null;
	}
	else{
		//qDebug("Found element");
		return elem->text(StationList::IPColumn);
	}
	
}	

bool StationList::setNotConnectedIcon(QString hostIP)
{
	QListViewItem * elem;
	qDebug("StationList::setNotConnectedIcon looking for elem: " + hostIP);
	
	elem = findItem(hostIP, StationList::IPColumn);
	//elem = findItem(hostIP, 0);
	if (elem != 0 ){
		elem->setPixmap(0,QPixmap::fromMimeSource("web_offline.png"));
		return true;
	}
	return false;
}

/// would update any entry in the selected hostIP .
/// \return  true if something changed
/// \return  false otherwise (if not found too)
bool StationList::updateHostView(QString hostIP, int status, QString hostName, 
				 QString time, QString user, QString loginUser, QString comments)
{
	bool rc;	
	QListViewItem *felement = 0;
	QListViewItemIterator it(this);
	bool found;
	
	rc = false;
	found = false;
	
	while ( it.current() ) {
		felement = it.current();
		if (felement->text(StationList::IPColumn) == hostIP ){	
			found = true;
			break;
		}		
		++it;
	}
	
	if (!found){
		return false;
	}
	else{	
	// found host. Start to change
		if ( status != -1 ){
			switch(status){
				case WorkStation::BLOCKED : 
					//qDebug("StationList::updateHostView() putting RED state on " + hostIP + " state: %d",  status  );
					//felement->setText(StationList::CommentsColumn, "");
					felement->setPixmap(StationList::ActiveIconColumn, QPixmap::fromMimeSource("circle_red.png"));
					break;
				case WorkStation::INACTIVE :
					//qDebug("StationList::updateHostView() putting BLUE state on " + hostIP+ " state:  %d ",  status);
					//felement->setText(StationList::CommentsColumn, "");
					felement->setPixmap(StationList::ActiveIconColumn, QPixmap::fromMimeSource("circle_blue.png"));
					break;
				case WorkStation::ERROR:
					//qDebug("StationList::updateHostView() putting ERROR state on " + hostIP+ " state: %d",  status);
					felement->setPixmap(StationList::ActiveIconColumn, QPixmap::fromMimeSource("web_offline.png"));
					break;
				case WorkStation::CONN1:
					//qDebug("StationList::updateHostView() putting CONN1 state on " + hostIP );
					felement->setPixmap(StationList::ActiveIconColumn, QPixmap::fromMimeSource("conn1.png"));
					break;
				case WorkStation::CONN2:
					//qDebug("StationList::updateHostView() putting CONN2 state on " + hostIP );
					felement->setPixmap(StationList::ActiveIconColumn, QPixmap::fromMimeSource("conn2.png"));
					break;
				case WorkStation::CONN3:
					//qDebug("StationList::updateHostView() putting CONN3 state on " + hostIP );
					felement->setPixmap(StationList::ActiveIconColumn, QPixmap::fromMimeSource("conn3.png"));
					break;
				case WorkStation::CONN4:
					//qDebug("StationList::updateHostView() putting CONN4 state on " + hostIP );
					felement->setPixmap(StationList::ActiveIconColumn, QPixmap::fromMimeSource("conn4.png"));
					break;						
				default:
					//qDebug("StationList::updateHostView() putting undefined state on "+  hostIP+ " state: %d",  status);
					//felement->setText(StationList::CommentsColumn, "");
					felement->setPixmap(StationList::ActiveIconColumn, QPixmap::fromMimeSource("circle_silver.png"));
			}
			rc = true;
		}//if (found){
	
		if ( hostName != QString::null) {
			felement->setText(StationList::HostNameColumn, hostName);	
			rc = true;
		}
	
		if ( time != QString::null) {
			felement->setText(StationList::RemainingTimeColumn, time);
			rc = true;
		}
	
		if ( user != QString::null) {
			felement->setText(StationList::UserColumn, user);
			rc = true;
		}
	
		if ( loginUser != QString::null) {
			felement->setText(StationList::LoggedUserColumn, loginUser);
			rc = true;
		}
	
		if (comments != QString::null) {
			felement->setText(StationList::CommentsColumn, comments);
			rc = true;
		}
	}	
			
	return rc;
} 

/// Function to add a new QListViewItem to the QListView.
bool StationList::addHostView(QString hostIP, QString hostName)
{
	if (findItem(hostIP, StationList::IPColumn) != 0){
		// already inserted
		// Action?
		return false;
		
	}
	//new QListViewItem(this, "", hostIP,  hostName);
	new ColorListViewItem(this, "", hostIP, hostName);
	return true;
}

/// Would delete the host in the hostview
bool StationList::deleteHostView(QString hostIP)
{
	QListViewItem *elem;
	
	elem = findItem(hostIP, StationList::IPColumn);
	
	if (elem != 0 ){
		takeItem(elem);
		return true;
	}
	return false;
	
}

