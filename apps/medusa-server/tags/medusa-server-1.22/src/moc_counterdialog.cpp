/****************************************************************************
** CounterDialog meta object code from reading C++ file 'counterdialog.h'
**
** Created: Tue Feb 10 12:56:23 2009
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.7   edited Oct 19 16:22 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "counterdialog.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *CounterDialog::className() const
{
    return "CounterDialog";
}

QMetaObject *CounterDialog::metaObj = 0;
static QMetaObjectCleanUp cleanUp_CounterDialog( "CounterDialog", &CounterDialog::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString CounterDialog::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "CounterDialog", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString CounterDialog::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "CounterDialog", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* CounterDialog::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = CounterDialogBase::staticMetaObject();
    static const QUParameter param_slot_0[] = {
	{ "time", &static_QUType_varptr, "\x1b", QUParameter::In }
    };
    static const QUMethod slot_0 = {"timeChanged", 1, param_slot_0 };
    static const QMetaData slot_tbl[] = {
	{ "timeChanged(const QTime&)", &slot_0, QMetaData::Public }
    };
    metaObj = QMetaObject::new_metaobject(
	"CounterDialog", parentObject,
	slot_tbl, 1,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_CounterDialog.setMetaObject( metaObj );
    return metaObj;
}

void* CounterDialog::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "CounterDialog" ) )
	return this;
    return CounterDialogBase::qt_cast( clname );
}

bool CounterDialog::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: timeChanged((const QTime&)*((const QTime*)static_QUType_ptr.get(_o+1))); break;
    default:
	return CounterDialogBase::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool CounterDialog::qt_emit( int _id, QUObject* _o )
{
    return CounterDialogBase::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool CounterDialog::qt_property( int id, int f, QVariant* v)
{
    return CounterDialogBase::qt_property( id, f, v);
}

bool CounterDialog::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
