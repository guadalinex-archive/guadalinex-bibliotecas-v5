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


#ifndef CONFIGURATIONDIALOG_H
#define CONFIGURATIONDIALOG_H

#include "configurationdialogbase.h"

class QFont;

class ConfigurationDialog : public ConfigurationDialogBase
{
Q_OBJECT
public:
	ConfigurationDialog(QWidget *parent = 0, const char *name = 0);
	//void clearItems();
	void setConfigFont(QFont font);
	QFont getConfigFont();

	QString configFont;	
	
private slots:
	//	void enableOkButton();
	void selectFont();	
	void selectLogFile();
	
private:
	QFont _font;
};

#endif 


