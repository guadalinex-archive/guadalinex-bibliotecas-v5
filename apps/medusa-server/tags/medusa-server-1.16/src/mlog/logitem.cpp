/***************************************************************************
 *   Copyright (C) 2004 Daniel Carrión                                     *
 *   daniel@yacoi.com                                                      *
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

#include "logitem.h"
#include "output.h"
#include <list>
#include <qstring.h>
#include <qmutex.h>

using namespace std;
using namespace mlog;

void LogItem::attachOutput(Output *output)
{
  outputs.push_back(output);
}

void LogItem::detachOutput(Output *output)
{
  outputs.remove(output);
}

void LogItem::log(const QString message)
{
  mutex.lock();

  list<Output *>::const_iterator it;
  for(it = outputs.begin(); it != outputs.end(); ++it)
    (*it)->write(message);

  mutex.unlock();
}
