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
#include <qlabel.h>
#include <qcheckbox.h>
#include <qpushbutton.h>
 
#include "runningwarning.h"

RunningWarning::RunningWarning(QWidget *parent, const char *name )
		: RunningWarningBase(parent, name)
{
	dontCheck->setText(tr("Don't ask again"));
	warningLabel->setText(tr("All the clients are controlled by leaving this application running. Closing it "
	"would left the clients as they are at this very moment, all countdowns would be cancelled and "
	"they won't be able to be recovered.\n"
	"Are you sure you want to do this?"));
	
	helpButton->setEnabled(false);
}





