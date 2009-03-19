/****************************************************************************
** AddHostDialogBase meta object code from reading C++ file 'addhostdialogbase.h'
**
** Created: Tue Feb 10 12:56:27 2009
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.7   edited Oct 19 16:22 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "addhostdialogbase.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *AddHostDialogBase::className() const
{
    return "AddHostDialogBase";
}

QMetaObject *AddHostDialogBase::metaObj = 0;
static QMetaObjectCleanUp cleanUp_AddHostDialogBase( "AddHostDialogBase", &AddHostDialogBase::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString AddHostDialogBase::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "AddHostDialogBase", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString AddHostDialogBase::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "AddHostDialogBase", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* AddHostDialogBase::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QDialog::staticMetaObject();
    static const QUMethod slot_0 = {"clearItems", 0, 0 };
    static const QUMethod slot_1 = {"enableOkButton", 0, 0 };
    static const QUMethod slot_2 = {"languageChange", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "clearItems()", &slot_0, QMetaData::Public },
	{ "enableOkButton()", &slot_1, QMetaData::Public },
	{ "languageChange()", &slot_2, QMetaData::Protected }
    };
    metaObj = QMetaObject::new_metaobject(
	"AddHostDialogBase", parentObject,
	slot_tbl, 3,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_AddHostDialogBase.setMetaObject( metaObj );
    return metaObj;
}

void* AddHostDialogBase::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "AddHostDialogBase" ) )
	return this;
    return QDialog::qt_cast( clname );
}

bool AddHostDialogBase::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: clearItems(); break;
    case 1: enableOkButton(); break;
    case 2: languageChange(); break;
    default:
	return QDialog::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool AddHostDialogBase::qt_emit( int _id, QUObject* _o )
{
    return QDialog::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool AddHostDialogBase::qt_property( int id, int f, QVariant* v)
{
    return QDialog::qt_property( id, f, v);
}

bool AddHostDialogBase::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
