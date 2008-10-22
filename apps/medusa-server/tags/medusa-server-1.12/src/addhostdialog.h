#ifndef ADDHOSTDIALOG_H
#define ADDHOSTDIALOG_H

#include "addhostdialogbase.h"

class AddHostDialog : public AddHostDialogBase
{
	Q_OBJECT
public:
	AddHostDialog(QWidget *parent = 0, const char *name = 0);
	void clearItems();

private slots:
	void enableOkButton();
};

#endif 
