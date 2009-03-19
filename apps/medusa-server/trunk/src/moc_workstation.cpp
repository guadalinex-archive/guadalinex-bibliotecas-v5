/****************************************************************************
** WorkStation meta object code from reading C++ file 'workstation.h'
**
** Created: Tue Feb 10 12:56:18 2009
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.7   edited Oct 19 16:22 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "workstation.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *WorkStation::className() const
{
    return "WorkStation";
}

QMetaObject *WorkStation::metaObj = 0;
static QMetaObjectCleanUp cleanUp_WorkStation( "WorkStation", &WorkStation::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString WorkStation::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "WorkStation", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString WorkStation::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "WorkStation", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* WorkStation::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QObject::staticMetaObject();
    static const QUMethod slot_0 = {"updateTimer", 0, 0 };
    static const QUMethod slot_1 = {"status", 0, 0 };
    static const QUMethod slot_2 = {"user", 0, 0 };
    static const QUMethod slot_3 = {"connectionClosedByClient", 0, 0 };
    static const QUMethod slot_4 = {"readFromClient", 0, 0 };
    static const QUParameter param_slot_5[] = {
	{ "errorno", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_5 = {"socketError", 1, param_slot_5 };
    static const QUMethod slot_6 = {"sendCommand", 0, 0 };
    static const QUMethod slot_7 = {"sendCommandTime", 0, 0 };
    static const QUMethod slot_8 = {"blockSlot", 0, 0 };
    static const QUMethod slot_9 = {"delayBlocked", 0, 0 };
    static const QUMethod slot_10 = {"wakeUp", 0, 0 };
    static const QUMethod slot_11 = {"connectionTimeout", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "updateTimer()", &slot_0, QMetaData::Public },
	{ "status()", &slot_1, QMetaData::Public },
	{ "user()", &slot_2, QMetaData::Public },
	{ "connectionClosedByClient()", &slot_3, QMetaData::Private },
	{ "readFromClient()", &slot_4, QMetaData::Private },
	{ "socketError(int)", &slot_5, QMetaData::Private },
	{ "sendCommand()", &slot_6, QMetaData::Private },
	{ "sendCommandTime()", &slot_7, QMetaData::Private },
	{ "blockSlot()", &slot_8, QMetaData::Private },
	{ "delayBlocked()", &slot_9, QMetaData::Private },
	{ "wakeUp()", &slot_10, QMetaData::Private },
	{ "connectionTimeout()", &slot_11, QMetaData::Private }
    };
    static const QUParameter param_signal_0[] = {
	{ "host", &static_QUType_QString, 0, QUParameter::In },
	{ "message", &static_QUType_QString, 0, QUParameter::In }
    };
    static const QUMethod signal_0 = {"wsConnError", 2, param_signal_0 };
    static const QUParameter param_signal_1[] = {
	{ "host", &static_QUType_QString, 0, QUParameter::In },
	{ "rsecs", &static_QUType_ptr, "long", QUParameter::In }
    };
    static const QUMethod signal_1 = {"wsTimeChanged", 2, param_signal_1 };
    static const QUParameter param_signal_2[] = {
	{ "id", &static_QUType_ptr, "Q_UINT8", QUParameter::In }
    };
    static const QUMethod signal_2 = {"wsBlocked", 1, param_signal_2 };
    static const QUParameter param_signal_3[] = {
	{ "host", &static_QUType_QString, 0, QUParameter::In },
	{ "state", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod signal_3 = {"wsStatusChanged", 2, param_signal_3 };
    static const QUParameter param_signal_4[] = {
	{ "host", &static_QUType_QString, 0, QUParameter::In },
	{ "user", &static_QUType_QString, 0, QUParameter::In }
    };
    static const QUMethod signal_4 = {"userChanged", 2, param_signal_4 };
    static const QUParameter param_signal_5[] = {
	{ "host", &static_QUType_QString, 0, QUParameter::In },
	{ "user", &static_QUType_QString, 0, QUParameter::In }
    };
    static const QUMethod signal_5 = {"loginUserChanged", 2, param_signal_5 };
    static const QMetaData signal_tbl[] = {
	{ "wsConnError(QString,QString)", &signal_0, QMetaData::Public },
	{ "wsTimeChanged(QString,long)", &signal_1, QMetaData::Public },
	{ "wsBlocked(Q_UINT8)", &signal_2, QMetaData::Public },
	{ "wsStatusChanged(QString,int)", &signal_3, QMetaData::Public },
	{ "userChanged(const QString&,const QString&)", &signal_4, QMetaData::Public },
	{ "loginUserChanged(const QString&,const QString&)", &signal_5, QMetaData::Public }
    };
    metaObj = QMetaObject::new_metaobject(
	"WorkStation", parentObject,
	slot_tbl, 12,
	signal_tbl, 6,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_WorkStation.setMetaObject( metaObj );
    return metaObj;
}

void* WorkStation::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "WorkStation" ) )
	return this;
    return QObject::qt_cast( clname );
}

#include <qobjectdefs.h>
#include <qsignalslotimp.h>

// SIGNAL wsConnError
void WorkStation::wsConnError( QString t0, QString t1 )
{
    if ( signalsBlocked() )
	return;
    QConnectionList *clist = receivers( staticMetaObject()->signalOffset() + 0 );
    if ( !clist )
	return;
    QUObject o[3];
    static_QUType_QString.set(o+1,t0);
    static_QUType_QString.set(o+2,t1);
    activate_signal( clist, o );
}

// SIGNAL wsTimeChanged
void WorkStation::wsTimeChanged( QString t0, long t1 )
{
    if ( signalsBlocked() )
	return;
    QConnectionList *clist = receivers( staticMetaObject()->signalOffset() + 1 );
    if ( !clist )
	return;
    QUObject o[3];
    static_QUType_QString.set(o+1,t0);
    static_QUType_ptr.set(o+2,&t1);
    activate_signal( clist, o );
}

// SIGNAL wsBlocked
void WorkStation::wsBlocked( Q_UINT8 t0 )
{
    if ( signalsBlocked() )
	return;
    QConnectionList *clist = receivers( staticMetaObject()->signalOffset() + 2 );
    if ( !clist )
	return;
    QUObject o[2];
    static_QUType_ptr.set(o+1,&t0);
    activate_signal( clist, o );
}

// SIGNAL wsStatusChanged
void WorkStation::wsStatusChanged( QString t0, int t1 )
{
    if ( signalsBlocked() )
	return;
    QConnectionList *clist = receivers( staticMetaObject()->signalOffset() + 3 );
    if ( !clist )
	return;
    QUObject o[3];
    static_QUType_QString.set(o+1,t0);
    static_QUType_int.set(o+2,t1);
    activate_signal( clist, o );
}

// SIGNAL userChanged
void WorkStation::userChanged( const QString& t0, const QString& t1 )
{
    if ( signalsBlocked() )
	return;
    QConnectionList *clist = receivers( staticMetaObject()->signalOffset() + 4 );
    if ( !clist )
	return;
    QUObject o[3];
    static_QUType_QString.set(o+1,t0);
    static_QUType_QString.set(o+2,t1);
    activate_signal( clist, o );
}

// SIGNAL loginUserChanged
void WorkStation::loginUserChanged( const QString& t0, const QString& t1 )
{
    if ( signalsBlocked() )
	return;
    QConnectionList *clist = receivers( staticMetaObject()->signalOffset() + 5 );
    if ( !clist )
	return;
    QUObject o[3];
    static_QUType_QString.set(o+1,t0);
    static_QUType_QString.set(o+2,t1);
    activate_signal( clist, o );
}

bool WorkStation::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: updateTimer(); break;
    case 1: status(); break;
    case 2: user(); break;
    case 3: connectionClosedByClient(); break;
    case 4: readFromClient(); break;
    case 5: socketError((int)static_QUType_int.get(_o+1)); break;
    case 6: sendCommand(); break;
    case 7: sendCommandTime(); break;
    case 8: blockSlot(); break;
    case 9: delayBlocked(); break;
    case 10: wakeUp(); break;
    case 11: connectionTimeout(); break;
    default:
	return QObject::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool WorkStation::qt_emit( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->signalOffset() ) {
    case 0: wsConnError((QString)static_QUType_QString.get(_o+1),(QString)static_QUType_QString.get(_o+2)); break;
    case 1: wsTimeChanged((QString)static_QUType_QString.get(_o+1),(long)(*((long*)static_QUType_ptr.get(_o+2)))); break;
    case 2: wsBlocked((Q_UINT8)(*((Q_UINT8*)static_QUType_ptr.get(_o+1)))); break;
    case 3: wsStatusChanged((QString)static_QUType_QString.get(_o+1),(int)static_QUType_int.get(_o+2)); break;
    case 4: userChanged((const QString&)static_QUType_QString.get(_o+1),(const QString&)static_QUType_QString.get(_o+2)); break;
    case 5: loginUserChanged((const QString&)static_QUType_QString.get(_o+1),(const QString&)static_QUType_QString.get(_o+2)); break;
    default:
	return QObject::qt_emit(_id,_o);
    }
    return TRUE;
}
#ifndef QT_NO_PROPERTIES

bool WorkStation::qt_property( int id, int f, QVariant* v)
{
    return QObject::qt_property( id, f, v);
}

bool WorkStation::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
