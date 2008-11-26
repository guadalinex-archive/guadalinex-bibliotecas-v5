/****************************************************************************
** Form interface generated from reading ui file 'gotocelldialog.ui'
**
** Created: Sat Jul 17 01:07:13 2004
**      by: The User Interface Compiler ($Id: gotocelldialog.h 57 2004-09-01 11:04:20Z jroncero $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef GOTOCELLDIALOG_H
#define GOTOCELLDIALOG_H

#include <qvariant.h>
#include <qdialog.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QLabel;
class QLineEdit;
class QPushButton;

class GoToCellDialog : public QDialog
{
    Q_OBJECT

public:
    GoToCellDialog( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~GoToCellDialog();

    QLabel* cellLocationLabel;
    QLineEdit* lineEdit;
    QPushButton* okButton;
    QPushButton* cancelButton;

public slots:
    virtual void enableOkButton();

protected:
    QVBoxLayout* GoToCellDialogLayout;
    QHBoxLayout* topLayout;
    QHBoxLayout* bottomLayout;

protected slots:
    virtual void languageChange();

private:
    void init();

};

#endif // GOTOCELLDIALOG_H
