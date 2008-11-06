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
 
 // $Id: protocol.h 209 2004-11-18 14:13:05Z rmartin $
 // $Author: rmartin $
 
#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <qstring.h>

/**
This is the base file for defining the medusa protocol.

Basic usage: 
	sendInstruction( Protocol::startCMD() )
	
Now it is a class which return a QString, but the idea is that it could be expanded
in the future to check for XML, etc

@author Jesús Roncero
*/
class Protocol{
public:
	Protocol();

	~Protocol();
	
	enum ProtocolName {
		StartCommand,
		StopCommand,
		StatusCommand,
		UserCommand,
		EndSessionCommand
	};
	
	QString getCommand(int cmd);
	
	QString startCMD();
	QString statusCMD();
	QString stopCMD();

	QString start;
	QString stop;
	QString status;	
	QString user;
	QString endSession;
	
};

	



#endif
