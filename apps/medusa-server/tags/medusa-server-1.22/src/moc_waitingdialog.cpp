/****************************************************************************
** WaitingDialog meta object code from reading C++ file 'waitingdialog.h'
**
** Created: Tue Feb 10 12:56:25 2009
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.7   edited Oct 19 16:22 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "waitingdialog.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *WaitingDialog::className() const
{
    return "WaitingDialog";
}

QMetaObject *WaitingDialog::metaObj = 0;
static QMetaObjectCleanUp cleanUp_WaitingDialog( "WaitingDialog", &WaitingDialog::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString WaitingDialog::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "WaitingDialog", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString WaitingDialog::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "WaitingDialog", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* WaitingDialog::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = WaitingDialogBase::staticMetaObject();
    static const QUMethod slot_0 = {"advanceBar", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "advanceBar()", &slot_0, QMetaData::Public }
    };
    metaObj = QMetaObject::new_metaobject(
	"WaitingDialog", parentObject,
	slot_tbl, 1,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_WaitingDialog.setMetaObject( metaObj );
    return metaObj;
}

void* WaitingDialog::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "WaitingDialog" ) )
	return this;
    return WaitingDialogBase::qt_cast( clname );
}

bool WaitingDialog::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: advanceBar(); break;
    default:
	return WaitingDialogBase::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool WaitingDialog::qt_emit( int _id, QUObject* _o )
{
    return WaitingDialogBase::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool WaitingDialog::qt_property( int id, int f, QVariant* v)
{
    return WaitingDialogBase::qt_property( id, f, v);
}

bool WaitingDialog::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
