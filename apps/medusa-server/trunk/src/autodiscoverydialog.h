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
 
 // $Id$
 // $Author$
#ifndef AUTODISCOVERYDIALOG_H
#define AUTODISCOVERYDIALOG_H

//#include <qptrlist.h>

#include "autodiscoverydialogbase.h"
#include "workstationgroup.h"


//typedef QPtrList<WorkStation> WorkStationList;
//typedef QPtrListIterator<WorkStation> WorkStationListIterator;



class WorkStation;
/**
This is the class for adding new workstation automagically

@author Jesús Roncero
*/
class AutoDiscoveryDialog : public AutoDiscoveryDialogBase
{
	Q_OBJECT
public:
	AutoDiscoveryDialog(QWidget *parent = 0, const char *name = 0);
	~AutoDiscoveryDialog();

	
signals:
	void newStation(QString host);

private slots:
	void startSearchSlot();	
	void stationFound(QString host, int status);
	void stationNotFound(QString host, QString err);
	void stopSearchSlot();
	void changedStartEdit1(const QString& text);
	void changedStartEdit2(const QString& text);
	void changedStartEdit3(const QString& text);
	void changedStartEdit4(const QString& text);
	void changedEndEdit1(const QString& text);
	void changedEndEdit2(const QString& text);
	void changedEndEdit3(const QString& text);
	void changedEndEdit4(const QString& text);
	void cancelSearchSlot();
private:
	bool eventFilter(QObject *target, QEvent *event);
	void setNextFocus(QObject *target);
	bool started;
	unsigned maxNumber;
	bool continueSearch;
	
	WorkStationList testedComputers;
	
};

#endif
