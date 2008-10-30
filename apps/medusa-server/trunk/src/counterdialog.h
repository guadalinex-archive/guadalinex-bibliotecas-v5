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
#ifndef COUNTERDIALOG_H
#define COUNTERDIALOG_H

#include <counterdialogbase.h>

/**
@author Jesús Roncero
*/
class CounterDialog : public CounterDialogBase
{
  Q_OBJECT
public:
	CounterDialog(QWidget *parent = 0, const char *name = 0);

	~CounterDialog();
	
	long getSeconds();
	
public slots:
	void timeChanged(const QTime &time);
	
private:
	Q_UINT8 hours;
	Q_UINT8 minutes;
	Q_UINT8 seconds;

};

#endif
