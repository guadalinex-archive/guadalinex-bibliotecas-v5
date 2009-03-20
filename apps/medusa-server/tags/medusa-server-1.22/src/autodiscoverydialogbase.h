/****************************************************************************
** Form interface generated from reading ui file 'autodiscoverydialogbase.ui'
**
** Created: mar feb 10 12:55:51 2009
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.7   edited Aug 31 2005 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef AUTODISCOVERYDIALOGBASE_H
#define AUTODISCOVERYDIALOGBASE_H

#include <qvariant.h>
#include <qdialog.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QLineEdit;
class QLabel;
class QProgressBar;
class QPushButton;

class AutoDiscoveryDialogBase : public QDialog
{
    Q_OBJECT

public:
    AutoDiscoveryDialogBase( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~AutoDiscoveryDialogBase();

    QLineEdit* startEdit1;
    QLineEdit* startEdit2;
    QLineEdit* startEdit3;
    QLineEdit* startEdit4;
    QLineEdit* endEdit1;
    QLineEdit* endEdit2;
    QLineEdit* endEdit3;
    QLineEdit* endEdit4;
    QLabel* endLabel;
    QLabel* startLabel;
    QProgressBar* progressBar;
    QPushButton* stopButton;
    QPushButton* searchButton;
    QPushButton* helpButton;
    QPushButton* cancelButton;

protected:
    QGridLayout* AutoDiscoveryDialogBaseLayout;
    QHBoxLayout* layout15;
    QHBoxLayout* layout16;
    QHBoxLayout* Layout1;
    QSpacerItem* Horizontal_Spacing2;

protected slots:
    virtual void languageChange();

};

#endif // AUTODISCOVERYDIALOGBASE_H
