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
 
 //
 // $Id$
 // $Author$
#include <qprogressbar.h>
#include <qpushbutton.h>
#include <qapplication.h>
#include <qvalidator.h>
#include <qlineedit.h>
#include <qhostaddress.h>
#include <qstring.h>
#include <qmessagebox.h>
  
#include "autodiscoverydialog.h"
#include "workstation.h"
#include "mainwindow.h"


AutoDiscoveryDialog::AutoDiscoveryDialog(QWidget *parent, const char *name )
	: AutoDiscoveryDialogBase(parent, name)
{
	started = false;
	connect(searchButton, SIGNAL(clicked()), this, SLOT(startSearchSlot()) );
	connect(stopButton, SIGNAL(clicked()), this, SLOT(stopSearchSlot()) );
	
	QRegExp regExp("\\d{1,3}");
	startEdit1->setValidator(new QRegExpValidator(regExp, this));
	startEdit2->setValidator(new QRegExpValidator(regExp, this));
	startEdit3->setValidator(new QRegExpValidator(regExp, this));
	startEdit4->setValidator(new QRegExpValidator(regExp, this));
	endEdit1->setValidator(new QRegExpValidator(regExp, this));
	endEdit2->setValidator(new QRegExpValidator(regExp, this));
	endEdit3->setValidator(new QRegExpValidator(regExp, this));
	endEdit4->setValidator(new QRegExpValidator(regExp, this));
	connect( startEdit1, SIGNAL( textChanged(const QString&) ), this, SLOT( changedStartEdit1(const QString&) ) );
	connect( startEdit2, SIGNAL( textChanged(const QString&) ), this, SLOT( changedStartEdit2(const QString&) ) );
	connect( startEdit3, SIGNAL( textChanged(const QString&) ), this, SLOT( changedStartEdit3(const QString&) ) );
	connect( startEdit4, SIGNAL( textChanged(const QString&) ), this, SLOT( changedStartEdit4(const QString&) ) );
	connect( endEdit1, SIGNAL( textChanged(const QString&) ), this, SLOT( changedEndEdit1(const QString&) ) );
	connect( endEdit2, SIGNAL( textChanged(const QString&) ), this, SLOT( changedEndEdit2(const QString&) ) );
	connect( endEdit3, SIGNAL( textChanged(const QString&) ), this, SLOT( changedEndEdit3(const QString&) ) );
	connect( endEdit4, SIGNAL( textChanged(const QString&) ), this, SLOT( changedEndEdit4(const QString&) ) );
	
	connect( stopButton, SIGNAL( clicked() ), this, SLOT( cancelSearchSlot()) );
	
	// Registering a custon event filter
	startEdit1->installEventFilter(this);
	startEdit2->installEventFilter(this);
	startEdit3->installEventFilter(this);
	//startEdit4->installEventFilter(this);
	endEdit1->installEventFilter(this);
	endEdit2->installEventFilter(this);
	endEdit3->installEventFilter(this);
	//endEdit4->installEventFilter(this);
	
	// maximun number of hosts to scan
	maxNumber = 1000;
	
	cancelButton->setText(tr("Close"));
	
	// We want the computers to be deleted
	testedComputers.setAutoDelete(true);

	// autodiscovery for SADESI
	startEdit1->setText("192");
	startEdit2->setText("168");
	startEdit3->setText("1");
	startEdit4->setText("1");
	endEdit1->setText("192");
	endEdit2->setText("168");
	endEdit3->setText("1");
	endEdit4->setText("254");
	startEdit1->setFocus();
	
}

AutoDiscoveryDialog::~AutoDiscoveryDialog()
{
	testedComputers.clear();
}

void AutoDiscoveryDialog::cancelSearchSlot()
{
	continueSearch = false;
	searchButton->setEnabled(true);
	testedComputers.clear();
	stopButton->setText(tr("Cancel"));
	progressBar->reset();
}


/// Event filter 
bool AutoDiscoveryDialog::eventFilter(QObject *target, QEvent *event)
{
	/// We capture the Key_Period to go to the next edit
	if ( target == startEdit1 || target == startEdit2 || target == startEdit3 ||
		    target == endEdit1 || target == endEdit2 || target == endEdit3 ) {
		if (event->type() == QEvent::KeyPress) {
			QKeyEvent * keyEvent = (QKeyEvent *) event;
			if (keyEvent->key() == Key_Period) {
				setNextFocus(target);
				return true;
			}
		}
		return QDialog::eventFilter(target, event);
	}
	return true;
}

void AutoDiscoveryDialog::setNextFocus(QObject *target)
{

	if ( target == startEdit1 ){
		startEdit2->setFocus();
		startEdit2->selectAll();
	}
	else if ( target == startEdit2 ){
		if (startEdit2->text() != "" && ! startEdit2->hasSelectedText() ){
			startEdit3->setFocus();
			startEdit3->selectAll();
		}
	}
	else if ( target == startEdit3 ){
		if (startEdit3->text() != "" && ! startEdit3->hasSelectedText() ){
			startEdit4->setFocus();
			startEdit4->selectAll();
		}
	}
	else if ( target == endEdit1 ){
		if (endEdit1->text() != "" && ! endEdit1->hasSelectedText() ){
			endEdit2->setFocus();
			endEdit2->selectAll();
		}
	}
	else if ( target == endEdit2 ){
		if (endEdit2->text() != "" && ! endEdit2->hasSelectedText() ){
			endEdit3->setFocus();
			endEdit3->selectAll();
		}
	}
	else if ( target == endEdit3  ){
		if (endEdit3->text() != "" && ! endEdit3->hasSelectedText() ){
			endEdit4->setFocus();
			endEdit4->selectAll();
		}
	}
	//else if (target == endEdit4 ) {
	//	if (endEdit4->text() != "" && !endEdit
	
}


void AutoDiscoveryDialog::changedStartEdit1(const QString& text)
{	
	if (text.length() == 3){
		startEdit2->setFocus();
		startEdit2->selectAll();
	}
}

void AutoDiscoveryDialog::changedStartEdit2(const QString& text)
{	
	if (text.length() == 3){
		startEdit3->setFocus();
		startEdit3->selectAll();
	}
}

void AutoDiscoveryDialog::changedStartEdit3(const QString& text)
{	
	if (text.length() == 3){
		startEdit4->setFocus();
		startEdit4->selectAll();
	}
}

void AutoDiscoveryDialog::changedStartEdit4(const QString& text)
{	
	if (text.length() == 3){
		endEdit1->setFocus();
		endEdit1->selectAll();
	}
}


void AutoDiscoveryDialog::changedEndEdit1(const QString& text)
{	
	if (text.length() == 3){
		endEdit2->setFocus();
		endEdit2->selectAll();
	}
}

void AutoDiscoveryDialog::changedEndEdit2(const QString& text)
{	
	if (text.length() == 3){
		endEdit3->setFocus();
		endEdit3->selectAll();
	}
}

void AutoDiscoveryDialog::changedEndEdit3(const QString& text)
{	
	if (text.length() == 3){
		endEdit4->setFocus();
		endEdit4->selectAll();
	}
}

void AutoDiscoveryDialog::changedEndEdit4(const QString& text)
{	
	if (text.length() == 3)
		searchButton->setFocus();
}





void AutoDiscoveryDialog::stopSearchSlot()
{
	//MainWindow *main=static_cast<MainWindow *>(qApp()->mainWidget());
	//MainWindow *main = static_cast<MainWindow *>(qApp->mainWidget());
	
	//qDebug("Control Port: %d", main->controlPort);
}

/// searching the net
void AutoDiscoveryDialog::startSearchSlot()
{
	WorkStation *ws;
	QString host;
	
	started = true;
	searchButton->setEnabled(false);
		
	QHostAddress startAddress;
	QHostAddress stopAddress;
	QHostAddress iAddress;
	Q_UINT32 startIP;
	Q_UINT32 endIP;
	Q_UINT32 offsetIP;
	Q_UINT32 i;	
	bool rc;
	
	QString startStrAddress = QString("%1.%2.%3.%4").arg(startEdit1->text()).arg(startEdit2->text())
			.arg(startEdit3->text()).arg(startEdit4->text());
	qDebug ("AutoDiscoveryDialog::startSearchSlot()  startStrAddress = " + startStrAddress) ;
	if (  ! (rc = startAddress.setAddress(startStrAddress))){
		// seems to be a wrong address
		QMessageBox::critical( this, tr("Medusa Error"),
			QString(tr("The start address you typed is ivalid.\n"
				"Please correct it and press start again")));
		searchButton->setEnabled(true);
		return;	
	}
	
	QString endStrAddress = QString("%1.%2.%3.%4").arg(endEdit1->text()).arg(endEdit2->text())
			.arg(endEdit3->text()).arg(endEdit4->text());
	
	if (  ! (rc = stopAddress.setAddress(endStrAddress))){
		// seems to be a wrong address
		QMessageBox::critical( this, tr("Medusa Error"),
			QString(tr("The end address you typed is ivalid.\n"
			"Please correct it and press start again")));
		searchButton->setEnabled(true);	
		return;
	}
	
	
	startIP = startAddress.toIPv4Address();
	endIP = stopAddress.toIPv4Address();
	
	offsetIP = endIP - startIP;
	qDebug ("offsetIP = %u", offsetIP);
	if ( offsetIP <= 0 ){
		QMessageBox::critical( this, tr("Medusa Error"),
			QString(tr("The addresses range you typed are wrong\n"
					"You must introduce a valid range.\n"
					"Example: 192.168.1.1 - 192.168.2.255"
				"Please correct it and press start again")));
		
		searchButton->setEnabled(true);	
		return;
	}
	else if (offsetIP > maxNumber ) {
		int ret = QMessageBox::question(this,
				tr("Medusa Warning"),
				tr("You have selected to scan the network "
				"for more than %1 hosts.\nThis may cause the application to run"
				"very slow or even to hang\n"
						"Are you sure you want to continue?").arg(maxNumber),
				tr("&Yes"), tr("&No"),
				QString::null, 0, 1 ) ;
		if ( ret == 1 ){
			searchButton->setEnabled(true);
			return;
		}
	}
		
	
	progressBar->setTotalSteps(offsetIP );
	
	qDebug("startIP: %u  , endIP: %u ", startIP, endIP);
	qDebug("Total: %u", offsetIP);
	
	continueSearch = true;
	stopButton->setText(tr("Cancel"));
	
	for (i = startIP; i <= endIP ; i++){
		iAddress.setAddress(i);
		QString host = iAddress.toString();
		qDebug("host: " + host);
		ws = new WorkStation(this, host, host, 1);
		testedComputers.append(ws);
		
		connect (ws, SIGNAL(wsStatusChanged(QString, int )),
			 this, SLOT(stationFound(QString, int)) );
		connect (ws, SIGNAL(wsConnError(QString, QString )),
			 this, SLOT(stationNotFound(QString, QString)) );
		
		//ws->status();
		ws->delayStatus( (int) (i - startIP + 1) );
		
		//make it more responsive
		qApp->processEvents();
		
		if (!continueSearch)
			break;
	}
	
}


void AutoDiscoveryDialog::stationFound(QString host, int status)
{
	qDebug("WorkStation: " + host);
	qDebug("Status: %d " , status);
	int p = progressBar->progress();
	progressBar->setProgress(++p);
	
	// we need to emit a signal indicating we found this station
	//if (status == WorkStation::ERROR)
	emit newStation(host);
	if (p >= progressBar->totalSteps() )
		stopButton->setText(tr("Reset"));
	


}


void AutoDiscoveryDialog::stationNotFound(QString host, QString err)
{
	//qDebug("WorkStation not found " + host );	
	int p = progressBar->progress();
	
	progressBar->setProgress(++p);
	if (p >= progressBar->totalSteps() )
		stopButton->setText(tr("Reset"));	
}

