#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <qmainwindow.h>
#include <qstringlist.h>

#include "workstationgroup.h"

class QAction;
class QLabel;
class QListViewItem;
class StationList;
class AddHostDialog;
class ConfigurationDialog;
class QFont;
class OSDWidget;

class MainWindow:public QMainWindow {
	Q_OBJECT 
public:
	MainWindow(QWidget * parent = 0, const char *name = 0);
	Q_UINT16 getControlPort();
	QString getLogFile();
	bool getAskStatus();
	int getAskStatusTime();
		
protected:
	void closeEvent(QCloseEvent * event);
	void contextMenuEvent(QContextMenuEvent * event);
	void showOSDMsg(const QString &text);

	
		
private slots:
	void deleteHost();
	void editHost(); 
	void addHost();
	void autoDiscovery();
	void discoveredStation(QString host);
	void editSettings();
	void newFile();
	void open();
	bool save();
	bool saveAs();
	void about();
	void openRecentFile(int param);
	void blockAll();
	void updateView(QString host, long time);
	void blockSelected();
	void unblockAll();
	void activateSelectedHost();
	void blockSelectedSlot();
	void unblockSelectedSlot();
	void updateViewError(QString host, QString msg);
	void updateViewStatus(QString host, int status);
	void updateViewUser(const QString &host, const QString &user);
	void updateViewLoginUser(const QString &host, const QString &user);
	void getLoginUser();
	


private:	
	void showSimpleWarningBox(const QString &text);
	bool needToSave();
	void configModified();
	void createActions();
	void createMenus();
	void createToolBars();
	void createStatusBar();
	void readSettings();
	void writeSettings();
	bool maybeSave();
	void loadFile(const QString & fileName);
	void saveFile(const QString & fileName);
	void setCurrentFile(const QString & fileName);
	void updateRecentFileItems();
	QString strippedName(const QString & fullFileName);
	QString appTitle;

	
	// Dialogs
	AddHostDialog *addHostDialog;
	ConfigurationDialog *configDialog;
	
	QListViewItem *element;

	QLabel *locationLabel;
	QLabel *formulaLabel;
	QLabel *modLabel;
	QStringList recentFiles;
	QString curFile;
	QString fileFilters;
	bool modified;

	enum { MaxRecentFiles = 5 };
	int recentFileIds[MaxRecentFiles];

	// Menus
	QPopupMenu *fileMenu;
	QPopupMenu *editMenu;
	QPopupMenu *selectSubMenu;
	QPopupMenu *hostsMenu;
	QPopupMenu *actionsMenu;
	QPopupMenu *optionsMenu;
	QPopupMenu *helpMenu;

	// Toolbars
	QToolBar *fileToolBar;
	QToolBar *editToolBar;
	QToolBar *hostToolBar;
	QToolBar *actionToolBar;
	
	// File
	QAction *newAct;
	QAction *openAct;
	QAction *saveAct;
	QAction *saveAsAct;
	QAction *exitAct;

	// Edit
	QAction *cutAct;
	QAction *copyAct;
	QAction *pasteAct;
	QAction *deleteAct;
	QAction *selectRowAct;
	QAction *selectColumnAct;
	QAction *selectAllAct;
	
	// Hosts
	QAction *addHostAct;
	QAction *editHostAct;
	QAction *deleteHostAct;
	
	// actions
	QAction *blockAllAct;
	QAction *blockSelectedAct;
	QAction *unblockAllAct;
	QAction *unblockSelectedAct;
	QAction *setTimerAct;
	QAction *getUserAct;

	// Settings
	QAction *autoDisAct;
	QAction *editSetAct;

	QAction *findAct;
	QAction *goToCellAct;
	QAction *recalculateAct;
	QAction *sortAct;

	// Help
	QAction *aboutAct;
	QAction *aboutQtAct;
	
	
	WorkStationGroup wsGroup;
	// Holds the list
	StationList *stationlist;
	
	// Settings
	
	// should we close the app 
	bool askClosing;
	Q_UINT16 notifyPort;
	Q_UINT16 controlPort;
	QFont listFont;
	QString logFileName;
	bool askStatus;
	int askStatusTime;
	
	OSDWidget* osd;	
};

#endif
