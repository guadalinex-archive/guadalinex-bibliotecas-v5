/****************************************************************************
** Form implementation generated from reading ui file 'gotocelldialog.ui'
**
** Created: Sat Jul 17 01:08:34 2004
**      by: The User Interface Compiler ($Id: gotocelldialog.cpp 57 2004-09-01 11:04:20Z jroncero $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "gotocelldialog.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include "gotocelldialog.ui.h"

/*
 *  Constructs a GoToCellDialog as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
GoToCellDialog::GoToCellDialog( QWidget* parent, const char* name, bool modal, WFlags fl )
    : QDialog( parent, name, modal, fl )
{
    if ( !name )
	setName( "GoToCellDialog" );
    GoToCellDialogLayout = new QVBoxLayout( this, 11, 6, "GoToCellDialogLayout"); 

    topLayout = new QHBoxLayout( 0, 0, 6, "topLayout"); 

    cellLocationLabel = new QLabel( this, "cellLocationLabel" );
    topLayout->addWidget( cellLocationLabel );

    lineEdit = new QLineEdit( this, "lineEdit" );
    topLayout->addWidget( lineEdit );
    GoToCellDialogLayout->addLayout( topLayout );

    bottomLayout = new QHBoxLayout( 0, 0, 6, "bottomLayout"); 
    QSpacerItem* spacer = new QSpacerItem( 10, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    bottomLayout->addItem( spacer );

    okButton = new QPushButton( this, "okButton" );
    okButton->setEnabled( FALSE );
    okButton->setDefault( TRUE );
    bottomLayout->addWidget( okButton );

    cancelButton = new QPushButton( this, "cancelButton" );
    bottomLayout->addWidget( cancelButton );
    GoToCellDialogLayout->addLayout( bottomLayout );
    languageChange();
    resize( QSize(232, 86).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    // signals and slots connections
    connect( lineEdit, SIGNAL( textChanged(const QString&) ), this, SLOT( enableOkButton() ) );
    connect( okButton, SIGNAL( clicked() ), this, SLOT( accept() ) );
    connect( cancelButton, SIGNAL( clicked() ), this, SLOT( reject() ) );

    // buddies
    cellLocationLabel->setBuddy( lineEdit );
    init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
GoToCellDialog::~GoToCellDialog()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void GoToCellDialog::languageChange()
{
    setCaption( tr( "Go to Cell" ) );
    cellLocationLabel->setText( tr( "&Cell Location:" ) );
    okButton->setText( tr( "OK" ) );
    cancelButton->setText( tr( "Cancel" ) );
}

