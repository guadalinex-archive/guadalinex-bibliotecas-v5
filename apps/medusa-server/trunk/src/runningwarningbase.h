/****************************************************************************
** Form interface generated from reading ui file 'runningwarningbase.ui'
**
** Created: mar feb 10 12:55:51 2009
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.7   edited Aug 31 2005 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef RUNNINGWARNINGBASE_H
#define RUNNINGWARNINGBASE_H

#include <qvariant.h>
#include <qpixmap.h>
#include <qdialog.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QPushButton;
class QCheckBox;
class QLabel;

class RunningWarningBase : public QDialog
{
    Q_OBJECT

public:
    RunningWarningBase( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~RunningWarningBase();

    QPushButton* helpButton;
    QPushButton* okButton;
    QPushButton* cancelButton;
    QCheckBox* dontCheck;
    QLabel* imageLabel;
    QLabel* warningLabel;

protected:
    QGridLayout* RunningWarningBaseLayout;
    QHBoxLayout* Layout1;
    QSpacerItem* Horizontal_Spacing2;
    QHBoxLayout* layout13;

protected slots:
    virtual void languageChange();

private:
    QPixmap image0;

};

#endif // RUNNINGWARNINGBASE_H
