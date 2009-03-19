/****************************************************************************
** Form implementation generated from reading ui file 'waitingdialogbase.ui'
**
** Created: mar feb 10 12:56:14 2009
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.7   edited Aug 31 2005 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "waitingdialogbase.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qprogressbar.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>

/*
 *  Constructs a WaitingDialogBase as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
WaitingDialogBase::WaitingDialogBase( QWidget* parent, const char* name, bool modal, WFlags fl )
    : QDialog( parent, name, modal, fl )
{
    if ( !name )
	setName( "WaitingDialogBase" );
    setSizeGripEnabled( TRUE );
    WaitingDialogBaseLayout = new QGridLayout( this, 1, 1, 11, 6, "WaitingDialogBaseLayout"); 

    Layout1 = new QHBoxLayout( 0, 0, 6, "Layout1"); 
    Horizontal_Spacing2 = new QSpacerItem( 261, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    Layout1->addItem( Horizontal_Spacing2 );

    cancelButton = new QPushButton( this, "cancelButton" );
    cancelButton->setAutoDefault( TRUE );
    Layout1->addWidget( cancelButton );

    WaitingDialogBaseLayout->addLayout( Layout1, 2, 0 );

    textLabel = new QLabel( this, "textLabel" );
    textLabel->setAlignment( int( QLabel::WordBreak | QLabel::AlignTop ) );

    WaitingDialogBaseLayout->addWidget( textLabel, 0, 0 );

    progressBar = new QProgressBar( this, "progressBar" );
    progressBar->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)4, (QSizePolicy::SizeType)0, 0, 0, progressBar->sizePolicy().hasHeightForWidth() ) );

    WaitingDialogBaseLayout->addWidget( progressBar, 1, 0 );
    languageChange();
    resize( QSize(361, 192).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    // signals and slots connections
    connect( cancelButton, SIGNAL( clicked() ), this, SLOT( reject() ) );
}

/*
 *  Destroys the object and frees any allocated resources
 */
WaitingDialogBase::~WaitingDialogBase()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void WaitingDialogBase::languageChange()
{
    setCaption( tr( "MyDialog" ) );
    cancelButton->setText( tr( "&Cancel" ) );
    cancelButton->setAccel( QKeySequence( QString::null ) );
    textLabel->setText( tr( "textLabel2" ) );
}

