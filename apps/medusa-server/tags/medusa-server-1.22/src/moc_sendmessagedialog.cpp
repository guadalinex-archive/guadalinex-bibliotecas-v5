/****************************************************************************
** SendMessageDialog meta object code from reading C++ file 'sendmessagedialog.h'
**
** Created: Tue Feb 10 12:56:26 2009
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.7   edited Oct 19 16:22 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "sendmessagedialog.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *SendMessageDialog::className() const
{
    return "SendMessageDialog";
}

QMetaObject *SendMessageDialog::metaObj = 0;
static QMetaObjectCleanUp cleanUp_SendMessageDialog( "SendMessageDialog", &SendMessageDialog::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString SendMessageDialog::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "SendMessageDialog", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString SendMessageDialog::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "SendMessageDialog", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* SendMessageDialog::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = SendMessageDialogBase::staticMetaObject();
    static const QUMethod slot_0 = {"enableSendButton", 0, 0 };
    static const QUMethod slot_1 = {"clearText", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "enableSendButton()", &slot_0, QMetaData::Private },
	{ "clearText()", &slot_1, QMetaData::Private }
    };
    metaObj = QMetaObject::new_metaobject(
	"SendMessageDialog", parentObject,
	slot_tbl, 2,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_SendMessageDialog.setMetaObject( metaObj );
    return metaObj;
}

void* SendMessageDialog::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "SendMessageDialog" ) )
	return this;
    return SendMessageDialogBase::qt_cast( clname );
}

bool SendMessageDialog::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: enableSendButton(); break;
    case 1: clearText(); break;
    default:
	return SendMessageDialogBase::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool SendMessageDialog::qt_emit( int _id, QUObject* _o )
{
    return SendMessageDialogBase::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool SendMessageDialog::qt_property( int id, int f, QVariant* v)
{
    return SendMessageDialogBase::qt_property( id, f, v);
}

bool SendMessageDialog::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
