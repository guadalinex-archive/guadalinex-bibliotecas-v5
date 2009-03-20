/****************************************************************************
** ConfigurationDialog meta object code from reading C++ file 'configurationdialog.h'
**
** Created: Tue Feb 10 12:56:21 2009
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.7   edited Oct 19 16:22 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "configurationdialog.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *ConfigurationDialog::className() const
{
    return "ConfigurationDialog";
}

QMetaObject *ConfigurationDialog::metaObj = 0;
static QMetaObjectCleanUp cleanUp_ConfigurationDialog( "ConfigurationDialog", &ConfigurationDialog::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString ConfigurationDialog::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "ConfigurationDialog", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString ConfigurationDialog::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "ConfigurationDialog", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* ConfigurationDialog::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = ConfigurationDialogBase::staticMetaObject();
    static const QUMethod slot_0 = {"selectFont", 0, 0 };
    static const QUMethod slot_1 = {"selectLogFile", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "selectFont()", &slot_0, QMetaData::Private },
	{ "selectLogFile()", &slot_1, QMetaData::Private }
    };
    metaObj = QMetaObject::new_metaobject(
	"ConfigurationDialog", parentObject,
	slot_tbl, 2,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_ConfigurationDialog.setMetaObject( metaObj );
    return metaObj;
}

void* ConfigurationDialog::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "ConfigurationDialog" ) )
	return this;
    return ConfigurationDialogBase::qt_cast( clname );
}

bool ConfigurationDialog::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: selectFont(); break;
    case 1: selectLogFile(); break;
    default:
	return ConfigurationDialogBase::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool ConfigurationDialog::qt_emit( int _id, QUObject* _o )
{
    return ConfigurationDialogBase::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool ConfigurationDialog::qt_property( int id, int f, QVariant* v)
{
    return ConfigurationDialogBase::qt_property( id, f, v);
}

bool ConfigurationDialog::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
