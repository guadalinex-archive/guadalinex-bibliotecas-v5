#include <qtextedit.h>
#include <qlabel.h>
#include <qpushbutton.h>
#include <qvalidator.h>
#include <iostream.h>

#include "sendmessagedialog.h"

SendMessageDialog::SendMessageDialog(QWidget *parent, const char *name )
      : SendMessageDialogBase(parent, name)
{
}

void SendMessageDialog::enableSendButton()
{
   if (textMessage->length() != 0){
      sendButton->setEnabled(true);
      if (textMessage->length() > 120){
         textMessage->setText(texto);
         textMessage->moveCursor(QTextEdit::MoveEnd, false);
      }
      else{
         int van = textMessage->length();
         int quedan = 120 - van;
         temp.setNum(quedan);
         charsLabel->setText(temp);
         texto = textMessage->text();
      }
         
   }
   else{
      charsLabel->setText("120");
      sendButton->setEnabled(false);
   }
}

void SendMessageDialog::clearText()
{
   textMessage->clear();
}

