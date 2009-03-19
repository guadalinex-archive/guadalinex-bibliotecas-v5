/****************************************************************************
** Form interface generated from reading ui file 'configurationdialogbase.ui'
**
** Created: mar feb 10 12:55:51 2009
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.7   edited Aug 31 2005 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef CONFIGURATIONDIALOGBASE_H
#define CONFIGURATIONDIALOGBASE_H

#include <qvariant.h>
#include <qdialog.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QTabWidget;
class QWidget;
class QGroupBox;
class QLabel;
class QLineEdit;
class QCheckBox;
class QToolButton;
class QPushButton;
class QLCDNumber;
class QSlider;

class ConfigurationDialogBase : public QDialog
{
    Q_OBJECT

public:
    ConfigurationDialogBase( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~ConfigurationDialogBase();

    QTabWidget* tabWidget;
    QWidget* mainTab;
    QGroupBox* clientGroupBox;
    QLabel* notifyPortLabel;
    QLabel* controlPortLabel;
    QLineEdit* notifyPortEdit;
    QLineEdit* controlPortEdit;
    QLineEdit* defaultTimeEdit;
    QLabel* defaultTimeLabel;
    QCheckBox* askCloseCheckbox;
    QGroupBox* logGroupBox;
    QToolButton* logFileButton;
    QLineEdit* logFileEdit;
    QLabel* logFileLabel;
    QWidget* extraTab;
    QGroupBox* fontBox;
    QPushButton* fontButton;
    QLabel* fontListViewLabel;
    QLineEdit* fontEdit;
    QGroupBox* miscBox;
    QCheckBox* askStatusBox;
    QLCDNumber* askStatusLCD;
    QLabel* askStatusLabel;
    QSlider* askStatusSlider;
    QPushButton* okButton;
    QPushButton* cancelButton;
    QPushButton* helpButton;

public slots:
    virtual void defaultTimeLabel_destroyed( QObject * );
    virtual void notifyPortLabel_destroyed( QObject * );

protected:
    QGridLayout* ConfigurationDialogBaseLayout;
    QSpacerItem* Horizontal_Spacing2;
    QGridLayout* mainTabLayout;
    QGridLayout* extraTabLayout;

protected slots:
    virtual void languageChange();

};

#endif // CONFIGURATIONDIALOGBASE_H
