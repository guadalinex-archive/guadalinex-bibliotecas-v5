#include <qlineedit.h>
#include <qpushbutton.h>
#include <qvalidator.h>

#include "addhostdialog.h"

AddHostDialog::AddHostDialog(QWidget *parent, const char *name )
		: AddHostDialogBase(parent, name)
{
	QRegExp regExp("\\d{1,3}\\.\\d{1,3}\\.\\d{1,3}\\.\\d{1,3}");
	addressEdit->setValidator(new QRegExpValidator(regExp, this));
	setCaption(tr("Add New Host"));
}

void AddHostDialog::enableOkButton()
{
	okButton->setEnabled(hostEdit->hasAcceptableInput());
}

void AddHostDialog::clearItems()
{
	addressEdit->clear();
}


