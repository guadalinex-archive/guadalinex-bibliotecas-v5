/****************************************************************************
** AutoDiscoveryDialog meta object code from reading C++ file 'autodiscoverydialog.h'
**
** Created: Tue Feb 10 12:56:23 2009
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.7   edited Oct 19 16:22 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "autodiscoverydialog.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *AutoDiscoveryDialog::className() const
{
    return "AutoDiscoveryDialog";
}

QMetaObject *AutoDiscoveryDialog::metaObj = 0;
static QMetaObjectCleanUp cleanUp_AutoDiscoveryDialog( "AutoDiscoveryDialog", &AutoDiscoveryDialog::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString AutoDiscoveryDialog::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "AutoDiscoveryDialog", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString AutoDiscoveryDialog::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "AutoDiscoveryDialog", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* AutoDiscoveryDialog::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = AutoDiscoveryDialogBase::staticMetaObject();
    static const QUMethod slot_0 = {"startSearchSlot", 0, 0 };
    static const QUParameter param_slot_1[] = {
	{ "host", &static_QUType_QString, 0, QUParameter::In },
	{ "status", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_1 = {"stationFound", 2, param_slot_1 };
    static const QUParameter param_slot_2[] = {
	{ "host", &static_QUType_QString, 0, QUParameter::In },
	{ "err", &static_QUType_QString, 0, QUParameter::In }
    };
    static const QUMethod slot_2 = {"stationNotFound", 2, param_slot_2 };
    static const QUMethod slot_3 = {"stopSearchSlot", 0, 0 };
    static const QUParameter param_slot_4[] = {
	{ "text", &static_QUType_QString, 0, QUParameter::In }
    };
    static const QUMethod slot_4 = {"changedStartEdit1", 1, param_slot_4 };
    static const QUParameter param_slot_5[] = {
	{ "text", &static_QUType_QString, 0, QUParameter::In }
    };
    static const QUMethod slot_5 = {"changedStartEdit2", 1, param_slot_5 };
    static const QUParameter param_slot_6[] = {
	{ "text", &static_QUType_QString, 0, QUParameter::In }
    };
    static const QUMethod slot_6 = {"changedStartEdit3", 1, param_slot_6 };
    static const QUParameter param_slot_7[] = {
	{ "text", &static_QUType_QString, 0, QUParameter::In }
    };
    static const QUMethod slot_7 = {"changedStartEdit4", 1, param_slot_7 };
    static const QUParameter param_slot_8[] = {
	{ "text", &static_QUType_QString, 0, QUParameter::In }
    };
    static const QUMethod slot_8 = {"changedEndEdit1", 1, param_slot_8 };
    static const QUParameter param_slot_9[] = {
	{ "text", &static_QUType_QString, 0, QUParameter::In }
    };
    static const QUMethod slot_9 = {"changedEndEdit2", 1, param_slot_9 };
    static const QUParameter param_slot_10[] = {
	{ "text", &static_QUType_QString, 0, QUParameter::In }
    };
    static const QUMethod slot_10 = {"changedEndEdit3", 1, param_slot_10 };
    static const QUParameter param_slot_11[] = {
	{ "text", &static_QUType_QString, 0, QUParameter::In }
    };
    static const QUMethod slot_11 = {"changedEndEdit4", 1, param_slot_11 };
    static const QUMethod slot_12 = {"cancelSearchSlot", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "startSearchSlot()", &slot_0, QMetaData::Private },
	{ "stationFound(QString,int)", &slot_1, QMetaData::Private },
	{ "stationNotFound(QString,QString)", &slot_2, QMetaData::Private },
	{ "stopSearchSlot()", &slot_3, QMetaData::Private },
	{ "changedStartEdit1(const QString&)", &slot_4, QMetaData::Private },
	{ "changedStartEdit2(const QString&)", &slot_5, QMetaData::Private },
	{ "changedStartEdit3(const QString&)", &slot_6, QMetaData::Private },
	{ "changedStartEdit4(const QString&)", &slot_7, QMetaData::Private },
	{ "changedEndEdit1(const QString&)", &slot_8, QMetaData::Private },
	{ "changedEndEdit2(const QString&)", &slot_9, QMetaData::Private },
	{ "changedEndEdit3(const QString&)", &slot_10, QMetaData::Private },
	{ "changedEndEdit4(const QString&)", &slot_11, QMetaData::Private },
	{ "cancelSearchSlot()", &slot_12, QMetaData::Private }
    };
    static const QUParameter param_signal_0[] = {
	{ "host", &static_QUType_QString, 0, QUParameter::In }
    };
    static const QUMethod signal_0 = {"newStation", 1, param_signal_0 };
    static const QMetaData signal_tbl[] = {
	{ "newStation(QString)", &signal_0, QMetaData::Public }
    };
    metaObj = QMetaObject::new_metaobject(
	"AutoDiscoveryDialog", parentObject,
	slot_tbl, 13,
	signal_tbl, 1,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_AutoDiscoveryDialog.setMetaObject( metaObj );
    return metaObj;
}

void* AutoDiscoveryDialog::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "AutoDiscoveryDialog" ) )
	return this;
    return AutoDiscoveryDialogBase::qt_cast( clname );
}

// SIGNAL newStation
void AutoDiscoveryDialog::newStation( QString t0 )
{
    activate_signal( staticMetaObject()->signalOffset() + 0, t0 );
}

bool AutoDiscoveryDialog::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: startSearchSlot(); break;
    case 1: stationFound((QString)static_QUType_QString.get(_o+1),(int)static_QUType_int.get(_o+2)); break;
    case 2: stationNotFound((QString)static_QUType_QString.get(_o+1),(QString)static_QUType_QString.get(_o+2)); break;
    case 3: stopSearchSlot(); break;
    case 4: changedStartEdit1((const QString&)static_QUType_QString.get(_o+1)); break;
    case 5: changedStartEdit2((const QString&)static_QUType_QString.get(_o+1)); break;
    case 6: changedStartEdit3((const QString&)static_QUType_QString.get(_o+1)); break;
    case 7: changedStartEdit4((const QString&)static_QUType_QString.get(_o+1)); break;
    case 8: changedEndEdit1((const QString&)static_QUType_QString.get(_o+1)); break;
    case 9: changedEndEdit2((const QString&)static_QUType_QString.get(_o+1)); break;
    case 10: changedEndEdit3((const QString&)static_QUType_QString.get(_o+1)); break;
    case 11: changedEndEdit4((const QString&)static_QUType_QString.get(_o+1)); break;
    case 12: cancelSearchSlot(); break;
    default:
	return AutoDiscoveryDialogBase::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool AutoDiscoveryDialog::qt_emit( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->signalOffset() ) {
    case 0: newStation((QString)static_QUType_QString.get(_o+1)); break;
    default:
	return AutoDiscoveryDialogBase::qt_emit(_id,_o);
    }
    return TRUE;
}
#ifndef QT_NO_PROPERTIES

bool AutoDiscoveryDialog::qt_property( int id, int f, QVariant* v)
{
    return AutoDiscoveryDialogBase::qt_property( id, f, v);
}

bool AutoDiscoveryDialog::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
