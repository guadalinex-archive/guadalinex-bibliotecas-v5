/****************************************************************************
** AddHostDialog meta object code from reading C++ file 'addhostdialog.h'
**
** Created: Tue Feb 10 12:56:20 2009
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.7   edited Oct 19 16:22 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "addhostdialog.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *AddHostDialog::className() const
{
    return "AddHostDialog";
}

QMetaObject *AddHostDialog::metaObj = 0;
static QMetaObjectCleanUp cleanUp_AddHostDialog( "AddHostDialog", &AddHostDialog::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString AddHostDialog::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "AddHostDialog", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString AddHostDialog::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "AddHostDialog", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* AddHostDialog::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = AddHostDialogBase::staticMetaObject();
    static const QUMethod slot_0 = {"enableOkButton", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "enableOkButton()", &slot_0, QMetaData::Private }
    };
    metaObj = QMetaObject::new_metaobject(
	"AddHostDialog", parentObject,
	slot_tbl, 1,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_AddHostDialog.setMetaObject( metaObj );
    return metaObj;
}

void* AddHostDialog::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "AddHostDialog" ) )
	return this;
    return AddHostDialogBase::qt_cast( clname );
}

bool AddHostDialog::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: enableOkButton(); break;
    default:
	return AddHostDialogBase::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool AddHostDialog::qt_emit( int _id, QUObject* _o )
{
    return AddHostDialogBase::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool AddHostDialog::qt_property( int id, int f, QVariant* v)
{
    return AddHostDialogBase::qt_property( id, f, v);
}

bool AddHostDialog::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
