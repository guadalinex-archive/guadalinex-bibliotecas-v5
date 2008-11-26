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

#include "layout.h"
#include "output.h"
#include <qfile.h>
#include <qstring.h>
#include <qtextstream.h>
#include <syslog.h>
#include <iostream>

using namespace mlog;
using namespace std;

void Output::write(QString message)
{
  cout << message << "\n";
}

File::File() { };

File::File(File &copy) : Output(copy) {
	//file = copy.file;
}

File::File(QString filename, Layout layout)
{
	assignLayout(layout);
	assignFile(filename);
}

void File::assignLayout(Layout layout)
{
  this->layout = layout;
}

void File::assignFile(QString filename)
{
	file.close();
  file.setName(filename);
  file.open(IO_WriteOnly | IO_Append);
}

void File::write(QString message)
{
  QTextStream stream(&file);
  message = layout.beautify(message);
  stream << message << "\n";
	file.flush();
}

void File::close()
{
	file.close();
}

File::~File()
{
  file.close();
}

Syslog::Syslog() { };

Syslog::Syslog(Syslog &copy) : Output(copy) { };

Syslog::Syslog(Layout layout)
{
  assignLayout(layout);
}

void Syslog::assignLayout(Layout layout)
{
  this->layout = layout;
}

void Syslog::write(QString message)
{
  message = layout.beautify(message);
  syslog(LOG_INFO, message);
}
