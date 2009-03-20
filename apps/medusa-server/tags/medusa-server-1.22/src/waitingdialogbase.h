/****************************************************************************
** Form interface generated from reading ui file 'waitingdialogbase.ui'
**
** Created: mar feb 10 12:55:51 2009
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.7   edited Aug 31 2005 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef WAITINGDIALOGBASE_H
#define WAITINGDIALOGBASE_H

#include <qvariant.h>
#include <qdialog.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QPushButton;
class QLabel;
class QProgressBar;

class WaitingDialogBase : public QDialog
{
    Q_OBJECT

public:
    WaitingDialogBase( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~WaitingDialogBase();

    QPushButton* cancelButton;
    QLabel* textLabel;
    QProgressBar* progressBar;

protected:
    QGridLayout* WaitingDialogBaseLayout;
    QHBoxLayout* Layout1;
    QSpacerItem* Horizontal_Spacing2;

protected slots:
    virtual void languageChange();

};

#endif // WAITINGDIALOGBASE_H
