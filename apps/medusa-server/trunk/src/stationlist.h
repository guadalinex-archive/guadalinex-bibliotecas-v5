/***************************************************************************
 *   Copyright (C) 2004 by Emergya, S.C.A.                                   *
 *   info@emergya.info                                                     *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#ifndef STATIONLIST_H
#define STATIONLIST_H 

#include <qlistview.h>

class StationList : public QListView
{
	Q_OBJECT			
public:
	enum ColumnsOrder{ 
		ActiveIconColumn = 0,
		IPColumn ,
		HostNameColumn,
		RemainingTimeColumn,
		UserColumn,
		LoggedUserColumn,
		CommentsColumn
	};
	
	//QString ColumName[7];
	//ColumnName[StationList::ActiveIconColumn] = QString("prueba");
		
		
		
	StationList(QWidget *parent = 0, const char *name = 0);
	QString findSelected();
	bool setNotConnectedIcon(QString hostIP);
	bool updateHostView(QString hostIP, int status = -1, QString hostName = QString::null, QString time = QString::null,
			    QString user = QString::null, QString loginUser = QString::null, QString comments = QString::null );	
	bool addHostView(QString hostIP, QString hostName);	
	bool deleteHostView(QString hostIP);	
	
private:
	bool initialized;
	void createLabels(void);
	//QListViewItemIterator *it;
		
	
	
};
	

class ColorListViewItem :public QListViewItem
{
public:
	ColorListViewItem( QListView* view, const QString& str )
	:QListViewItem( view, str ) 
		{
		}
		
	ColorListViewItem( QListView* view, const QString &str1, const QString &str2, const QString &str3)
	:QListViewItem( view, str1, str2, str3)
	{}
	
	void paintCell(QPainter* p,
		       const QColorGroup& cg,
		       int column,
		       int width,
		       int align)
	{
		bool withColor = false;
		for( QListViewItemIterator it( listView() ); it.current(); ++it ) {
			if ( it.current() == this ) {
				break;
			}
			withColor = !withColor;
		}

		QColorGroup cgcopy(cg);
		if (withColor)
			cgcopy.setColor( QColorGroup::Base, QColor(240, 240, 240) );
		else
			cgcopy.setColor( QColorGroup::Base, white);


		QListViewItem::paintCell(p, cgcopy, column, width, align);
	}
};





#endif
