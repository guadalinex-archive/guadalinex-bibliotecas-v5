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
 
 //
 // $Id$
 // $Author$
 
#include <qgroupbox.h> 
#include <qlabel.h>
#include <qlineedit.h>
#include <qcheckbox.h> 
#include <qpushbutton.h>
#include <qtoolbutton.h>
#include <qwhatsthis.h>
#include <qfontdialog.h>
#include <qfont.h>
#include <qstring.h>
#include <qfiledialog.h>
#include <qslider.h>
#include <qlcdnumber.h>

#include "configurationdialog.h"
#include "mlog/output.h"
#include "mlog/layout.h"

using namespace mlog;

ConfigurationDialog::ConfigurationDialog(QWidget *parent, const char *name )
	: ConfigurationDialogBase(parent, name)
{
	controlPortLabel->setText(tr("Control Port"));
	// I need to set the whats this here
	notifyPortLabel->setText(tr("Notification Port"));
	
	clientGroupBox->setTitle(tr("Client Configuration"));
	
	// right now this is a future enhancement
	notifyPortEdit->setEnabled(false);
	helpButton->setEnabled(false);
	
	logGroupBox->setTitle(tr("Logging Configuration"));
	
	logFileLabel->setText(tr("Log file"));
	//logFileButton->
	
	//fontEdit->setEnabled(FALSE);
	fontEdit->setPaletteBackgroundColor(this->paletteBackgroundColor());
	fontEdit->setReadOnly(TRUE);
	
	fontListViewLabel->setText(tr("List font"));
	fontButton->setText(tr("&Choose"));
	fontBox->setTitle(tr("Fonts"));
	connect(fontButton, SIGNAL(clicked()), 
		this, SLOT(selectFont()) );
	
	askCloseCheckbox->setText(tr("Ask confirmation to close the application"));
	QWhatsThis::add(controlPortLabel, tr("This is the port in which the clients are running the medusa client control program"));
	QWhatsThis::add(notifyPortLabel, tr("This is the port in which the clients are running the medusa client notification program"));
	QWhatsThis::add(askCloseCheckbox, tr("Medusa needs to be running at all times in order to control the clients. This "
			"enables asking for confirmation to close the application"));
	QWhatsThis::add(logFileLabel, tr("This specify the file on which medusa would log every action"));
	
	connect( logFileButton, SIGNAL(clicked()), this, SLOT(selectLogFile()) );
	
	miscBox->setTitle(tr("Refresh Status"));
	askStatusBox->setText(tr("Periodically ask for status on all workstations"));
	//askStatusSlider->setEnabled(FALSE);
	//askStatusLCD->setEnabled(FALSE);
	askStatusLabel->setText(tr("seconds"));
	
	connect( askStatusSlider, SIGNAL(valueChanged(int )), 
		 askStatusLCD, SLOT(display(int)));
	askStatusLCD->display(askStatusSlider->value());
	
	//configFont = QString::null;
	
}

/// set configuration font and set textEdit appropiately
void ConfigurationDialog::setConfigFont(QFont font)
{
	
	_font = font;
	//configFont = font.toString();;
	//fontEdit->setText(font);
	fontEdit->setText("Dolor Ipsum Est");
	fontEdit->setFont(_font);
	
}

QFont ConfigurationDialog::getConfigFont()
{
	return _font;
}
		
	

void ConfigurationDialog::selectFont()
{
	bool ok;
	QFont font;
	font.fromString( configFont );
		
	_font = QFontDialog::getFont(&ok, _font, this);		
	if(ok)
		fontEdit->setFont(_font);

}


void ConfigurationDialog::selectLogFile()
{
	extern File station_log;
	extern Layout datetime_layout;

	QString fileName = QFileDialog::getSaveFileName(".", "*.log", this);
	qDebug ("Filename: " + fileName );
	if (fileName != "" ){
		logFileEdit->setText(fileName);
		station_log.close();
		station_log.assignFile(fileName);
		station_log.assignLayout(datetime_layout);
	}
}


