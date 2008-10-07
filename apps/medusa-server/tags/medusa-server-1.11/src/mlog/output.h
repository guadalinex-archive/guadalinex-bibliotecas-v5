/***************************************************************************
 *   Copyright (C) 2004 Junta de Andalucía                                 *
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

#ifndef OUTPUT_H
#define OUTPUT_H
#include "layout.h"
#include <qfile.h>
#include <qstring.h>

namespace mlog {
  /*! @class Output <output.h>
      @brief Output objects are wrappers to different potential destinations for log messages (files, widgets, sockets, etc.)

      Currently, only files and syslog are supported, and support for log priorities needs to be added, too.

      @author Daniel Carrión
  */
  class Output {
    public:
      /*! Layout to be used when sending a log message to an output. */
      Layout layout;

      /*! @brief Writes to output.
          @param message String to be written.
      */
      virtual void write(QString message);
  };

  class File: public Output {
    public:
      /*! File to send logs to */
      QFile file;
      
      /*! @brief Writes to the file.
          @param message String to be written.
      */
      void write(QString message);
      
      /*! @brief Create object with no layout assigned.
      */
      File();
      
      /*! @brief Copy constructor.
      */
      File(File &copy);
			
			/*! @brief Opens file for writing and assigns layout.
          @param filename File name.
          @param layout Layout to be used when writing logs to this file.
      */
      File(QString filename, Layout layout);

			/*! @brief Assigns layout to file.
          @param filename File name.
          @param layout Layout to be used when writing logs to this file.
      */
      void assignLayout(Layout layout);
      
			/*! @brief Opens file for writing.
          @param filename File name.
      */
      void assignFile(QString filename);
			
	/*! @brief Closes file.
	*/
	void close();
			
	/*! @brief Closes file.
	 */
	virtual ~File();
  };
  
  class Syslog: public Output {
    public:
      /*! @brief Writes to syslog.
          @param message String to be written.
      */
      void write(QString message);

      /*! @brief Create object with no layout assigned.
      */
      Syslog();
      
      /*! @brief Copy constructor.
      */
      Syslog(Syslog &copy);
			
			/*! @brief Assigns layout.
          @param layout Layout to be used when writing logs to syslog.
      */
      Syslog(Layout layout);
			
			/*! @brief Assigns layout to output.
          @param layout Layout to be used when writing logs to syslog.
      */
      void assignLayout(Layout layout);
  };
}
#endif //OUTPUT_H

