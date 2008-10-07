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
#ifndef WAITINGDIALOG_H
#define WAITINGDIALOG_H

#include "waitingdialogbase.h"

class QTimer;

/**
@author Jesús Roncero
*/
class WaitingDialog : public WaitingDialogBase
{
	Q_OBJECT
public:
	WaitingDialog(QWidget *parent = 0, const char *name = 0);
	void close(int i);

//	~WaitingDialog();
	
public slots:
	void advanceBar();
	
private:
	QTimer *progressTimer;

};

#endif
