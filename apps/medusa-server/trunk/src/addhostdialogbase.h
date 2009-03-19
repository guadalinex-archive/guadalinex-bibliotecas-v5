/****************************************************************************
** Form interface generated from reading ui file 'addhostdialogbase.ui'
**
** Created: mar feb 10 12:55:51 2009
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.7   edited Aug 31 2005 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef ADDHOSTDIALOGBASE_H
#define ADDHOSTDIALOGBASE_H

#include <qvariant.h>
#include <qdialog.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QPushButton;
class QLineEdit;
class QLabel;

class AddHostDialogBase : public QDialog
{
    Q_OBJECT

public:
    AddHostDialogBase( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~AddHostDialogBase();

    QPushButton* okButton;
    QPushButton* cancelButton;
    QLineEdit* addressEdit;
    QLineEdit* hostEdit;
    QLineEdit* macEdit;
    QLabel* macLabel;
    QLabel* addressLabel;
    QLabel* nameLabel;

public slots:
    virtual void clearItems();
    virtual void enableOkButton();

protected:
    QGridLayout* AddHostDialogBaseLayout;
    QSpacerItem* spacer1;

protected slots:
    virtual void languageChange();

};

#endif // ADDHOSTDIALOGBASE_H
