/***************************************************************************
 *   Copyright (C) 2004 by Junta de Andalucía                              *
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
/*
 * $Id: main.cpp 211 2005-01-21 16:02:38Z rmartin $
 * $Author: rmartin $
 */
 
#include <qapplication.h>
#include <qtextcodec.h>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    // TODO: i18n only works if executed from path_to_project/bin
    //       possibly, the .qm file should de placed in /usr/share/qt3/translations

    QApplication app(argc, argv);

    // translation file for Qt (TODO: set qm file path to something more sensible, see above)
    QTranslator qt(0);
    qt.load(QString("qt.") + QTextCodec::locale(), "/usr/share/qt3/translations");
    app.installTranslator(&qt);

    // translation file for application strings (TODO: set qm file path to something more sensible, see above)
    QTranslator myapp(0);
    //myapp.load(QString("mdserver_") + QTextCodec::locale(), "../src");
    myapp.load(QString("mdserver_") + QTextCodec::locale(), "/usr/share/qt3/translations");
    app.installTranslator(&myapp);

    MainWindow mainWin;
    app.setMainWidget(&mainWin);
    
    QObject::connect( qApp, SIGNAL( lastWindowClosed() ),
                 qApp, SLOT( quit() ) );
    

    mainWin.show();
    
    
    return app.exec();
}
