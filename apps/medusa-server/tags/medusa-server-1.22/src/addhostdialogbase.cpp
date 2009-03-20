/****************************************************************************
** Form implementation generated from reading ui file 'addhostdialogbase.ui'
**
** Created: mar feb 10 12:56:09 2009
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.7   edited Aug 31 2005 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "addhostdialogbase.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qlineedit.h>
#include <qlabel.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>

/*
 *  Constructs a AddHostDialogBase as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
AddHostDialogBase::AddHostDialogBase( QWidget* parent, const char* name, bool modal, WFlags fl )
    : QDialog( parent, name, modal, fl )
{
    if ( !name )
	setName( "AddHostDialogBase" );
    AddHostDialogBaseLayout = new QGridLayout( this, 1, 1, 11, 6, "AddHostDialogBaseLayout"); 
    spacer1 = new QSpacerItem( 217, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    AddHostDialogBaseLayout->addMultiCell( spacer1, 3, 3, 0, 1 );

    okButton = new QPushButton( this, "okButton" );
    okButton->setEnabled( FALSE );

    AddHostDialogBaseLayout->addWidget( okButton, 3, 2 );

    cancelButton = new QPushButton( this, "cancelButton" );

    AddHostDialogBaseLayout->addWidget( cancelButton, 3, 3 );

    addressEdit = new QLineEdit( this, "addressEdit" );

    AddHostDialogBaseLayout->addMultiCellWidget( addressEdit, 0, 0, 1, 3 );

    hostEdit = new QLineEdit( this, "hostEdit" );

    AddHostDialogBaseLayout->addMultiCellWidget( hostEdit, 1, 1, 1, 3 );

    macEdit = new QLineEdit( this, "macEdit" );

    AddHostDialogBaseLayout->addMultiCellWidget( macEdit, 2, 2, 1, 3 );

    macLabel = new QLabel( this, "macLabel" );

    AddHostDialogBaseLayout->addWidget( macLabel, 2, 0 );

    addressLabel = new QLabel( this, "addressLabel" );

    AddHostDialogBaseLayout->addWidget( addressLabel, 0, 0 );

    nameLabel = new QLabel( this, "nameLabel" );

    AddHostDialogBaseLayout->addWidget( nameLabel, 1, 0 );
    languageChange();
    resize( QSize(360, 133).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    // signals and slots connections
    connect( okButton, SIGNAL( clicked() ), this, SLOT( accept() ) );
    connect( cancelButton, SIGNAL( clicked() ), this, SLOT( reject() ) );
    connect( addressEdit, SIGNAL( textChanged(const QString&) ), this, SLOT( enableOkButton() ) );

    // tab order
    setTabOrder( addressEdit, hostEdit );
    setTabOrder( hostEdit, macEdit );
    setTabOrder( macEdit, okButton );
    setTabOrder( okButton, cancelButton );

    // buddies
    addressLabel->setBuddy( hostEdit );
    nameLabel->setBuddy( hostEdit );
}

/*
 *  Destroys the object and frees any allocated resources
 */
AddHostDialogBase::~AddHostDialogBase()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void AddHostDialogBase::languageChange()
{
    setCaption( tr( "dialog" ) );
    okButton->setText( tr( "OK" ) );
    cancelButton->setText( tr( "Cancel" ) );
    QToolTip::add( addressEdit, tr( "Ip address in decimal format" ) );
    macLabel->setText( tr( "MAC" ) );
    QWhatsThis::add( macLabel, tr( "Insert the MAC Address of this workstation" ) );
    addressLabel->setText( tr( "&Address (IP)" ) );
    QWhatsThis::add( addressLabel, tr( "Insert the IP address of the workstation" ) );
    nameLabel->setText( tr( "&Host Name" ) );
    QWhatsThis::add( nameLabel, tr( "Insert the preferred name for this workstation" ) );
}

void AddHostDialogBase::clearItems()
{
    qWarning( "AddHostDialogBase::clearItems(): Not implemented yet" );
}

void AddHostDialogBase::enableOkButton()
{
    qWarning( "AddHostDialogBase::enableOkButton(): Not implemented yet" );
}

