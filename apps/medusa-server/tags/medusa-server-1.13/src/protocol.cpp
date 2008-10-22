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
 
 //
 // $Id: protocol.cpp 218 2005-11-08 21:17:25Z rmartin $
 // $Author: rmartin $
#include <qstring.h>

#include "protocol.h"


Protocol::Protocol()
{
	// Do I need to send a \n at the end?
	//STARTCMD = "<MB><START/></MB>";
	start = "<MD><START/></MD>";
	stop = "<MD><STOP/></MD>";
	status = "<MD><STATUS/></MD>";
	user = "<MD><USER/></MD>";
	endSession = "<MD><ENDSESSION/></MD>";
	shutdown = "<MD><SHUTDOWN/></MD>";
	halfTime= "<MD><HALFTIME/></MD>";
	quarterTime= "<MD><QUARTERTIME/></MD>";
	twoMinutes= "<MD><TWOMINUTES/></MD>";
	oneMinute= "<MD><ONEMINUTE/></MD>";
	time="<MD><TIME/></MD>";
	
}

//! This function returns the specified command on the cmd parameter
QString Protocol::getCommand(int cmd)
{
	switch (cmd){
		case Protocol::StartCommand :
			return start;
			break;
		case Protocol::StopCommand :
			return stop;
			break;
		case Protocol::StatusCommand :
			return status;
			break;
		case Protocol::UserCommand:
			return user;
			break;
		case Protocol::EndSessionCommand:
			return endSession;
			break;
		case Protocol::ShutdownCommand:
			return shutdown;
			break;
		case Protocol::halfTimeCommand:
			return halfTime;
			break;
		case Protocol::quarterTimeCommand:
			return quarterTime;
			break;
		case Protocol::twoMinutesCommand:
			return twoMinutes;
			break;
		case Protocol::oneMinuteCommand:
			return oneMinute;
			break;
		case Protocol::timeCommand:
			return time;
			break;
		default:
			return stop;
			
	}
}

/// \brief start command
QString Protocol::startCMD()
{
	return start;
}

/// \brief stop command
QString Protocol::stopCMD()
{
	return stop;
}

/// \brief status command
QString Protocol::statusCMD()
{
	return status;
}


Protocol::~Protocol()
{
	
}


