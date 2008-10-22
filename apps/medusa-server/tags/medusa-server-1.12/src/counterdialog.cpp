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
#include <qpushbutton.h>
#include <qdatetimeedit.h>
#include <qcheckbox.h>
#include <qlabel.h>
#include <qtooltip.h>

#include "counterdialog.h"

CounterDialog::CounterDialog(QWidget *parent, const char *name, long seconds)
	: CounterDialogBase(parent, name)
{
	connect( timeEdit, SIGNAL(valueChanged(const QTime &)), 
		 this, SLOT(timeChanged(const QTime &)) );
	helpButton->setEnabled(false);
	timeLabel->setText(tr("Time"));
	//userLabel->setText(tr("User code"));
	resetSessionCheck->setText(tr("Close last user session"));
	resetSessionCheck->setChecked(true);
	
	this->setCaption(tr("Start new session"));

	/* Setting default 30 minutes */
	//QTime time = QTime(1,0,0);
	
	//timeEdit->setTime(time);
	int hours = seconds / 3600;
	int mins = (seconds - hours * 3600) / 60;
	int secs = (seconds - hours * 3600 - mins * 60); 
	timeEdit->setTime(QTime(hours, mins, secs));
	
	QToolTip::add(timeEdit, tr("Minimum: 10 seconds"));
}


CounterDialog::~CounterDialog()
{}

void CounterDialog::timeChanged(const QTime &time)
{
	hours = time.hour();
	minutes = time.minute();
	seconds = time.second();
	if ( getSeconds() < 10 ){
		okButton->setEnabled(false);
	}
	else{
		okButton->setEnabled(true);
	}
}

long CounterDialog::getSeconds()
{
	long secs;
	secs = (hours * 3600 ) + (minutes * 60) + seconds ;
	
	return secs;
}

