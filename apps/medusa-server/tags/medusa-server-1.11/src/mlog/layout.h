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

#ifndef LAYOUT_H
#define LAYOUT_H
#include <qstring.h>

namespace mlog {
	/*! @brief Types of layout.
			Currently,
				simple: no processing at all.
				timestamp: adds date and time to message.
	*/
	typedef enum {
		simple,
		timestamp
	} LayoutType;
	
  /*! @class Layout <layout.h>
      @brief Add fields to a log message before writing it to a file.

      TODO

      @author Daniel Carrión
  */
  class Layout {
    public:
			/*! Holds the layout type. */
			LayoutType type;
			
      /*! @brief Add fields to a log message before writing it to a file.

          Currently, it just sends the same string back.

          @param message String to be processed.
      */
      QString beautify(QString message);
      
			/*! @brief Sets the layout type;
          @param newType String to be processed.
      */
			void setType(LayoutType newType);
  };
}
#endif //LAYOUT_H

