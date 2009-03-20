/****************************************************************************
** Form interface generated from reading ui file 'sendmessagedialogbase.ui'
**
** Created: mar feb 10 12:55:51 2009
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.7   edited Aug 31 2005 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef SENDMESSAGEDIALOGBASE_H
#define SENDMESSAGEDIALOGBASE_H

#include <qvariant.h>
#include <qpixmap.h>
#include <qdialog.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QPushButton;
class QLabel;
class QTextEdit;

class SendMessageDialogBase : public QDialog
{
    Q_OBJECT

public:
    SendMessageDialogBase( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~SendMessageDialogBase();

    QPushButton* cancelButton;
    QLabel* textLabel1;
    QTextEdit* textMessage;
    QLabel* charsLabel;
    QPushButton* sendButton;

protected:

protected slots:
    virtual void languageChange();

private:
    QPixmap image0;

private slots:
    virtual void enableSendButton();

};

#endif // SENDMESSAGEDIALOGBASE_H
