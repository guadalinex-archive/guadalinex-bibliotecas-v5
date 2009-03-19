/****************************************************************************
** StationList meta object code from reading C++ file 'stationlist.h'
**
** Created: Tue Feb 10 12:56:19 2009
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.7   edited Oct 19 16:22 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "stationlist.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *StationList::className() const
{
    return "StationList";
}

QMetaObject *StationList::metaObj = 0;
static QMetaObjectCleanUp cleanUp_StationList( "StationList", &StationList::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString StationList::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "StationList", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString StationList::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "StationList", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* StationList::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QListView::staticMetaObject();
    metaObj = QMetaObject::new_metaobject(
	"StationList", parentObject,
	0, 0,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_StationList.setMetaObject( metaObj );
    return metaObj;
}

void* StationList::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "StationList" ) )
	return this;
    return QListView::qt_cast( clname );
}

bool StationList::qt_invoke( int _id, QUObject* _o )
{
    return QListView::qt_invoke(_id,_o);
}

bool StationList::qt_emit( int _id, QUObject* _o )
{
    return QListView::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool StationList::qt_property( int id, int f, QVariant* v)
{
    return QListView::qt_property( id, f, v);
}

bool StationList::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
