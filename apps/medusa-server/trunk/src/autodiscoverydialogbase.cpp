/****************************************************************************
** Form implementation generated from reading ui file 'autodiscoverydialogbase.ui'
**
** Created: mar feb 10 12:56:13 2009
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.7   edited Aug 31 2005 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "autodiscoverydialogbase.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qlineedit.h>
#include <qlabel.h>
#include <qprogressbar.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>

/*
 *  Constructs a AutoDiscoveryDialogBase as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
AutoDiscoveryDialogBase::AutoDiscoveryDialogBase( QWidget* parent, const char* name, bool modal, WFlags fl )
    : QDialog( parent, name, modal, fl )
{
    if ( !name )
	setName( "AutoDiscoveryDialogBase" );
    setSizeGripEnabled( TRUE );
    AutoDiscoveryDialogBaseLayout = new QGridLayout( this, 1, 1, 11, 6, "AutoDiscoveryDialogBaseLayout"); 

    layout15 = new QHBoxLayout( 0, 0, 6, "layout15"); 

    startEdit1 = new QLineEdit( this, "startEdit1" );
    layout15->addWidget( startEdit1 );

    startEdit2 = new QLineEdit( this, "startEdit2" );
    layout15->addWidget( startEdit2 );

    startEdit3 = new QLineEdit( this, "startEdit3" );
    layout15->addWidget( startEdit3 );

    startEdit4 = new QLineEdit( this, "startEdit4" );
    layout15->addWidget( startEdit4 );

    AutoDiscoveryDialogBaseLayout->addLayout( layout15, 0, 1 );

    layout16 = new QHBoxLayout( 0, 0, 6, "layout16"); 

    endEdit1 = new QLineEdit( this, "endEdit1" );
    layout16->addWidget( endEdit1 );

    endEdit2 = new QLineEdit( this, "endEdit2" );
    layout16->addWidget( endEdit2 );

    endEdit3 = new QLineEdit( this, "endEdit3" );
    layout16->addWidget( endEdit3 );

    endEdit4 = new QLineEdit( this, "endEdit4" );
    layout16->addWidget( endEdit4 );

    AutoDiscoveryDialogBaseLayout->addLayout( layout16, 1, 1 );

    endLabel = new QLabel( this, "endLabel" );

    AutoDiscoveryDialogBaseLayout->addWidget( endLabel, 1, 0 );

    startLabel = new QLabel( this, "startLabel" );

    AutoDiscoveryDialogBaseLayout->addWidget( startLabel, 0, 0 );

    progressBar = new QProgressBar( this, "progressBar" );

    AutoDiscoveryDialogBaseLayout->addMultiCellWidget( progressBar, 2, 2, 0, 2 );

    stopButton = new QPushButton( this, "stopButton" );

    AutoDiscoveryDialogBaseLayout->addWidget( stopButton, 1, 2 );

    searchButton = new QPushButton( this, "searchButton" );

    AutoDiscoveryDialogBaseLayout->addWidget( searchButton, 0, 2 );

    Layout1 = new QHBoxLayout( 0, 0, 6, "Layout1"); 

    helpButton = new QPushButton( this, "helpButton" );
    helpButton->setEnabled( FALSE );
    helpButton->setAutoDefault( TRUE );
    Layout1->addWidget( helpButton );
    Horizontal_Spacing2 = new QSpacerItem( 20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    Layout1->addItem( Horizontal_Spacing2 );

    cancelButton = new QPushButton( this, "cancelButton" );
    cancelButton->setAutoDefault( TRUE );
    Layout1->addWidget( cancelButton );

    AutoDiscoveryDialogBaseLayout->addMultiCellLayout( Layout1, 3, 3, 0, 2 );
    languageChange();
    resize( QSize(325, 137).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    // signals and slots connections
    connect( cancelButton, SIGNAL( clicked() ), this, SLOT( reject() ) );

    // tab order
    setTabOrder( startEdit1, startEdit2 );
    setTabOrder( startEdit2, startEdit3 );
    setTabOrder( startEdit3, startEdit4 );
    setTabOrder( startEdit4, endEdit1 );
    setTabOrder( endEdit1, endEdit2 );
    setTabOrder( endEdit2, endEdit3 );
    setTabOrder( endEdit3, endEdit4 );
    setTabOrder( endEdit4, searchButton );
    setTabOrder( searchButton, stopButton );
    setTabOrder( stopButton, cancelButton );
    setTabOrder( cancelButton, helpButton );
}

/*
 *  Destroys the object and frees any allocated resources
 */
AutoDiscoveryDialogBase::~AutoDiscoveryDialogBase()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void AutoDiscoveryDialogBase::languageChange()
{
    setCaption( tr( "Auto Discovery" ) );
    endLabel->setText( tr( "End IP" ) );
    startLabel->setText( tr( "Start IP" ) );
    stopButton->setText( tr( "Stop" ) );
    searchButton->setText( tr( "Search" ) );
    helpButton->setText( tr( "&Help" ) );
    helpButton->setAccel( QKeySequence( tr( "F1" ) ) );
    cancelButton->setText( tr( "&Cancel" ) );
    cancelButton->setAccel( QKeySequence( QString::null ) );
}

