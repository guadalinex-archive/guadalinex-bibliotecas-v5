/****************************************************************************
** Form implementation generated from reading ui file 'counterdialogbase.ui'
**
** Created: mar feb 10 12:56:12 2009
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.7   edited Aug 31 2005 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "counterdialogbase.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qdatetimeedit.h>
#include <qlineedit.h>
#include <qcheckbox.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>

/*
 *  Constructs a CounterDialogBase as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
CounterDialogBase::CounterDialogBase( QWidget* parent, const char* name, bool modal, WFlags fl )
    : QDialog( parent, name, modal, fl )
{
    if ( !name )
	setName( "CounterDialogBase" );
    setModal( TRUE );
    CounterDialogBaseLayout = new QGridLayout( this, 1, 1, 11, 6, "CounterDialogBaseLayout"); 

    layout10 = new QHBoxLayout( 0, 0, 6, "layout10"); 

    timeLabel = new QLabel( this, "timeLabel" );
    timeLabel->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)5, (QSizePolicy::SizeType)5, 0, 0, timeLabel->sizePolicy().hasHeightForWidth() ) );
    layout10->addWidget( timeLabel );
    spacer5 = new QSpacerItem( 31, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layout10->addItem( spacer5 );

    timeEdit = new QTimeEdit( this, "timeEdit" );
    timeEdit->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)1, (QSizePolicy::SizeType)0, 0, 0, timeEdit->sizePolicy().hasHeightForWidth() ) );
    timeEdit->setMinimumSize( QSize( 45, 0 ) );
    timeEdit->setDisplay( int( QTimeEdit::Seconds | QTimeEdit::Minutes | QTimeEdit::Hours ) );
    layout10->addWidget( timeEdit );

    CounterDialogBaseLayout->addLayout( layout10, 1, 0 );

    layout4 = new QHBoxLayout( 0, 0, 1, "layout4"); 

    userLabel = new QLabel( this, "userLabel" );
    userLabel->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)5, (QSizePolicy::SizeType)5, 0, 0, userLabel->sizePolicy().hasHeightForWidth() ) );
    layout4->addWidget( userLabel );
    spacer2 = new QSpacerItem( 31, 20, QSizePolicy::Fixed, QSizePolicy::Minimum );
    layout4->addItem( spacer2 );

    userEdit = new QLineEdit( this, "userEdit" );
    userEdit->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)7, (QSizePolicy::SizeType)0, 0, 0, userEdit->sizePolicy().hasHeightForWidth() ) );
    layout4->addWidget( userEdit );

    CounterDialogBaseLayout->addLayout( layout4, 0, 0 );

    resetSessionCheck = new QCheckBox( this, "resetSessionCheck" );

    CounterDialogBaseLayout->addWidget( resetSessionCheck, 2, 0 );

    Layout1 = new QHBoxLayout( 0, 0, 3, "Layout1"); 

    helpButton = new QPushButton( this, "helpButton" );
    helpButton->setAutoDefault( TRUE );
    Layout1->addWidget( helpButton );
    Horizontal_Spacing2 = new QSpacerItem( 142, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    Layout1->addItem( Horizontal_Spacing2 );

    okButton = new QPushButton( this, "okButton" );
    okButton->setAutoDefault( TRUE );
    okButton->setDefault( TRUE );
    Layout1->addWidget( okButton );

    cancelButton = new QPushButton( this, "cancelButton" );
    cancelButton->setAutoDefault( TRUE );
    Layout1->addWidget( cancelButton );

    CounterDialogBaseLayout->addLayout( Layout1, 3, 0 );
    languageChange();
    resize( QSize(432, 134).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    // signals and slots connections
    connect( okButton, SIGNAL( clicked() ), this, SLOT( accept() ) );
    connect( cancelButton, SIGNAL( clicked() ), this, SLOT( reject() ) );

    // tab order
    setTabOrder( userEdit, timeEdit );
    setTabOrder( timeEdit, okButton );
    setTabOrder( okButton, cancelButton );
    setTabOrder( cancelButton, helpButton );
}

/*
 *  Destroys the object and frees any allocated resources
 */
CounterDialogBase::~CounterDialogBase()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void CounterDialogBase::languageChange()
{
    setCaption( tr( "MyDialog" ) );
    timeLabel->setText( tr( "textLabel4" ) );
    userLabel->setText( tr( "Nombre de Usuario" ) );
    resetSessionCheck->setText( tr( "Reset Session" ) );
    helpButton->setText( tr( "&Help" ) );
    helpButton->setAccel( QKeySequence( tr( "F1" ) ) );
    okButton->setText( tr( "&OK" ) );
    okButton->setAccel( QKeySequence( QString::null ) );
    cancelButton->setText( tr( "&Cancel" ) );
    cancelButton->setAccel( QKeySequence( QString::null ) );
}

