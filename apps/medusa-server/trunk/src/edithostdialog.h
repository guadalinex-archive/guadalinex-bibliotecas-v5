/***************************************************************************
 *   Copyright (C) 2004 byEmergya, S.C.A.                                   *
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
#ifndef EDITHOSTDIALOG_H
#define EDITHOSTDIALOG_H

#include <addhostdialogbase.h>

/**
@author Jesús Roncero
\class EditHostDialog A class for editing the selected Host
*/
class EditHostDialog : public AddHostDialogBase
{
	Q_OBJECT
public:
	EditHostDialog(QWidget *parent = 0, const char *name = 0, QString _initHost = "",
		       QString _initHostName = "", QString _initMAC = "");
		
	const QString initHost;
	const QString initHostName;
	const QString initMAC;
	
private slots:
	void enableOkButton();

};

#endif
