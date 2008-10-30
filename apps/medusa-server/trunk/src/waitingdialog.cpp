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
#include <qtimer.h>
#include <qlabel.h>
#include <qdialog.h>
  
#include "waitingdialog.h"

WaitingDialog::WaitingDialog(QWidget *parent, const char *name )
	: WaitingDialogBase(parent, name)
{
	progressTimer = new QTimer();
	progressBar->setTotalSteps(0);
	connect( progressTimer, SIGNAL(timeout()), 
		  this, SLOT(advanceBar()) );
	
	progressTimer->start(200, false);
	qDebug("Conectando timer");
	//progressBar->setProgress(0);
	textLabel->setText(tr("Please, wait until the workstation reboots"));
	setCaption(tr("Waiting.."));
}


void WaitingDialog::advanceBar()
{
	progressBar->setProgress(progressBar->progress() + 2);
	
}


void WaitingDialog::close(int i)
{
	this->done(i);
}


//WaitingDialog::~WaitingDialog()
//{
//}


