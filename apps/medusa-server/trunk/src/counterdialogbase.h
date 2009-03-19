/****************************************************************************
** Form interface generated from reading ui file 'counterdialogbase.ui'
**
** Created: mar feb 10 12:55:51 2009
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.7   edited Aug 31 2005 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef COUNTERDIALOGBASE_H
#define COUNTERDIALOGBASE_H

#include <qvariant.h>
#include <qdialog.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QLabel;
class QTimeEdit;
class QLineEdit;
class QCheckBox;
class QPushButton;

class CounterDialogBase : public QDialog
{
    Q_OBJECT

public:
    CounterDialogBase( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~CounterDialogBase();

    QLabel* timeLabel;
    QTimeEdit* timeEdit;
    QLabel* userLabel;
    QLineEdit* userEdit;
    QCheckBox* resetSessionCheck;
    QPushButton* helpButton;
    QPushButton* okButton;
    QPushButton* cancelButton;

protected:
    QGridLayout* CounterDialogBaseLayout;
    QHBoxLayout* layout10;
    QSpacerItem* spacer5;
    QHBoxLayout* layout4;
    QSpacerItem* spacer2;
    QHBoxLayout* Layout1;
    QSpacerItem* Horizontal_Spacing2;

protected slots:
    virtual void languageChange();

};

#endif // COUNTERDIALOGBASE_H
