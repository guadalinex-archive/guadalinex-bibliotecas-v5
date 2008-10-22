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

#include <qaction.h>
#include <qapplication.h>
#include <qcombobox.h>
#include <qfiledialog.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qmenubar.h>
#include <qlistview.h>
#include <qmessagebox.h>
#include <qpopupmenu.h>
#include <qsettings.h>
#include <qstatusbar.h>
#include <qcheckbox.h>
#include <qdatetimeedit.h>
#include <qfont.h>
#include <qcolor.h>
#include <qslider.h>
#include <stdlib.h>
#include <iostream>

#include "addhostdialog.h"
#include "edithostdialog.h"
#include "configurationdialog.h"
#include "mainwindow.h"
#include "stationlist.h"
#include "workstation.h"
#include "runningwarning.h"
#include "counterdialog.h"
#include "autodiscoverydialog.h"
#include "osd.h"
#include "mlog/layout.h"
#include "mlog/output.h"

using namespace mlog;
using namespace std;


// Constructor
//
// 
MainWindow::MainWindow(QWidget * parent, const char *name)
:QMainWindow(parent, name)
{
	stationlist = new StationList(this, "prueba");
	setCentralWidget(stationlist);
	
	//defaults
	addHostDialog = 0;
	configDialog = 0;
	controlPort = 10000;
	notifyPort = 10001;
	initialSessionSeconds = 3600; 

	//listFont.fromString( "" );
	
	askClosing = true;
	askStatus = true;

	createActions();
	createMenus();
	createToolBars();
	createStatusBar();
	logFileName = "" ;

	readSettings();

	appTitle = tr("Medusa");

	setCaption(appTitle);
	setIcon(QPixmap::fromMimeSource("icon.png"));

	fileFilters = tr("files (*.md)");
	modified = false;
	
	connect ( &wsGroup, SIGNAL(updateView(QString, long)),
		   this, SLOT(updateView(QString , long )) );
	// Should updateViewError be mixed with updateView ? TODO
	connect ( &wsGroup, SIGNAL(wsSocketErrorSignal(QString, QString )),
		   this, SLOT(updateViewError(QString , QString)) );
	connect ( &wsGroup, SIGNAL(wsStatusChangedSignal(QString, int )),
		   this, SLOT(updateViewStatus(QString, int)) );
	connect ( &wsGroup, SIGNAL(userChangedSignal(const QString&, const QString& )),
		   this, SLOT(updateViewUser(const QString&, const QString&)) );
	connect ( &wsGroup, SIGNAL(loginUserChangedSignal(const QString&, const QString& )),
		   this, SLOT(updateViewLoginUser(const QString&, const QString&)) );
	   
	stationlist->setFont(listFont);
	
	osd = new OSDWidget ("Medusa", this);
	QColor a(205, 38, 38);
	QColor b(255,255,255);
	osd->setBackgroundColor(a);
	osd->setTextColor(b);
	
	system("/usr/sbin/generate-medusa-conf");
	loadFile("/etc/medusa.conf");
//	// loading last configurationdialog
	if ( (int) recentFiles.size() > 0 ){
		qDebug ("recentfiles: %d", (int) recentFiles.size() );
		qDebug (recentFiles[0]);
		//loadFile(recentFiles[0]);
		openRecentFile(0);
		//wsGroup.statusAll();
	}
	
}


void MainWindow::createActions()
{
	newAct = new QAction(tr("&New Configuration"), tr("Ctrl+N"), this);
	newAct->setIconSet(QPixmap::fromMimeSource("new.png"));
	newAct->setStatusTip(tr("Create a new configuration"));
	connect(newAct, SIGNAL(activated()), this, SLOT(newFile()));

	openAct = new QAction(tr("&Open Configuration..."), tr("Ctrl+O"), this);
	openAct->setIconSet(QPixmap::fromMimeSource("open.png"));
	openAct->setStatusTip(tr("Open an existing configuration"));
	connect(openAct, SIGNAL(activated()), this, SLOT(open()));

	saveAct = new QAction(tr("&Save Configuration"), tr("Ctrl+S"), this);
	saveAct->setIconSet(QPixmap::fromMimeSource("save.png"));
	saveAct->setStatusTip(tr("Save the configuration to disk"));
	connect(saveAct, SIGNAL(activated()), this, SLOT(save()));

	saveAsAct = new QAction(tr("Save Configuration &As..."), 0, this);
	saveAsAct->setStatusTip(tr("Save the actual configuration under a new "
				   "name"));
	connect(saveAsAct, SIGNAL(activated()), this, SLOT(saveAs()));

	exitAct = new QAction(tr("E&xit"), tr("Ctrl+Q"), this);
	exitAct->setStatusTip(tr("Exit the application"));
	connect(exitAct, SIGNAL(activated()), this, SLOT(close()));
	
	addHostAct = new QAction(tr("&Add Host"), tr("Ctrl+A"), this);
	addHostAct->setStatusTip(tr("Add a host"));
	addHostAct->setIconSet(QPixmap::fromMimeSource("address_next_move_add_insert.png"));
	connect(addHostAct, SIGNAL(activated()), this, SLOT(addHost()));
	
	editHostAct = new QAction(tr("&Edit Host"), tr("Ctrl+E"), this);
	editHostAct->setStatusTip(tr("Edit selected host"));
	editHostAct->setIconSet(QPixmap::fromMimeSource("address_edit.png"));
	connect(editHostAct, SIGNAL(activated()), this, SLOT(editHost()) );
	
	deleteHostAct = new QAction(tr("&Delete Host"), tr("Ctrl+D"), this);
	deleteHostAct->setStatusTip(tr("Delete selected host"));
	deleteHostAct->setIconSet(QPixmap::fromMimeSource("address_delete.png"));
	connect(deleteHostAct, SIGNAL(activated()), this, SLOT(deleteHost()) );
	
	
	blockAllAct = new QAction(tr("&Block All Hosts"), tr("Ctrl+B"), this);
	blockAllAct->setStatusTip(tr("Block all the workstations at once"));
	blockAllAct->setIconSet(QPixmap::fromMimeSource("error_x.png"));
	connect(blockAllAct, SIGNAL(activated()), this, SLOT(blockAll()) );
	
	blockSelectedAct = new QAction(tr("&Block Selected Host"), tr("Ctrl+K"), this);
	blockSelectedAct->setStatusTip(tr("Block the selected workstations at once"));
	blockSelectedAct->setIconSet(QPixmap::fromMimeSource("circle_red.png"));
	connect(blockSelectedAct, SIGNAL(activated()), this, SLOT(blockSelectedSlot()) );
	
	unblockAllAct = new QAction(tr("&Unblock All Hosts"), tr("Ctrl+U"), this);
	unblockAllAct->setStatusTip(tr("Unblock all the workstations at once"));
	unblockAllAct->setIconSet(QPixmap::fromMimeSource("circle_green.png"));
	connect(unblockAllAct, SIGNAL(activated()), this, SLOT(unblockAll()) );
	
	shutdownAllAct = new QAction(tr("&Shutdown All Hosts"), tr("Ctrl+G"), this);
	shutdownAllAct->setStatusTip(tr("Shutdown all the workstations at once"));
	shutdownAllAct->setIconSet(QPixmap::fromMimeSource("system-log-out.png"));
	connect(shutdownAllAct, SIGNAL(activated()), this, SLOT(shutdownAll()) );

	unblockSelectedAct = new QAction(tr("&Unblock selected Host"), tr("Ctrl+L"), this);
	unblockSelectedAct->setStatusTip(tr("Unblock all the workstations at once"));
	unblockSelectedAct->setIconSet(QPixmap::fromMimeSource("circle_blue.png"));
	connect(unblockSelectedAct, SIGNAL(activated()), this, SLOT(unblockSelectedSlot()) );

	shutdownSelectedAct = new QAction(tr("&Shutdown selected Host"), tr("Ctrl+F"), this);
	shutdownSelectedAct->setStatusTip(tr("Shutdown just selected workstations"));
	shutdownSelectedAct->setIconSet(QPixmap::fromMimeSource("xscreensaver.png"));
	connect(shutdownSelectedAct, SIGNAL(activated()), this, SLOT(shutdownSelectedSlot()) );
	
	setTimerAct  = new QAction(tr("&Start new session on selected Host"), tr("Ctrl+T"), this);
	setTimerAct->setStatusTip(tr("Start a session for a new user"));
	setTimerAct->setIconSet(QPixmap::fromMimeSource("clock.png"));
	connect( setTimerAct, SIGNAL(activated()), this, SLOT(activateSelectedHost()) );
	
	/*
	getUserAct = new QAction(tr("&Get login User"), tr("Ctrl+U"), this);
	getUserAct->setStatusTip(tr("Get the log in user on the client"));
	connect( getUserAct, SIGNAL(activated()), this, SLOT(getLoginUser()) );
	*/
	
	autoDisAct = new QAction(tr("&Auto discovery"), tr("Ctrl+V"), this);
	autoDisAct->setStatusTip(tr("Try to discover all possible clients on the network")); 
	autoDisAct->setIconSet(QPixmap::fromMimeSource("light_bulb.png"));
	connect ( autoDisAct, SIGNAL(activated()), this, SLOT(autoDiscovery() ) );
	
	editSetAct = new QAction(tr("&Edit Settings"), tr("Ctrl+P"), this);
	editSetAct->setStatusTip(tr("Edit current settings for this list of workstations"));
	editSetAct->setIconSet(QPixmap::fromMimeSource("tabs.png"));
	connect(editSetAct, SIGNAL(activated()), this, SLOT(editSettings()) );
		

	/*
	findAct = new QAction(tr("&Find..."), tr("Ctrl+F"), this);
	findAct->setIconSet(QPixmap::fromMimeSource("find.png"));
	findAct->setStatusTip(tr("Find"));
	connect(findAct, SIGNAL(activated()), this, SLOT(find()));
	*/

	aboutAct = new QAction(tr("&About Medusa"), 0, this);
	aboutAct->setStatusTip(tr("Show the application's About box"));
	connect(aboutAct, SIGNAL(activated()), this, SLOT(about()));

	aboutQtAct = new QAction(tr("About &Qt"), 0, this);
	aboutQtAct->setStatusTip(tr("Show the Qt library's About box"));
	connect(aboutQtAct, SIGNAL(activated()), qApp, SLOT(aboutQt()));
}


/// \brief Create main menues
void MainWindow::createMenus()
{
	fileMenu = new QPopupMenu(this);
	newAct->addTo(fileMenu);
	openAct->addTo(fileMenu);
	saveAct->addTo(fileMenu);
	saveAsAct->addTo(fileMenu);
	fileMenu->insertSeparator();
	exitAct->addTo(fileMenu);

	for (int i = 0; i < MaxRecentFiles; ++i)
		recentFileIds[i] = -1;
	
	hostsMenu = new QPopupMenu(this);
	addHostAct->addTo(hostsMenu); // 4 remve ADRIAN
	editHostAct->addTo(hostsMenu);
	deleteHostAct->addTo(hostsMenu);	
	
	
	actionsMenu = new QPopupMenu(this);
	setTimerAct->addTo(actionsMenu);
	blockAllAct->addTo(actionsMenu);
	unblockAllAct->addTo(actionsMenu);
	blockSelectedAct->addTo(actionsMenu);
	unblockSelectedAct->addTo(actionsMenu);
	shutdownSelectedAct->addTo(actionsMenu);
	shutdownAllAct->addTo(actionsMenu);
	//getUserAct->addTo(actionsMenu);
	

	optionsMenu = new QPopupMenu(this);
	autoDisAct->addTo(optionsMenu);
	editSetAct->addTo(optionsMenu);
	
	helpMenu = new QPopupMenu(this);
	aboutAct->addTo(helpMenu);
	aboutQtAct->addTo(helpMenu);

	menuBar()->insertItem(tr("&File"), fileMenu);
	//menuBar()->insertItem(tr("&Edit"), editMenu);
	menuBar()->insertItem(tr("&Hosts"), hostsMenu);
	menuBar()->insertItem(tr("&Actions"), actionsMenu);
	menuBar()->insertItem(tr("&Options"), optionsMenu);
	menuBar()->insertSeparator();
	menuBar()->insertItem(tr("&Help"), helpMenu);
}

/// \brief Create main context menues
void MainWindow::contextMenuEvent(QContextMenuEvent * event)
{
	QPopupMenu contextMenu(this);

	setTimerAct->addTo(&contextMenu);	
	blockSelectedAct->addTo(&contextMenu);
	unblockSelectedAct->addTo(&contextMenu);
	shutdownSelectedAct->addTo(&contextMenu);
	contextMenu.insertSeparator();
	editHostAct->addTo(&contextMenu);
	deleteHostAct->addTo(&contextMenu);	
	

	contextMenu.exec(event->globalPos());
}

void MainWindow::createToolBars()
{
	fileToolBar = new QToolBar(tr("File"), this);
	newAct->addTo(fileToolBar);
	openAct->addTo(fileToolBar);
	saveAct->addTo(fileToolBar);
	
	hostToolBar = new QToolBar(tr("Hosts"), this);
	addHostAct->addTo(hostToolBar);
	editHostAct->addTo(hostToolBar);
	deleteHostAct->addTo(hostToolBar);
	
	actionToolBar = new QToolBar(tr("Actions"), this);
	setTimerAct->addTo(actionToolBar);
	blockAllAct->addTo(actionToolBar);
	unblockAllAct->addTo(actionToolBar);
	blockSelectedAct->addTo(actionToolBar);
	unblockSelectedAct->addTo(actionToolBar);
	shutdownSelectedAct->addTo(actionToolBar);
	shutdownAllAct->addTo(actionToolBar);
	
}

void MainWindow::newFile()
{
	if (maybeSave()) {
		stationlist->clear();
		wsGroup.deleteAll();
		setCurrentFile("");
	}
}

void MainWindow::open()
{
	if (maybeSave()) {
		QString fileName = QFileDialog::getOpenFileName(".", fileFilters, this);
		if (!fileName.isEmpty()) {	
			stationlist->clear();
			wsGroup.deleteAll();
			loadFile(fileName);
		}
		else{
			QMessageBox::warning(this, tr("Filename Not Found"), 
					     tr("The configuration file %1 could not be opened.<br>\n"
						"Make sure it exists or load another one").arg(fileName),
					     tr("Ok") );
		}
	}
}

void MainWindow::loadFile(const QString & fileName)
{
	qDebug ("Trying to load file : " + fileName);
	if (wsGroup.load(fileName, stationlist, initialSessionSeconds)) {
		setCurrentFile(fileName);
		statusBar()->message(tr("Config loaded"), 2000);
		//wsGroup.statusAll();
	} else {
		QMessageBox::warning(this, tr("Filename Not Found"), 
				     tr("The configuration file %1 could not be opened.\n"
					"Make sure it exists or load another one").arg(fileName),
				     tr("Ok") );
		statusBar()->message(tr("File could not be loaded"), 2000);
	}
}

bool MainWindow::save()
{
	if (curFile.isEmpty()) {
		return saveAs();
	} else {
		saveFile(curFile);
		return true;
	}
}

void MainWindow::saveFile(const QString & fileName)
{
	if (wsGroup.save(fileName, initialSessionSeconds)) {
		setCurrentFile(fileName);
		statusBar()->message(tr("Config saved"), 2000);
	} else {
		statusBar()->message(tr("Saving canceled"), 2000);
	}
}

bool MainWindow::saveAs()
{
	QString fileName =
	    QFileDialog::getSaveFileName(".", fileFilters, this);
	if (fileName.isEmpty())
		return false;

	if (QFile::exists(fileName)) {
		int ret = QMessageBox::warning(this, appTitle,
					       tr
					       ("File %1 already exists.\n"
						"Do you want to overwrite it?")
					       .
					       arg(QDir::convertSeparators(fileName)),
					       QMessageBox::Yes | QMessageBox::Default,
					       QMessageBox::No | QMessageBox::Escape);
		if (ret == QMessageBox::No)
			return true;
	}
	if (!fileName.isEmpty())
		saveFile(fileName);
	return true;
}

/// ask if it has to save the configurationdialog
///
/// \return true if it needs to exit
/// \return false if it needs to stay
bool MainWindow::needToSave()
{
	if (maybeSave()) {
		writeSettings();
		//event->accept();
		return true;
	} else {
		//event->ignore();
		return false;
	}
}

void MainWindow::closeEvent(QCloseEvent * event)
{
	if ( askClosing ) {
		RunningWarning *box = new RunningWarning(this);	
		int ret = box->exec();
		if ( ret ) {
			// modifying askClosing
			if (box->dontCheck->isChecked()){
				askClosing = false;
			}
			if (needToSave()){
				event->accept();
			} else {
				event->ignore();
			}
		}else if ( ret == QMessageBox::Cancel ) {
			event->ignore();
		}
		else{
			event->ignore();
		}
		delete box;
	}
        else{
		if (needToSave()){
				event->accept();
		} 
		else {
				event->ignore();
		}	
	}
}

bool MainWindow::maybeSave()
{
	if (modified) {
		int ret = QMessageBox::warning(this, appTitle,
					       tr
					       ("The configuration has been modified.\n"
						"Do you want to save your changes?"),
					       QMessageBox::
					       Yes | QMessageBox::Default,
					       QMessageBox::No,
					       QMessageBox::
					       Cancel | QMessageBox::
					       Escape);
		if (ret == QMessageBox::Yes)
			return save();
		else if (ret == QMessageBox::Cancel)
			return false;
	}
	return true;
}

void MainWindow::setCurrentFile(const QString & fileName)
{
	curFile = fileName;
	modLabel->clear();
	modified = false;

	if (curFile.isEmpty()) {
		setCaption(appTitle);
	} else {
		setCaption(tr("%1 - %2").arg(strippedName(curFile))
			   .arg(appTitle));
		recentFiles.remove(curFile);
		recentFiles.push_front(curFile);
		updateRecentFileItems();
	}
}

QString MainWindow::strippedName(const QString & fullFileName)
{
	return QFileInfo(fullFileName).fileName();
}

void MainWindow::updateRecentFileItems()
{
	while ((int) recentFiles.size() > MaxRecentFiles)
		recentFiles.pop_back();

	for (int i = 0; i < (int) recentFiles.size(); ++i) {
		QString text = tr("&%1 %2").arg(i + 1).arg(strippedName(recentFiles[i]));
		if (recentFileIds[i] == -1) {
			if (i == 0)
				fileMenu->insertSeparator(fileMenu-> count() - 2);
			recentFileIds[i] =fileMenu->insertItem(text, this,
						 SLOT(openRecentFile(int)),
						 0, -1,
						 fileMenu->count() - 2);
			fileMenu->setItemParameter(recentFileIds[i], i);
		} else {
			fileMenu->changeItem(recentFileIds[i], text);
		}
	}
}

void MainWindow::openRecentFile(int param)
{
	if (maybeSave()){
		stationlist->clear();
		wsGroup.deleteAll();
		loadFile(recentFiles[param]);
	}
}

void MainWindow::createStatusBar()
{
	locationLabel = new QLabel("     ", this);
	locationLabel->setAlignment(AlignHCenter);
	locationLabel->setMinimumSize(locationLabel->sizeHint());

	formulaLabel = new QLabel(this);

	modLabel = new QLabel(tr(" MOD "), this);
	modLabel->setAlignment(AlignHCenter);
	modLabel->setMinimumSize(modLabel->sizeHint());
	modLabel->clear();

	statusBar()->addWidget(locationLabel);
	statusBar()->addWidget(formulaLabel, 1);
	statusBar()->addWidget(modLabel);
	
}


/// Would add a new host to the system.
///
/// It would try to add it to the internal group of hosts. If it successes,
/// then it would add it to the View.
/// If not, presenting a QMessgeBox
void MainWindow::addHost()
{	
	int rc;
			
	AddHostDialog dialog (this);
	if (dialog.exec()){
		QString hostStr = dialog.addressEdit->text();
		QString nameStr = dialog.hostEdit->text();
		QString macStr = dialog.macEdit->text();
		// Inserting the workstation
		rc = wsGroup.addStation(hostStr, nameStr, macStr );		
		if (rc == -1 ){
			// That IP Already exists
			QMessageBox::information(this, tr("%1 - Error").arg(appTitle),
					tr("Host %1 already exists. \n").arg(hostStr),
					QMessageBox::Ok | QMessageBox::Default);
			
			return;
		}
		// Adding host to the system	
		if (!stationlist->addHostView(hostStr,nameStr)){
			// this is redundant anyway			
			return;
		}	
		
		configModified();
	}	
}

/// Edit current host
void MainWindow::editHost()
{
	EditHostDialog *dialog = 0;	
	WorkStation *wsHost;
	QString mac;
	QString hostName;
	QString host;
	
	host = stationlist->findSelected();
	//qDebug("MainWindow::editHost() -- editing " + host);	
	if (host != QString::null){
		qDebug("MainWindow::editHost() - searching for host " + host );
		wsHost = wsGroup.findHost(host);
		if (wsHost == 0){
			// nothing found. Shouldn't be here
			return;
		}
		hostName = wsHost->getHostName();
		mac = wsHost->getMac();
		
		dialog = new EditHostDialog(this, "no name", host, hostName, mac);
		dialog->addressEdit->setText(host);
		dialog->macEdit->setText(mac);
		dialog->hostEdit->setText(hostName);
		if (dialog->exec()){
			// Modifying the actual object
			QString newIP = dialog->addressEdit->text();
			QString newHostName = dialog->hostEdit->text();
			QString newMac = dialog->macEdit->text();
			if (host != newIP){
				// We create a new one and delete the old
				// Deleting selected entry
				deleteHost();
				wsGroup.addStation(newIP, newHostName, newMac );
				stationlist->addHostView(newIP, newHostName);
			}
			else{
				// Only modifying the view and the changed text
				wsHost->setMac(newMac);
				wsHost->setName(newHostName);
				stationlist->updateHostView(host, -1, newHostName );
			}
			//wsHost->set	
		}	
	}
	else{	
		showSimpleWarningBox(tr("You need to select a workstation first"));
	}
	if (dialog != 0 )
		delete dialog;	
	
}


void MainWindow::showSimpleWarningBox(const QString &text)
{
	QMessageBox::warning(this, tr("Warning"), 
			     text,
			     tr("Ok") );
}

/// Delete de selected host
void MainWindow::deleteHost()
{
	// We have to find out what is selected.	
	QString host;
		
	host = stationlist->findSelected();	
	if (host != QString::null){
		qDebug("MainWindow::deleteHost() -- deleting " + host );
		//wsGroup.blockStation(host);
		wsGroup.deleteHost(host);
		// Should I do it this way or using the signal mechanism?
		stationlist->deleteHostView(host);
		configModified();
	}
	else{
		showSimpleWarningBox(tr("You need to select a workstation first"));
		//statusBar()->message(tr("Host %1 seems not to be on our list - BUG").
		//		arg(host), 2000);
	}
}



void MainWindow::autoDiscovery()
{
	AutoDiscoveryDialog dialog (this);
	connect( &dialog, SIGNAL(newStation(QString )),
		  this, SLOT(discoveredStation(QString)) );
	dialog.exec();
	
}

/// Function to add a new stations when it's been automagically
/// discovered
void MainWindow::discoveredStation(QString host)
{
	int rc;
	rc = wsGroup.addStation(host, host, tr("mac missing") );
	if (rc == -1 ){
		// That IP Already exists
		statusBar()->message(tr("Host %1 already inserted").arg(host), 2000);	
		return;
	}
	else {
		configModified();
	}	
		// Adding host to the system	
	if (!stationlist->addHostView(host, host)){
		// this is redundant anyway			
		return;
	}
}


bool MainWindow::getAskStatus()
{
	return askStatus;
}

void MainWindow::editSettings()
{
	extern File station_log;
	extern Layout datetime_layout;

	// TODO this shouldn't be created this way but using the pointer and
	// hiding the whole thing for later reuse
	ConfigurationDialog dialog (this);
	dialog.setConfigFont(listFont);
	dialog.askCloseCheckbox->setChecked(askClosing);
	dialog.controlPortEdit->setText(QString::number(controlPort));
	dialog.logFileEdit->setText(logFileName);
	dialog.askStatusBox->setChecked(askStatus);
	dialog.askStatusSlider->setValue(askStatusTime);
	if (dialog.exec()){
		askClosing = dialog.askCloseCheckbox->isChecked();
		controlPort = dialog.controlPortEdit->text().toUInt();
		//qDebug("setting font font: " + dialog.configFont );	
		listFont = dialog.getConfigFont();		
		stationlist->setFont(dialog.getConfigFont());
		logFileName = dialog.logFileEdit->text();
		if (logFileName != "" ) {
			station_log.close();
			station_log.assignFile(logFileName);
			station_log.assignLayout(datetime_layout);
		}
		askStatus = dialog.askStatusBox->isChecked();
		askStatusTime = dialog.askStatusSlider->value();
	}
}


QString MainWindow::getLogFile()
{
	return logFileName;
}

void MainWindow::updateView(QString host, long time)
{
	// update the listview
	QString remainingText;
	int hour, minute, sec, rsec;
	if ( time >= 0 ){
		hour = time /3600 ;
		rsec = time % 3600 ; 
		minute = rsec / 60 ;
		sec = rsec % 60 ;
		
		QTime time = QTime (hour, minute, sec);
		remainingText = time.toString("hh:mm:ss");
		//remainingText = QString(tr("%1:%2:%3")).arg( hour, 2 ).arg(minute, 2).arg(sec, 2);	
	}
	else if ( time == -1 ) {
		remainingText = QString(tr("finished"));
	}
	else if (time == -2 ){
		remainingText = QString(tr(""));
	}
	else {
		remainingText = QString(tr("Error"));
	}
	
	stationlist->updateHostView(host, -1, QString::null, remainingText, QString::null, QString::null, QString::null);
	return;
		
	
}


/// TODO I should include a iterator in the class to avoid creating it
/// everytime I want to use it, or use a generic function
void MainWindow::updateViewError(QString  host, QString msg)
{
	stationlist->updateHostView(host, WorkStation::ERROR, QString::null, QString::null, QString::null, QString::null, msg);
}

void MainWindow::updateViewStatus(QString host, int status)
{
	// also cleaning the comment field
	stationlist->updateHostView(host, status, QString::null, QString::null, QString::null, QString::null, "");
}

void MainWindow::updateViewUser(const QString &host, const QString &user)
{
	stationlist->updateHostView(host, -1, QString::null, QString::null, user, QString::null, QString::null);
		
}

void MainWindow::updateViewLoginUser(const QString &host, const QString &user)
{
	//stationlist->updateHostView(
	stationlist->updateHostView(host, -1, QString::null, QString::null, QString::null, user,  QString::null);
		
}

void MainWindow::blockAll()
{
	//qDebug("Trying to block all workstations");	
	wsGroup.blockAll();
}

void MainWindow::blockSelected()
{
	
}

/// This would start a session on selected host
void MainWindow::activateSelectedHost()
{
	QString host;
	CounterDialog dialog (this, (char *) NULL, initialSessionSeconds);
	QString user;
	//long seconds;

	host = stationlist->findSelected();
	if (host != QString::null){
		//qDebug("State: %d", wsGroup.getState(host));
		int state = wsGroup.getState(host) ;
		if (state == WorkStation::ERROR){
			showSimpleWarningBox(tr("WorkStation %1 seems to be disconnected. Make sure it is connected\n"
					"either by refreshing its state or making visual contact").arg(host));
			//return;
		}
		// Setting the last user
		QString user = wsGroup.getUserFromHost(host);
//		dialog.userEdit->setText(user);
//		dialog.userEdit->selectAll();
		
		qDebug("MainWindow::blockSelected() -- activating Timer on  " + host );
		//wsGroup.blockStation(host);
		if (dialog.exec()){
			// Really start
			//seconds = dialog.getSeconds();	
			if (initialSessionSeconds != dialog.getSeconds()) {
				initialSessionSeconds = dialog.getSeconds();
				configModified();
			}	
			//user = dialog.userEdit->text();
			user = "";
			//qDebug("segundos: %ld", seconds);
			//wsGroup.startTimerSession(host, seconds, user, dialog.resetSessionCheck->isChecked());
			wsGroup.startTimerSession(host, initialSessionSeconds, user, dialog.resetSessionCheck->isChecked());
			
		}
		else{
			qDebug("MainWindow::activateSelectedHost() - not activating timer");
		}
	}
	else{
		showSimpleWarningBox(tr("You need to select a workstation first"));
		//statusBar()->message(tr("Host %1 seems not to be on our list - BUG").
		//		arg(host), 2000);
	}
}


/// Used when block selected workstation is clicked
void MainWindow::blockSelectedSlot()
{
	// We have to find out what is selected. Then
	// act apropiately
	QString host;

	host = stationlist->findSelected();
	//qDebug("para " + temp);
	if (host != QString::null){
		qDebug("MainWindow::blockSelected() -- blocking " + host );
		wsGroup.blockStation(host);
	}
	else{
		showSimpleWarningBox(tr("You need to select a workstation first"));
		//statusBar()->message(tr("Host %1 seems not to be on our list - BUG").
		//		arg(host), 2000);
	}
		
}

void MainWindow::showOSDMsg(const QString &text)
{
	//osd->setText(text);
	osd->showOSD(text);
}


void MainWindow::getLoginUser()
{
	QString host;
	
	host = stationlist->findSelected();
	//osd->showOSD(tr( "Esto es una prueba" ));
	showOSDMsg("Esto es una prueba de una advertencia");
	//osd->setEnabled(true);
	if (host != QString::null){
		wsGroup.getLoginUser(host);
	}
	else{
		statusBar()->message(tr("Host %1 seems not to be on our list - BUG").
				arg(host), 2000);
	}
	
}



void MainWindow::unblockSelectedSlot()
{// We have to find out what is selected. Then
	// act apropiately
	QString host;
	
	host = stationlist->findSelected();
	if (host != QString::null){
		qDebug("MainWindow::unblockSelected() -- unblocking " + host );
		wsGroup.unblockStation(host);
	}
	else{
		showSimpleWarningBox(tr("You need to select a workstation first"));
		//statusBar()->message(tr("Host %1 seems not to be on our list - BUG").
		//		arg(host), 2000);
	}
}

void MainWindow::shutdownSelectedSlot()
{// We have to find out what is selected. Then
	// act apropiately
	QString host;
	
	host = stationlist->findSelected();
	if (host != QString::null){
		qDebug("MainWindow::shutdownSelected() -- shutting down " + host );
		wsGroup.shutdownStation(host);
	}
	else{
		showSimpleWarningBox(tr("You need to select a workstation first"));
		//statusBar()->message(tr("Host %1 seems not to be on our list - BUG").
		//		arg(host), 2000);
	}
}

void MainWindow::unblockAll()
{
	wsGroup.unblockAll();
	
}
	

void MainWindow::shutdownAll()
{
	wsGroup.shutdownAll();
	
}

void MainWindow::about()
{
	QMessageBox::about(this, tr("About Medusa"),
			tr("<h2>Medusa</h2>"
			"<p>Copyright &copy; 2004 Junta de Andalucia"
			"<p> Jess Roncero Franco <br>"
			" Daniel Carri� Reinoso <br>"
			" Coordination: Rafael Mart� de Agar Tirado"
			"<p>Medusa is a small application to remotely block/unblock computers. "
			"Its primary use is in a library or a internet cafe. "
			"Medusa is based on Zeiberbude by Christian T�p<br> " 
 			"                            "
			"<p>Icons by <a href=\"http://phoenity.com\">http://phoenity.com</a> - License Creative Commons. "));
}

void MainWindow::writeSettings()
{
	QSettings settings;
	settings.setPath("terminus-soft", "Md");
	settings.beginGroup("/Medusa");
	settings.writeEntry("/geometry/x", x());
	settings.writeEntry("/geometry/y", y());
	settings.writeEntry("/geometry/width", width());
	settings.writeEntry("/geometry/height", height());
	settings.writeEntry("/askClosing", askClosing);
	settings.writeEntry("/controlPort", controlPort);
	settings.writeEntry("/notifyPort", notifyPort);
	settings.writeEntry("/recentFiles", recentFiles);
	settings.writeEntry("/listFont", listFont.toString());	
	settings.writeEntry("/logFile", logFileName);
	settings.writeEntry("/askStatus", askStatus);
	settings.writeEntry("/askStatusTime", askStatusTime);
	settings.endGroup();
}

void MainWindow::readSettings()
{
	extern File station_log;
	extern Layout datetime_layout;
	
	QSettings settings;
	settings.setPath("terminus-soft", "Md");
	settings.beginGroup("/Medusa");

	int x = settings.readNumEntry("/geometry/x", 100);
	int y = settings.readNumEntry("/geometry/y", 100);
	int w = settings.readNumEntry("/geometry/width", 600);
	int h = settings.readNumEntry("/geometry/height", 500);
	askClosing = settings.readBoolEntry("/askClosing", true);
	controlPort = settings.readNumEntry("/controlPort", 10000);
	notifyPort = settings.readNumEntry("/notifyPort", 10001);
	logFileName  = settings.readEntry("/logFile", "/var/log/medusa.log");
	askStatus = settings.readBoolEntry("/askStatus", true);
	askStatusTime = settings.readNumEntry("/askStatusTime", 13);

	
	if (logFileName != "" ){		
		station_log.close();
		station_log.assignFile(logFileName);
		station_log.assignLayout(datetime_layout);
	}
	

	move(x, y);
	resize(w, h);

	recentFiles = settings.readListEntry("/recentFiles");
	QString strFont = settings.readEntry("/listFont", "Helvetica");
	listFont.fromString(strFont);
	updateRecentFileItems();

	settings.endGroup();
}


void MainWindow::configModified()
{
	modLabel->setText(tr("MOD"));
	modified = true;
}

Q_UINT16 MainWindow::getControlPort()
{
	return controlPort;
}

int MainWindow::getAskStatusTime()
{
	return askStatusTime;	
}
