//-----------------------------------------------------------------------------
// File:     QSimMainWindow.cpp
// Class:    QSimMainWindow
// Parent:   QMainWindow
// Purpose:  Main window for Qt application.
/* ------------------------------------------------------------------------- *
* QSim was developed with support from Simbios (the NIH National Center      *
* for Physics-Based Simulation Biological Structures at Stanford) under NIH  *
* Roadmap for Medical Research grant U54 GM072970 and from NCSRR (National   *
* Center for Simulation in Rehabilitation Research) under NIH research       *
* infrastructure grant R24 HD065690.                                         *
*                                                                            *
* Portions copyright (c) 2011 the Authors and/or and Stanford University.    *
* Authors: Paul Mitiguy                                                      *
* Contributors: Ayman Habib, Michael Sherman                                 *
*                                                                            *
* Permission is hereby granted, free of charge, to any person obtaining a    *
* copy of this software and associated documentation files (the "Software"), *
* to deal in the Software without restriction, including without limitation  *
* the rights to use, copy, modify, merge, publish, distribute, sublicense,   *
* and/or sell copies of the Software, and to permit persons to whom the      *
* Software is furnished to do so, subject to the following conditions:       *
*                                                                            *
* This sentence, the above copyright and permission notices, and the         *
* following disclaimer shall be included in all copies or substantial        *
* portions of the Software.                                                  *
*                                                                            *
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR *
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,   *
* FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL   *
* THE AUTHORS, CONTRIBUTORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,    *
* DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR      *
* OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE  *
* USE OR OTHER DEALINGS IN THE SOFTWARE.                                     *
* -------------------------------------------------------------------------- */
#include "QSimMainWindow.h"
#include "QSimGenericFunctions.h"


//------------------------------------------------------------------------------
namespace QSim {


//-----------------------------------------------------------------------------
QSimMainWindow::QSimMainWindow() : myExitProgramAction(NULL), myNewFileAction(NULL), myOpenFileAction(NULL), mySaveFileAction(NULL), mySaveFileAsAction(NULL), myPrintFileAction(NULL), myEditCutAction(NULL), myEditCopyAction(NULL), myEditPasteAction(NULL), myEditDeleteAction(NULL), myHelpAboutAction(NULL), myHelpContentsAction(NULL), mySimulateStartAction(NULL)
{
   // Complete the class construction.
   this->setCentralWidget( &myQSimMainWindowTextEdit );
   this->CreateFileMenu();
   this->CreateEditMenu();
   this->CreateHelpMenu();
   this->CreateSimulateMenu();

   // The application icon is typically displayed in the top-left corner of an application's top-level windows.
   // To change the icon of the executable file as presented on the desktop (i.e., prior to application execution),
   // it is necessary to employ a platform-dependent technique.
   // See:  http://doc.qt.nokia.com/latest/appicon.html
   const QIcon mainApplicationWindowIcon( ":/QSimApplicationIconC.ico" );
   this->setWindowIcon( mainApplicationWindowIcon );

   // Note: It may not be possible to bold-face the title of the main application window as it is controlled by OS, not Qt.
   //this->setWindowTitle( "QSim" );

   // Size this window (make it larger than usual) and show it.
   // this->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding );
   this->resize( 700, 500 );
   this->show();

   // Display a splash screen.
   this->DisplaySplashScreen();
}


//------------------------------------------------------------------------------
void  QSimMainWindow::AddActionToMainWindowMenu( QAction& action, QMenu& mainWindowMenu, const QString& textName, const char *pathToIconFile )
{
   action.setParent( this );
   action.setText( textName );
   if( pathToIconFile && *pathToIconFile )
   {
       const QIcon *actionIcon = new QIcon( pathToIconFile );
	   if( actionIcon && !actionIcon->isNull() )  action.setIcon( *actionIcon );
   }
   mainWindowMenu.addAction( &action );
}


//-----------------------------------------------------------------------------
void QSimMainWindow::CreateFileMenu()
{
   // Create actions (user-interface objects inserted into widgets) that allow a program to standardize
   // performance and keeps in sync identical commands invocable via menus, toolbar buttons, and/or keyboard shortcuts.
   //---------------------------------------
   QMenuBar* mainWindowMenuBar = this->menuBar();                // Creates/Gets/Owns QMainWindow menuBar.
   QMenu* fileMenu = mainWindowMenuBar->addMenu( tr("&File") );  // Creates/Gets/Owns this menu.

   this->AddActionToMainWindowMenu( myNewFileAction, *fileMenu, tr("&New file"),  QKeySequence::New,  ":/TangoPublicDomainImages/document-new.png" );
   QObject::connect( &myNewFileAction, SIGNAL(triggered()), this, SLOT(NewFileSlot()) );

   this->AddActionToMainWindowMenu( myOpenFileAction, *fileMenu, tr("&Open file"), QKeySequence::Open, ":/TangoPublicDomainImages/document-open.png" );
   QObject::connect( &myOpenFileAction, SIGNAL(triggered()), this, SLOT(OpenFileSlot()) );

   this->AddActionToMainWindowMenu( mySaveFileAction, *fileMenu, tr("&Save file"), QKeySequence::Save, ":/TangoPublicDomainImages/document-save.png" );
   QObject::connect( &mySaveFileAction, SIGNAL(triggered()), this, SLOT(SaveFileSlot()) );

   this->AddActionToMainWindowMenu( mySaveFileAsAction, *fileMenu, tr("Save file as"), QKeySequence::SaveAs, ":/TangoPublicDomainImages/document-save-as.png" );
   QObject::connect( &mySaveFileAsAction, SIGNAL(triggered()), this, SLOT(SaveFileAsSlot()) );

   this->AddActionToMainWindowMenu( myPrintFileAction, *fileMenu, tr("&Print file"), QKeySequence::Print, ":/TangoPublicDomainImages/printer.png" );
   QObject::connect( &myPrintFileAction, SIGNAL(triggered()), this, SLOT(PrintFileSlot()) );

   fileMenu->addSeparator();
   this->AddActionToMainWindowMenu( myExitProgramAction, *fileMenu, tr("&Quit/Exit program"), QKeySequence::Quit, ":/TangoPublicDomainImages/system-shutdown.png" );
   QObject::connect( &myExitProgramAction, SIGNAL(triggered()), this, SLOT(ExitProgramSlot()) );
}



//-----------------------------------------------------------------------------
void QSimMainWindow::CreateEditMenu()
{
   // Create actions (user-interface objects inserted into widgets) that allow a program to standardize
   // performance and keeps in sync identical commands invocable via menus, toolbar buttons, and/or keyboard shortcuts.
   //---------------------------------------
   QMenuBar* mainWindowMenuBar = this->menuBar();                // Creates/Gets/Owns QMainWindow menuBar.
   QMenu* editMenu = mainWindowMenuBar->addMenu( tr("&Edit") );  // Creates/Gets/Owns this menu.

   this->AddActionToMainWindowMenu( myEditCutAction, *editMenu, tr("Cu&t"),   QKeySequence::Cut,   ":/TangoPublicDomainImages/edit-cut.png" );
   QObject::connect( &myEditCutAction,   SIGNAL(triggered()), this, SLOT(EditCutSlot()) );

   this->AddActionToMainWindowMenu( myEditCopyAction, *editMenu, tr("&Copy"),  QKeySequence::Copy,  ":/TangoPublicDomainImages/edit-copy.png" );
   QObject::connect( &myEditCopyAction,  SIGNAL(triggered()), this, SLOT(EditCopySlot()) );

   this->AddActionToMainWindowMenu( myEditPasteAction, *editMenu, tr("&Paste"), QKeySequence::Paste, ":/TangoPublicDomainImages/edit-paste.png" );
   QObject::connect( &myEditPasteAction, SIGNAL(triggered()), this, SLOT(EditPasteSlot()) );

   this->AddActionToMainWindowMenu( myEditDeleteAction, *editMenu, tr("&Delete"), QKeySequence::Delete, ":/TangoPublicDomainImages/edit-delete.png" );
   QObject::connect( &myEditDeleteAction, SIGNAL(triggered()), this, SLOT(EditDeleteSlot()) );
}


//-----------------------------------------------------------------------------
void QSimMainWindow::CreateHelpMenu()
{
   // Create actions (user-interface objects inserted into widgets) that allow a program to standardize
   // performance and keeps in sync identical commands invocable via menus, toolbar buttons, and/or keyboard shortcuts.
   //---------------------------------------
   QMenuBar* mainWindowMenuBar = this->menuBar();                // Creates/Gets/Owns QMainWindow menuBar.
   QMenu* helpMenu = mainWindowMenuBar->addMenu( tr("&Help") );  // Creates/Gets/Owns this menu.

   this->AddActionToMainWindowMenu( myHelpAboutAction, *helpMenu, tr("&About"), ":/ApachePublicDomainImages/world1.png" );
   //this->AddActionToMainWindowMenu( myHelpAboutAction, *helpMenu, tr("&About"), ":../QSimApplicationIconC.ico" );
   QObject::connect( &myHelpAboutAction,   SIGNAL(triggered()), this, SLOT(HelpAboutSlot()) );

   this->AddActionToMainWindowMenu( myHelpContentsAction, *helpMenu, tr("&Help"),  QKeySequence::HelpContents,  ":/TangoPublicDomainImages/help-browser.png" );
   QObject::connect( &myHelpContentsAction,   SIGNAL(triggered()), this, SLOT(HelpContentsSlot()) );
}


//-----------------------------------------------------------------------------
void QSimMainWindow::CreateSimulateMenu()
{
   QMenuBar* mainWindowMenuBar = this->menuBar();                        // Creates/Gets/Owns QMainWindow menuBar.
   QMenu* simulateMenu = mainWindowMenuBar->addMenu( tr("&Simulate") );  // Creates/Gets/Owns this menu.

   this->AddActionToMainWindowMenu( mySimulateStartAction, *simulateMenu, tr("&Start"), ":/TangoPublicDomainImages/SimulateStartIcon.png" );
   QObject::connect( &mySimulateStartAction,  SIGNAL(triggered()), this, SLOT( SlotStartSimulationFromMainApplicationWindow()) );
}



//-----------------------------------------------------------------------------
void QSimMainWindow::CreateCrazyWidget()
{
   // Create widgets, i.e., "windows gadget" (visual element in user interface).
   // Widgets include labels, buttons, menus, scroll bars, and frames.
   // Widgets can contain other widgets.
   // Widgets are always created hidden to customize before showing (avoiding flicker).
   QWidget *mainWindowParentNull = NULL;
   Qt::WindowFlags  mainWindowFlags = Qt::Dialog;
   // QMainWindow mainWindowInApplication( mainWindowParentNull, mainWindowFlags );
   QWidget mainWindowInApplication( mainWindowParentNull, mainWindowFlags );
   mainWindowInApplication.setWindowTitle( "QSim" );
   mainWindowInApplication.setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding );
   // mainWindowInApplication.resize( 400, 200 );

   // Create layout manager for main window, which may be of type:
   // QGridLayout (grid)  or  QHBoxLayout (horizontal)  or  QVBoxLayout (vertical).
   // The constructor calls  mainWindowInApplication.setLayout( &mainWindowLayoutManager );
   QVBoxLayout mainWindowLayoutManager( &mainWindowInApplication );

   // Labels are widgets that contain text and that can be formatted with simple HTML-style formatting.
   QLabel widgetLabel( "<h1><b><i>Hello</i></b> &nbsp;&nbsp; <font color=blue>world!</font></h1> <h2><b><font color=blue><br>Scott, Sherm, Ayman, Peter, Matt, Chand, Mark, <br>Ajay, Sam, Edith, Jennifer, Joy, Jessie, Paul, Melanie, ...</font color><b><br></h2>", &mainWindowInApplication );
   widgetLabel.setAlignment( Qt::AlignHCenter );
   mainWindowLayoutManager.addWidget( &widgetLabel );

   // Qt provides four kinds of buttons: QPushButton, QCheckBox, QRadioButton, and QToolButton.
   // Widgets emit signals to indicate use action or a change of state.
   // For example QPushButton emits a clicked() signal when user clicks the button.
   // A signal can be connected to a function (called a "slot")
   QPushButton widgetPushButtonToQuit( "Push button to quit", &mainWindowInApplication );
   widgetPushButtonToQuit.resize( 600, 180 );
   QObject::connect( &widgetPushButtonToQuit, SIGNAL( clicked() ), this, SLOT( ExitProgramSlot() ) );
   mainWindowLayoutManager.addWidget( &widgetPushButtonToQuit );

   // Start a simulation when button is pushed by connecting to a "slot".
   QPushButton widgetPushButtonToSimulate( "Push button to simulate", &mainWindowInApplication );
   widgetPushButtonToSimulate.resize( 600, 180 );
   QObject::connect( &widgetPushButtonToSimulate, SIGNAL( clicked() ), this, SLOT( SlotStartSimulationFromMainApplicationWindow() ) );
   mainWindowLayoutManager.addWidget( &widgetPushButtonToSimulate );

   // QCheckBox allows for exclusive or non-exclusive selections.
   QCheckBox simpleCheckBox1( "This is check box 1", &mainWindowInApplication );
   QCheckBox simpleCheckBox2( "This is check box 2", &mainWindowInApplication );
   QCheckBox simpleCheckBox3( "This is check box 3", &mainWindowInApplication );
   mainWindowLayoutManager.addWidget( &simpleCheckBox1 );
   mainWindowLayoutManager.addWidget( &simpleCheckBox2 );
   mainWindowLayoutManager.addWidget( &simpleCheckBox3 );

   // Radio buttons (do not have to be contained within QGroupBox)
   QRadioButton simpleRadioButton1( "Random radio button 1", &mainWindowInApplication );
   QRadioButton simpleRadioButton2( "Random radio button 2", &mainWindowInApplication );
   mainWindowLayoutManager.addWidget( &simpleRadioButton1 );
   mainWindowLayoutManager.addWidget( &simpleRadioButton2 );
   simpleRadioButton2.setChecked( true );

   // Radio buttons (can be contained within QGroupBox).
   // QGroupBox widget provides a group box with optional title on top and displays widgets within itself.
   // The optional Shortcut activated by the user pressing ALT-& where & is the letter E following the & in the title.
   // The Shortcut moves focus to one of the children widgets inside QGroupBox.
   QGroupBox groupBoxOfRadioButtons( "&Exclusive Radio Buttons" );
   groupBoxOfRadioButtons.setAlignment( Qt::AlignLeft ); // aligns the title text with the left-hand side of the group box
   groupBoxOfRadioButtons.setCheckable( true );          // Grays out entire group via check-box to user.
   groupBoxOfRadioButtons.setFlat( false );              // Default is false, and puts a frame around group.
   mainWindowLayoutManager.addWidget( &groupBoxOfRadioButtons );
   QVBoxLayout vboxLayoutManagerForRadioButtons;
   groupBoxOfRadioButtons.setLayout( &vboxLayoutManagerForRadioButtons );

   QRadioButton radio1( "&Radio button 1" );
   QRadioButton radio2( "R&adio button 2" );
   QRadioButton radio3( "Ra&dio button 3" );
   radio1.setChecked(true);

   // Add a check box and push button to this groupBoxOfRadioButtons.
   QCheckBox independentCheckBox( "Independent check box" );
   QPushButton independentPopUpMenuButton( "Independent push button to display menus" );

   vboxLayoutManagerForRadioButtons.addWidget( &radio1 );
   vboxLayoutManagerForRadioButtons.addWidget( &radio2 );
   vboxLayoutManagerForRadioButtons.addWidget( &radio3 );
   vboxLayoutManagerForRadioButtons.addWidget( &independentCheckBox );
   vboxLayoutManagerForRadioButtons.addWidget( &independentPopUpMenuButton );
   // vboxLayoutManagerForRadioButtons.addStretch( 1 );

   // Make it so pushing independentPopUpMenuButton causes menu to appear.
   QMenu menu( &mainWindowInApplication );
   // menu.setTitle(  "Menu title" );                    // May only makes sense in certain circumstances.
   menu.addAction( "First  Menu Item" );
   menu.addAction( "Second Menu Item" );
   menu.addSeparator();
   menu.addAction( "Third  Menu Item" );
   menu.addAction( "Fourth Menu Item" );
   independentPopUpMenuButton.setMenu( &menu );

#if 0
   // QPushButton can display an icon.
   QIcon prettyIcon( "C://test//box1.ico" );
   QPushButton widgetPrettyPushButton( prettyIcon, "Hi there", &mainWindowInApplication );
   // widgetPrettyPushButton.resize( 600, 180 );
   mainWindowLayoutManager.addWidget( &widgetPrettyPushButton );
#endif

#if 0
   // QToolButton is usually used inside a QToolBar.
   QToolButton  simpleToolButton( &mainWindowInApplication );
   QToolBar     exampleToolBar( "Title of toolbar", &mainWindowInApplication );
   exampleToolBar.addWidget( &simpleToolButton );
   mainWindowLayoutManager.addWidget( &exampleToolBar );
#endif

   // Progress bar
   QProgressBar progressBar( &mainWindowInApplication );
   progressBar.setOrientation( Qt::Horizontal );
   progressBar.setAlignment( Qt::AlignHCenter );
   progressBar.setRange( 200, 400 );
   progressBar.setValue( 250 );
   progressBar.setTextVisible( true );
   mainWindowLayoutManager.addWidget( &progressBar );

   // Create spinbox with designated range, increment, etc.
   QSpinBox widgetSpinBox( &mainWindowInApplication );
   widgetSpinBox.setRange( 0, 20 );
   widgetSpinBox.setSingleStep( 2 );
   mainWindowLayoutManager.addWidget( &widgetSpinBox );

   // Create integer slider with designated range, tick interval, tick position, initial value, etc.
   QSlider  widgetSlider(Qt::Horizontal, &mainWindowInApplication );
   widgetSlider.setRange( 0, 20 );
   widgetSlider.setSingleStep( 2 );      // When user presses Left or Right arrow
   widgetSlider.setPageStep( 10 );       // When user presses Page Up or Page Down.
   widgetSlider.setTickInterval( 2 );
   widgetSlider.setTickPosition( QSlider::TicksBelow );
   mainWindowLayoutManager.addWidget( &widgetSlider );

   // Widgets can emit signals that are caught by other widgets and vice-versa.
   QObject::connect( &widgetSpinBox, SIGNAL( valueChanged(int) ), &widgetSlider,  SLOT( setValue(int) ) );
   QObject::connect( &widgetSlider,  SIGNAL( valueChanged(int) ), &widgetSpinBox, SLOT( setValue(int) ) );
   widgetSlider.setValue( 4  );

   // Show the main window and all its children.
   // mainWindowInApplication.setCentralWidget( &widgetPushButtonToSimulate );
   mainWindowInApplication.show();
   mainWindowInApplication.repaint();
   SleepInMilliseconds( 2000 );
}



//-----------------------------------------------------------------------------
void QSimMainWindow::DisplaySplashScreen()
{
   QWidget splashScreenDialog( this, Qt::Dialog );
   splashScreenDialog.setWindowTitle( "QSim" );
   splashScreenDialog.setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding );

   // Create layout manager for splash screen.
   QVBoxLayout splashScreenLayoutManager( &splashScreenDialog );

#if 0
   // Labels are widgets that contain text and that can be formatted with simple HTML-style formatting.
   QLabel movieLabel( &splashScreenDialog);
   QMovie animatedGif( ":/MiscImages/RedCircleOnYellowSquarePublicDomain.gif" );
   movieLabel.setMovie( &animatedGif );
   movieLabel.setAlignment( Qt::AlignHCenter );
   splashScreenLayoutManager.addWidget( &movieLabel );
#endif

   // Labels are widgets that contain text and that can be formatted with simple HTML-style formatting.
   QLabel widgetLabel( "<h2><b><font color=blue><br>Hello Scott, Sherm, Ayman, Peter, Matt, Chand, Mark, <br>Ajay, Sam, Edith, Jennifer, Joy, Jessie, Paul, Melanie, ...</font color><b><br></h2>", &splashScreenDialog );
   widgetLabel.setAlignment( Qt::AlignHCenter );
   splashScreenLayoutManager.addWidget( &widgetLabel );

   // Labels can contain pictures of various formats (e.g., BMP, GIF, JPG, PNG, PBM)
   QLabel logoLabel( &splashScreenDialog );
   QPixmap jpgLogoAsPixmap( ":/MiscImages/QSimLogo.jpg", "JPG" );
   logoLabel.setPixmap( jpgLogoAsPixmap );
   logoLabel.setAlignment( Qt::AlignHCenter );
   splashScreenLayoutManager.addWidget( &logoLabel );

   // Show the dialog box for a few seconds.
   // splashScreenDialog.setWindowModality( Qt::WindowModal );
   splashScreenDialog.show();
   splashScreenDialog.repaint();
   SleepInMilliseconds( 3000 );
}



//-----------------------------------------------------------------------------
void  QSimMainWindow::OpenFileSlot()
{
   QFileDialog fileOpenDialog( this, Qt::Dialog );
   fileOpenDialog.setFileMode( QFileDialog::ExistingFiles );    // Use Directory if only a directory may be selected.  Use AnyFile if can specify a file that does not exist (useful for Save As file dialog).
   fileOpenDialog.setViewMode( QFileDialog::Detail );           // Use QFileDialog::List for no detail.

   // Note: Separate multiple filters with two semicolons, e.g.:  "Images (*.png *.jpg);;Text files (*.txt);;XML files (*.xml)"
   fileOpenDialog.setNameFilter( tr("Image Files (*.png *.jpg *.bmp)") );

   if( myPreviousFileDialogWorkingDirectory.exists()  )
      fileOpenDialog.setDirectory( myPreviousFileDialogWorkingDirectory );

   if( fileOpenDialog.exec() )
   {
      QStringList fileNames = fileOpenDialog.selectedFiles();
	    if( fileNames.count() == 1 )
         myPreviousFileDialogWorkingDirectory = fileOpenDialog.directory();
   }
}


//-----------------------------------------------------------------------------
void  QSimMainWindow::SaveFileSlot()
{
   QFileDialog fileSaveDialog( this, Qt::Dialog );
   fileSaveDialog.setFileMode( QFileDialog::ExistingFiles );  // Use Directory if only a directory may be selected.  Use AnyFile if can specify a file that does not exist (useful for Save As file dialog).
   fileSaveDialog.setViewMode( QFileDialog::Detail );         // Use QFileDialog::List for no detail.

   // Note: Separate multiple filters with two semicolons, e.g.:  "Images (*.png *.jpg);;Text files (*.txt);;XML files (*.xml)"
   fileSaveDialog.setNameFilter( tr("Image Files (*.png *.jpg *.bmp)") );

   if( myPreviousFileDialogWorkingDirectory.exists()  )
      fileSaveDialog.setDirectory( myPreviousFileDialogWorkingDirectory );

   if( fileSaveDialog.exec() )
   {
      QStringList fileNames = fileSaveDialog.selectedFiles();
	    if( fileNames.count() == 1 )
         myPreviousFileDialogWorkingDirectory = fileSaveDialog.directory();
   }
}



#if 0
// #include <QAudio>
//-----------------------------------------------------------------------------
void  QSimMainWindow::PlayMusicFile()
{
   // A Google search for public domain music returned the follow list:
   // http://www.google.com/Top/Arts/Music/Sound_Files/Classical/MP3/
   // The William Tell Overture was download from here:
   // http://www.archive.org/details/WilliamTellOverture_414
   QMediaPlayer musicPlayer;
   musicPlayer.setMedia( QUrl::fromLocalFile("/Users/Paul/PublicDomainAudioVideo/william_tell_overture_2.mp3") );
   musicPlayer.setVolume( 50 );
   musicPlayer.play();
}
#endif


#if 0
//-----------------------------------------------------------------------------
// #include <QtMultimedia>
void  QSimMainWindow::PlayVideoFile()
{
   // Archive of public domain movies: http://www.archive.org/details/movies
   // List of public domain movies: http://www.freemediaguide.com/free_public_domain_videos.html
   // This public domain movie was downloaded from NASA Langely http://lisar.larc.nasa.gov/UTILS/info.cgi?id=LV-2000-00015
   QMediaPlayer videoPlayer;
   videoPlayer.setMedia( QUrl::fromLocalFile("/Users/Paul/PublicDomainAudioVideo/NasaLangelyHypersonicAircraftSimulation.mov") );

   QVideoWidget videoWidget( player );
   videoWidget.show();

   videoPlayer.play();
}
#endif


//------------------------------------------------------------------------------
}  // End of namespace QSim


