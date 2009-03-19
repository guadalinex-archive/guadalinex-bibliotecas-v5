/****************************************************************************
** MainWindow meta object code from reading C++ file 'mainwindow.h'
**
** Created: Tue Feb 10 12:56:17 2009
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.7   edited Oct 19 16:22 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "mainwindow.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *MainWindow::className() const
{
    return "MainWindow";
}

QMetaObject *MainWindow::metaObj = 0;
static QMetaObjectCleanUp cleanUp_MainWindow( "MainWindow", &MainWindow::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString MainWindow::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "MainWindow", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString MainWindow::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "MainWindow", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* MainWindow::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QMainWindow::staticMetaObject();
    static const QUMethod slot_0 = {"deleteHost", 0, 0 };
    static const QUMethod slot_1 = {"editHost", 0, 0 };
    static const QUMethod slot_2 = {"addHost", 0, 0 };
    static const QUMethod slot_3 = {"autoDiscovery", 0, 0 };
    static const QUParameter param_slot_4[] = {
	{ "host", &static_QUType_QString, 0, QUParameter::In }
    };
    static const QUMethod slot_4 = {"discoveredStation", 1, param_slot_4 };
    static const QUMethod slot_5 = {"editSettings", 0, 0 };
    static const QUMethod slot_6 = {"newFile", 0, 0 };
    static const QUMethod slot_7 = {"open", 0, 0 };
    static const QUParameter param_slot_8[] = {
	{ 0, &static_QUType_bool, 0, QUParameter::Out }
    };
    static const QUMethod slot_8 = {"save", 1, param_slot_8 };
    static const QUParameter param_slot_9[] = {
	{ 0, &static_QUType_bool, 0, QUParameter::Out }
    };
    static const QUMethod slot_9 = {"saveAs", 1, param_slot_9 };
    static const QUMethod slot_10 = {"about", 0, 0 };
    static const QUParameter param_slot_11[] = {
	{ "param", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_11 = {"openRecentFile", 1, param_slot_11 };
    static const QUMethod slot_12 = {"blockAll", 0, 0 };
    static const QUParameter param_slot_13[] = {
	{ "host", &static_QUType_QString, 0, QUParameter::In },
	{ "time", &static_QUType_ptr, "long", QUParameter::In }
    };
    static const QUMethod slot_13 = {"updateView", 2, param_slot_13 };
    static const QUMethod slot_14 = {"blockSelected", 0, 0 };
    static const QUMethod slot_15 = {"unblockAll", 0, 0 };
    static const QUMethod slot_16 = {"shutdownAll", 0, 0 };
    static const QUMethod slot_17 = {"activateSelectedHost", 0, 0 };
    static const QUMethod slot_18 = {"blockSelectedSlot", 0, 0 };
    static const QUMethod slot_19 = {"unblockSelectedSlot", 0, 0 };
    static const QUMethod slot_20 = {"shutdownSelectedSlot", 0, 0 };
    static const QUParameter param_slot_21[] = {
	{ "host", &static_QUType_QString, 0, QUParameter::In },
	{ "msg", &static_QUType_QString, 0, QUParameter::In }
    };
    static const QUMethod slot_21 = {"updateViewError", 2, param_slot_21 };
    static const QUParameter param_slot_22[] = {
	{ "host", &static_QUType_QString, 0, QUParameter::In },
	{ "status", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_22 = {"updateViewStatus", 2, param_slot_22 };
    static const QUParameter param_slot_23[] = {
	{ "host", &static_QUType_QString, 0, QUParameter::In },
	{ "user", &static_QUType_QString, 0, QUParameter::In }
    };
    static const QUMethod slot_23 = {"updateViewUser", 2, param_slot_23 };
    static const QUParameter param_slot_24[] = {
	{ "host", &static_QUType_QString, 0, QUParameter::In },
	{ "user", &static_QUType_QString, 0, QUParameter::In }
    };
    static const QUMethod slot_24 = {"updateViewLoginUser", 2, param_slot_24 };
    static const QUMethod slot_25 = {"getLoginUser", 0, 0 };
    static const QUMethod slot_26 = {"sendMessage", 0, 0 };
    static const QUMethod slot_27 = {"sendMessageAll", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "deleteHost()", &slot_0, QMetaData::Private },
	{ "editHost()", &slot_1, QMetaData::Private },
	{ "addHost()", &slot_2, QMetaData::Private },
	{ "autoDiscovery()", &slot_3, QMetaData::Private },
	{ "discoveredStation(QString)", &slot_4, QMetaData::Private },
	{ "editSettings()", &slot_5, QMetaData::Private },
	{ "newFile()", &slot_6, QMetaData::Private },
	{ "open()", &slot_7, QMetaData::Private },
	{ "save()", &slot_8, QMetaData::Private },
	{ "saveAs()", &slot_9, QMetaData::Private },
	{ "about()", &slot_10, QMetaData::Private },
	{ "openRecentFile(int)", &slot_11, QMetaData::Private },
	{ "blockAll()", &slot_12, QMetaData::Private },
	{ "updateView(QString,long)", &slot_13, QMetaData::Private },
	{ "blockSelected()", &slot_14, QMetaData::Private },
	{ "unblockAll()", &slot_15, QMetaData::Private },
	{ "shutdownAll()", &slot_16, QMetaData::Private },
	{ "activateSelectedHost()", &slot_17, QMetaData::Private },
	{ "blockSelectedSlot()", &slot_18, QMetaData::Private },
	{ "unblockSelectedSlot()", &slot_19, QMetaData::Private },
	{ "shutdownSelectedSlot()", &slot_20, QMetaData::Private },
	{ "updateViewError(QString,QString)", &slot_21, QMetaData::Private },
	{ "updateViewStatus(QString,int)", &slot_22, QMetaData::Private },
	{ "updateViewUser(const QString&,const QString&)", &slot_23, QMetaData::Private },
	{ "updateViewLoginUser(const QString&,const QString&)", &slot_24, QMetaData::Private },
	{ "getLoginUser()", &slot_25, QMetaData::Private },
	{ "sendMessage()", &slot_26, QMetaData::Private },
	{ "sendMessageAll()", &slot_27, QMetaData::Private }
    };
    metaObj = QMetaObject::new_metaobject(
	"MainWindow", parentObject,
	slot_tbl, 28,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_MainWindow.setMetaObject( metaObj );
    return metaObj;
}

void* MainWindow::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "MainWindow" ) )
	return this;
    return QMainWindow::qt_cast( clname );
}

bool MainWindow::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: deleteHost(); break;
    case 1: editHost(); break;
    case 2: addHost(); break;
    case 3: autoDiscovery(); break;
    case 4: discoveredStation((QString)static_QUType_QString.get(_o+1)); break;
    case 5: editSettings(); break;
    case 6: newFile(); break;
    case 7: open(); break;
    case 8: static_QUType_bool.set(_o,save()); break;
    case 9: static_QUType_bool.set(_o,saveAs()); break;
    case 10: about(); break;
    case 11: openRecentFile((int)static_QUType_int.get(_o+1)); break;
    case 12: blockAll(); break;
    case 13: updateView((QString)static_QUType_QString.get(_o+1),(long)(*((long*)static_QUType_ptr.get(_o+2)))); break;
    case 14: blockSelected(); break;
    case 15: unblockAll(); break;
    case 16: shutdownAll(); break;
    case 17: activateSelectedHost(); break;
    case 18: blockSelectedSlot(); break;
    case 19: unblockSelectedSlot(); break;
    case 20: shutdownSelectedSlot(); break;
    case 21: updateViewError((QString)static_QUType_QString.get(_o+1),(QString)static_QUType_QString.get(_o+2)); break;
    case 22: updateViewStatus((QString)static_QUType_QString.get(_o+1),(int)static_QUType_int.get(_o+2)); break;
    case 23: updateViewUser((const QString&)static_QUType_QString.get(_o+1),(const QString&)static_QUType_QString.get(_o+2)); break;
    case 24: updateViewLoginUser((const QString&)static_QUType_QString.get(_o+1),(const QString&)static_QUType_QString.get(_o+2)); break;
    case 25: getLoginUser(); break;
    case 26: sendMessage(); break;
    case 27: sendMessageAll(); break;
    default:
	return QMainWindow::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool MainWindow::qt_emit( int _id, QUObject* _o )
{
    return QMainWindow::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool MainWindow::qt_property( int id, int f, QVariant* v)
{
    return QMainWindow::qt_property( id, f, v);
}

bool MainWindow::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
