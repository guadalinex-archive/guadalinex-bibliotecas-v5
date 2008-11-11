#ifndef SENDMESSAGEDIALOG_H
#define SENDMESSAGEDIALOG_H

#include "sendmessagedialogbase.h"

class SendMessageDialog : public SendMessageDialogBase{
   Q_OBJECT
public:
   SendMessageDialog(QWidget *parent = 0, const char *name = 0);
   void clearMessage();

private:
   QString texto;
   QString temp;

private slots:
   void enableSendButton();
   void clearText();
};

#endif
