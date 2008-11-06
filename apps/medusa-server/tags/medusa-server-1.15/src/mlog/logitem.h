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

#ifndef LOGITEM_H
#define LOGITEM_H
#include "output.h"
#include <qstring.h>
#include <list>
#include <qmutex.h>

namespace mlog {
  /*! @class LogItem <logitem.h>
      @brief LogItem objects log messages to a set of outputs.

      A LogItem object keeps a list of outputs (files, widgets, etc.) and logs
      messages to them.

      Usage example:
      @code
      mlog::Layout simple_layout;
      
      mlog::File file1("file1.log", simple_layout);
      mlog::File file2("file2.log", simple_layout);
      mlog::Syslog system_log(simple_layout);
      
      mlog::LogItem example;

      example.attachOutput(&file1);
      example.attachOutput(&file2);
      example.attachOutput(&system_log);

      example.log("This is a message log. It will be appended to file1, file2 and syslog.");
      @endcode

      @author Daniel Carrión
  */
  class LogItem {
    public:
      /*! List of outputs to send logs to. */
      std::list<Output *> outputs;
      /*! @brief Add output to the list.
          @param output Output to be added.
      */
      void attachOutput(Output *output);

      /*! @brief Remove output from the list.
          @param output Output to be removed.
      */
      void detachOutput(Output *output);

      /*! @brief Log a message to all attached outputs.
          @param message Log message.
      */
      void log(const QString message);
    private:
      /*! To serialize access to log method from multiple threads. */
      QMutex mutex;
  };
}
#endif //LOGITEM_H

