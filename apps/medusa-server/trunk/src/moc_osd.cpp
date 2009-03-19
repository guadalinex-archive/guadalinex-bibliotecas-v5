/****************************************************************************
** OSDWidget meta object code from reading C++ file 'osd.h'
**
** Created: Tue Feb 10 12:56:24 2009
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.7   edited Oct 19 16:22 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "osd.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *OSDWidget::className() const
{
    return "OSDWidget";
}

QMetaObject *OSDWidget::metaObj = 0;
static QMetaObjectCleanUp cleanUp_OSDWidget( "OSDWidget", &OSDWidget::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString OSDWidget::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "OSDWidget", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString OSDWidget::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "OSDWidget", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* OSDWidget::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QWidget::staticMetaObject();
    static const QUParameter param_slot_0[] = {
	{ 0, &static_QUType_QString, 0, QUParameter::In }
    };
    static const QUMethod slot_0 = {"showOSD", 1, param_slot_0 };
    static const QUParameter param_slot_1[] = {
	{ 0, &static_QUType_QString, 0, QUParameter::In },
	{ "preemptive", &static_QUType_bool, 0, QUParameter::In }
    };
    static const QUMethod slot_1 = {"showOSD", 2, param_slot_1 };
    static const QUMethod slot_2 = {"removeOSD", 0, 0 };
    static const QUMethod slot_3 = {"minReached", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "showOSD(const QString&)", &slot_0, QMetaData::Public },
	{ "showOSD(const QString&,bool)", &slot_1, QMetaData::Public },
	{ "removeOSD()", &slot_2, QMetaData::Public },
	{ "minReached()", &slot_3, QMetaData::Protected }
    };
    metaObj = QMetaObject::new_metaobject(
	"OSDWidget", parentObject,
	slot_tbl, 4,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_OSDWidget.setMetaObject( metaObj );
    return metaObj;
}

void* OSDWidget::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "OSDWidget" ) )
	return this;
    return QWidget::qt_cast( clname );
}

bool OSDWidget::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: showOSD((const QString&)static_QUType_QString.get(_o+1)); break;
    case 1: showOSD((const QString&)static_QUType_QString.get(_o+1),(bool)static_QUType_bool.get(_o+2)); break;
    case 2: removeOSD(); break;
    case 3: minReached(); break;
    default:
	return QWidget::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool OSDWidget::qt_emit( int _id, QUObject* _o )
{
    return QWidget::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool OSDWidget::qt_property( int id, int f, QVariant* v)
{
    return QWidget::qt_property( id, f, v);
}

bool OSDWidget::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES


const char *OSDPreviewWidget::className() const
{
    return "OSDPreviewWidget";
}

QMetaObject *OSDPreviewWidget::metaObj = 0;
static QMetaObjectCleanUp cleanUp_OSDPreviewWidget( "OSDPreviewWidget", &OSDPreviewWidget::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString OSDPreviewWidget::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "OSDPreviewWidget", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString OSDPreviewWidget::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "OSDPreviewWidget", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* OSDPreviewWidget::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = OSDWidget::staticMetaObject();
    static const QUMethod signal_0 = {"positionChanged", 0, 0 };
    static const QMetaData signal_tbl[] = {
	{ "positionChanged()", &signal_0, QMetaData::Public }
    };
    metaObj = QMetaObject::new_metaobject(
	"OSDPreviewWidget", parentObject,
	0, 0,
	signal_tbl, 1,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_OSDPreviewWidget.setMetaObject( metaObj );
    return metaObj;
}

void* OSDPreviewWidget::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "OSDPreviewWidget" ) )
	return this;
    return OSDWidget::qt_cast( clname );
}

// SIGNAL positionChanged
void OSDPreviewWidget::positionChanged()
{
    activate_signal( staticMetaObject()->signalOffset() + 0 );
}

bool OSDPreviewWidget::qt_invoke( int _id, QUObject* _o )
{
    return OSDWidget::qt_invoke(_id,_o);
}

bool OSDPreviewWidget::qt_emit( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->signalOffset() ) {
    case 0: positionChanged(); break;
    default:
	return OSDWidget::qt_emit(_id,_o);
    }
    return TRUE;
}
#ifndef QT_NO_PROPERTIES

bool OSDPreviewWidget::qt_property( int id, int f, QVariant* v)
{
    return OSDWidget::qt_property( id, f, v);
}

bool OSDPreviewWidget::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
