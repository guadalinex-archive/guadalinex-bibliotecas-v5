/****************************************************************************
** Form implementation generated from reading ui file 'configurationdialogbase.ui'
**
** Created: mar feb 10 12:56:10 2009
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.7   edited Aug 31 2005 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "configurationdialogbase.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qtabwidget.h>
#include <qwidget.h>
#include <qgroupbox.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qcheckbox.h>
#include <qtoolbutton.h>
#include <qlcdnumber.h>
#include <qslider.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include "configurationdialogbase.ui.h"

/*
 *  Constructs a ConfigurationDialogBase as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
ConfigurationDialogBase::ConfigurationDialogBase( QWidget* parent, const char* name, bool modal, WFlags fl )
    : QDialog( parent, name, modal, fl )
{
    if ( !name )
	setName( "ConfigurationDialogBase" );
    setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)1, (QSizePolicy::SizeType)1, 0, 0, sizePolicy().hasHeightForWidth() ) );
    setMinimumSize( QSize( 500, 320 ) );
    setSizeGripEnabled( TRUE );
    ConfigurationDialogBaseLayout = new QGridLayout( this, 1, 1, 11, 6, "ConfigurationDialogBaseLayout"); 

    tabWidget = new QTabWidget( this, "tabWidget" );
    tabWidget->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)5, (QSizePolicy::SizeType)5, 0, 0, tabWidget->sizePolicy().hasHeightForWidth() ) );
    tabWidget->setMinimumSize( QSize( 0, 0 ) );

    mainTab = new QWidget( tabWidget, "mainTab" );
    mainTabLayout = new QGridLayout( mainTab, 1, 1, 11, 6, "mainTabLayout"); 

    clientGroupBox = new QGroupBox( mainTab, "clientGroupBox" );
    clientGroupBox->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)7, (QSizePolicy::SizeType)3, 0, 0, clientGroupBox->sizePolicy().hasHeightForWidth() ) );

    notifyPortLabel = new QLabel( clientGroupBox, "notifyPortLabel" );
    notifyPortLabel->setGeometry( QRect( 10, 50, 150, 22 ) );

    controlPortLabel = new QLabel( clientGroupBox, "controlPortLabel" );
    controlPortLabel->setGeometry( QRect( 10, 20, 150, 22 ) );

    notifyPortEdit = new QLineEdit( clientGroupBox, "notifyPortEdit" );
    notifyPortEdit->setGeometry( QRect( 370, 50, 60, 22 ) );
    notifyPortEdit->setAlignment( int( QLineEdit::AlignRight ) );

    controlPortEdit = new QLineEdit( clientGroupBox, "controlPortEdit" );
    controlPortEdit->setGeometry( QRect( 370, 20, 60, 22 ) );
    controlPortEdit->setAlignment( int( QLineEdit::AlignRight ) );

    defaultTimeEdit = new QLineEdit( clientGroupBox, "defaultTimeEdit" );
    defaultTimeEdit->setGeometry( QRect( 370, 80, 60, 22 ) );
    defaultTimeEdit->setFrameShape( QLineEdit::LineEditPanel );
    defaultTimeEdit->setFrameShadow( QLineEdit::Sunken );
    defaultTimeEdit->setAlignment( int( QLineEdit::AlignRight ) );

    defaultTimeLabel = new QLabel( clientGroupBox, "defaultTimeLabel" );
    defaultTimeLabel->setGeometry( QRect( 10, 80, 120, 21 ) );

    mainTabLayout->addWidget( clientGroupBox, 0, 0 );

    askCloseCheckbox = new QCheckBox( mainTab, "askCloseCheckbox" );

    mainTabLayout->addWidget( askCloseCheckbox, 1, 0 );

    logGroupBox = new QGroupBox( mainTab, "logGroupBox" );
    logGroupBox->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)7, (QSizePolicy::SizeType)7, 0, 0, logGroupBox->sizePolicy().hasHeightForWidth() ) );
    logGroupBox->setFrameShape( QGroupBox::GroupBoxPanel );

    logFileButton = new QToolButton( logGroupBox, "logFileButton" );
    logFileButton->setGeometry( QRect( 390, 30, 41, 21 ) );

    logFileEdit = new QLineEdit( logGroupBox, "logFileEdit" );
    logFileEdit->setGeometry( QRect( 111, 30, 270, 21 ) );

    logFileLabel = new QLabel( logGroupBox, "logFileLabel" );
    logFileLabel->setGeometry( QRect( 10, 30, 91, 21 ) );

    mainTabLayout->addWidget( logGroupBox, 2, 0 );
    tabWidget->insertTab( mainTab, QString::fromLatin1("") );

    extraTab = new QWidget( tabWidget, "extraTab" );
    extraTabLayout = new QGridLayout( extraTab, 1, 1, 11, 6, "extraTabLayout"); 

    fontBox = new QGroupBox( extraTab, "fontBox" );

    fontButton = new QPushButton( fontBox, "fontButton" );
    fontButton->setGeometry( QRect( 357, 21, 80, 24 ) );

    fontListViewLabel = new QLabel( fontBox, "fontListViewLabel" );
    fontListViewLabel->setGeometry( QRect( 9, 21, 100, 24 ) );

    fontEdit = new QLineEdit( fontBox, "fontEdit" );
    fontEdit->setGeometry( QRect( 119, 22, 230, 22 ) );
    fontEdit->setPaletteBackgroundColor( QColor( 194, 194, 194 ) );
    fontEdit->setReadOnly( TRUE );

    extraTabLayout->addWidget( fontBox, 0, 0 );

    miscBox = new QGroupBox( extraTab, "miscBox" );

    askStatusBox = new QCheckBox( miscBox, "askStatusBox" );
    askStatusBox->setGeometry( QRect( 11, 21, 430, 20 ) );

    askStatusLCD = new QLCDNumber( miscBox, "askStatusLCD" );
    askStatusLCD->setGeometry( QRect( 290, 45, 64, 24 ) );

    askStatusLabel = new QLabel( miscBox, "askStatusLabel" );
    askStatusLabel->setGeometry( QRect( 363, 47, 80, 24 ) );

    askStatusSlider = new QSlider( miscBox, "askStatusSlider" );
    askStatusSlider->setGeometry( QRect( 11, 47, 270, 24 ) );
    askStatusSlider->setMinValue( 5 );
    askStatusSlider->setMaxValue( 59 );
    askStatusSlider->setOrientation( QSlider::Horizontal );

    extraTabLayout->addWidget( miscBox, 1, 0 );
    tabWidget->insertTab( extraTab, QString::fromLatin1("") );

    ConfigurationDialogBaseLayout->addMultiCellWidget( tabWidget, 0, 0, 0, 3 );

    okButton = new QPushButton( this, "okButton" );
    okButton->setAutoDefault( TRUE );
    okButton->setDefault( TRUE );

    ConfigurationDialogBaseLayout->addWidget( okButton, 1, 2 );
    Horizontal_Spacing2 = new QSpacerItem( 284, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    ConfigurationDialogBaseLayout->addItem( Horizontal_Spacing2, 1, 1 );

    cancelButton = new QPushButton( this, "cancelButton" );
    cancelButton->setAutoDefault( TRUE );

    ConfigurationDialogBaseLayout->addWidget( cancelButton, 1, 3 );

    helpButton = new QPushButton( this, "helpButton" );
    helpButton->setAutoDefault( TRUE );

    ConfigurationDialogBaseLayout->addWidget( helpButton, 1, 0 );
    languageChange();
    resize( QSize(502, 361).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    // signals and slots connections
    connect( okButton, SIGNAL( clicked() ), this, SLOT( accept() ) );
    connect( cancelButton, SIGNAL( clicked() ), this, SLOT( reject() ) );
    connect( defaultTimeLabel, SIGNAL( destroyed(QObject*) ), this, SLOT( defaultTimeLabel_destroyed(QObject*) ) );
    connect( notifyPortLabel, SIGNAL( destroyed(QObject*) ), this, SLOT( notifyPortLabel_destroyed(QObject*) ) );

    // tab order
    setTabOrder( controlPortEdit, notifyPortEdit );
    setTabOrder( notifyPortEdit, askCloseCheckbox );
    setTabOrder( askCloseCheckbox, logFileEdit );
    setTabOrder( logFileEdit, okButton );
    setTabOrder( okButton, cancelButton );
    setTabOrder( cancelButton, helpButton );
    setTabOrder( helpButton, tabWidget );
}

/*
 *  Destroys the object and frees any allocated resources
 */
ConfigurationDialogBase::~ConfigurationDialogBase()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void ConfigurationDialogBase::languageChange()
{
    setCaption( tr( "Configuration" ) );
    clientGroupBox->setTitle( tr( "Client Settings" ) );
    notifyPortLabel->setText( tr( "Notify Port" ) );
    controlPortLabel->setText( tr( "Control Port" ) );
    QWhatsThis::add( controlPortLabel, tr( "This is the port" ) );
    defaultTimeLabel->setText( tr( "Default Time (min)" ) );
    QWhatsThis::add( defaultTimeLabel, tr( "Default session time" ) );
    askCloseCheckbox->setText( tr( "&Ask Confirmation to Close the Application" ) );
    askCloseCheckbox->setAccel( QKeySequence( tr( "Alt+A" ) ) );
    logGroupBox->setTitle( tr( "Logging Settings" ) );
    logFileButton->setText( tr( "..." ) );
    logFileLabel->setText( tr( "Log File" ) );
    tabWidget->changeTab( mainTab, tr( "Mai&n Configuration" ) );
    fontBox->setTitle( tr( "groupBox3" ) );
    fontButton->setText( tr( "p&ushButton4" ) );
    fontListViewLabel->setText( tr( "textLabel1" ) );
    miscBox->setTitle( tr( "groupBox4" ) );
    askStatusBox->setText( tr( "Periodically &ask status to all workstations" ) );
    askStatusLabel->setText( tr( "seconds" ) );
    tabWidget->changeTab( extraTab, tr( "E&xtra Configuration" ) );
    okButton->setText( tr( "O&K" ) );
    okButton->setAccel( QKeySequence( tr( "Alt+K" ) ) );
    cancelButton->setText( tr( "&Cancel" ) );
    cancelButton->setAccel( QKeySequence( QString::null ) );
    helpButton->setText( tr( "&Help" ) );
    helpButton->setAccel( QKeySequence( tr( "F1" ) ) );
}

