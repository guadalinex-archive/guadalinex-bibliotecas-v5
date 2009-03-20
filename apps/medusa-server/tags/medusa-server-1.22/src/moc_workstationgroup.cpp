/****************************************************************************
** WorkStationGroup meta object code from reading C++ file 'workstationgroup.h'
**
** Created: Tue Feb 10 12:56:20 2009
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.7   edited Oct 19 16:22 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "workstationgroup.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *WorkStationGroup::className() const
{
    return "WorkStationGroup";
}

QMetaObject *WorkStationGroup::metaObj = 0;
static QMetaObjectCleanUp cleanUp_WorkStationGroup( "WorkStationGroup", &WorkStationGroup::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString WorkStationGroup::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "WorkStationGroup", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString WorkStationGroup::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "WorkStationGroup", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* WorkStationGroup::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QObject::staticMetaObject();
    static const QUMethod slot_0 = {"askStatus", 0, 0 };
    static const QUMethod slot_1 = {"killDialog", 0, 0 };
    static const QUMethod slot_2 = {"killTimeoutDialog", 0, 0 };
    static const QUMethod slot_3 = {"continueWaiting", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "askStatus()", &slot_0, QMetaData::Private },
	{ "killDialog()", &slot_1, QMetaData::Private },
	{ "killTimeoutDialog()", &slot_2, QMetaData::Private },
	{ "continueWaiting()", &slot_3, QMetaData::Private }
    };
    static const QUParameter param_signal_0[] = {
	{ "id", &static_QUType_QString, 0, QUParameter::In },
	{ "time", &static_QUType_ptr, "long", QUParameter::In }
    };
    static const QUMethod signal_0 = {"updateView", 2, param_signal_0 };
    static const QUParameter param_signal_1[] = {
	{ "host", &static_QUType_QString, 0, QUParameter::In },
	{ "msg", &static_QUType_QString, 0, QUParameter::In }
    };
    static const QUMethod signal_1 = {"wsSocketErrorSignal", 2, param_signal_1 };
    static const QUParameter param_signal_2[] = {
	{ "host", &static_QUType_QString, 0, QUParameter::In },
	{ "status", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod signal_2 = {"wsStatusChangedSignal", 2, param_signal_2 };
    static const QUParameter param_signal_3[] = {
	{ "host", &static_QUType_QString, 0, QUParameter::In }
    };
    static const QUMethod signal_3 = {"workstationDeleted", 1, param_signal_3 };
    static const QUParameter param_signal_4[] = {
	{ "host", &static_QUType_QString, 0, QUParameter::In },
	{ "user", &static_QUType_QString, 0, QUParameter::In }
    };
    static const QUMethod signal_4 = {"userChangedSignal", 2, param_signal_4 };
    static const QUParameter param_signal_5[] = {
	{ "host", &static_QUType_QString, 0, QUParameter::In },
	{ "user", &static_QUType_QString, 0, QUParameter::In }
    };
    static const QUMethod signal_5 = {"loginUserChangedSignal", 2, param_signal_5 };
    static const QMetaData signal_tbl[] = {
	{ "updateView(QString,long)", &signal_0, QMetaData::Public },
	{ "wsSocketErrorSignal(QString,QString)", &signal_1, QMetaData::Public },
	{ "wsStatusChangedSignal(QString,int)", &signal_2, QMetaData::Public },
	{ "workstationDeleted(QString)", &signal_3, QMetaData::Public },
	{ "userChangedSignal(const QString&,const QString&)", &signal_4, QMetaData::Public },
	{ "loginUserChangedSignal(const QString&,const QString&)", &signal_5, QMetaData::Public }
    };
    metaObj = QMetaObject::new_metaobject(
	"WorkStationGroup", parentObject,
	slot_tbl, 4,
	signal_tbl, 6,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_WorkStationGroup.setMetaObject( metaObj );
    return metaObj;
}

void* WorkStationGroup::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "WorkStationGroup" ) )
	return this;
    return QObject::qt_cast( clname );
}

#include <qobjectdefs.h>
#include <qsignalslotimp.h>

// SIGNAL updateView
void WorkStationGroup::updateView( QString t0, long t1 )
{
    if ( signalsBlocked() )
	return;
    QConnectionList *clist = receivers( staticMetaObject()->signalOffset() + 0 );
    if ( !clist )
	return;
    QUObject o[3];
    static_QUType_QString.set(o+1,t0);
    static_QUType_ptr.set(o+2,&t1);
    activate_signal( clist, o );
}

// SIGNAL wsSocketErrorSignal
void WorkStationGroup::wsSocketErrorSignal( QString t0, QString t1 )
{
    if ( signalsBlocked() )
	return;
    QConnectionList *clist = receivers( staticMetaObject()->signalOffset() + 1 );
    if ( !clist )
	return;
    QUObject o[3];
    static_QUType_QString.set(o+1,t0);
    static_QUType_QString.set(o+2,t1);
    activate_signal( clist, o );
}

// SIGNAL wsStatusChangedSignal
void WorkStationGroup::wsStatusChangedSignal( QString t0, int t1 )
{
    if ( signalsBlocked() )
	return;
    QConnectionList *clist = receivers( staticMetaObject()->signalOffset() + 2 );
    if ( !clist )
	return;
    QUObject o[3];
    static_QUType_QString.set(o+1,t0);
    static_QUType_int.set(o+2,t1);
    activate_signal( clist, o );
}

// SIGNAL workstationDeleted
void WorkStationGroup::workstationDeleted( QString t0 )
{
    activate_signal( staticMetaObject()->signalOffset() + 3, t0 );
}

// SIGNAL userChangedSignal
void WorkStationGroup::userChangedSignal( const QString& t0, const QString& t1 )
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

// SIGNAL loginUserChangedSignal
void WorkStationGroup::loginUserChangedSignal( const QString& t0, const QString& t1 )
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

bool WorkStationGroup::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: askStatus(); break;
    case 1: killDialog(); break;
    case 2: killTimeoutDialog(); break;
    case 3: continueWaiting(); break;
    default:
	return QObject::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool WorkStationGroup::qt_emit( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->signalOffset() ) {
    case 0: updateView((QString)static_QUType_QString.get(_o+1),(long)(*((long*)static_QUType_ptr.get(_o+2)))); break;
    case 1: wsSocketErrorSignal((QString)static_QUType_QString.get(_o+1),(QString)static_QUType_QString.get(_o+2)); break;
    case 2: wsStatusChangedSignal((QString)static_QUType_QString.get(_o+1),(int)static_QUType_int.get(_o+2)); break;
    case 3: workstationDeleted((QString)static_QUType_QString.get(_o+1)); break;
    case 4: userChangedSignal((const QString&)static_QUType_QString.get(_o+1),(const QString&)static_QUType_QString.get(_o+2)); break;
    case 5: loginUserChangedSignal((const QString&)static_QUType_QString.get(_o+1),(const QString&)static_QUType_QString.get(_o+2)); break;
    default:
	return QObject::qt_emit(_id,_o);
    }
    return TRUE;
}
#ifndef QT_NO_PROPERTIES

bool WorkStationGroup::qt_property( int id, int f, QVariant* v)
{
    return QObject::qt_property( id, f, v);
}

bool WorkStationGroup::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
