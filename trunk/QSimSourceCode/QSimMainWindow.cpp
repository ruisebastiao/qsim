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
QSimMainWindow::QSimMainWindow()
{
   // It is possible to override the weird default behavior of separating the title/tool bar from the rest of the application on Macintosh computers.
   this->setUnifiedTitleAndToolBarOnMac( false );

   // The application icon is typically displayed in the top-left corner of an application's top-level windows.
   // To change the icon of the executable file as presented on the desktop (i.e., prior to application execution),
   // it is necessary to employ a platform-dependent technique.
   // See:  http://doc.qt.nokia.com/latest/appicon.html
   const QIcon mainApplicationWindowIcon( ":/QSimApplicationIconC.ico" );
   this->setWindowIcon( mainApplicationWindowIcon );

   // Note: It may not be possible to bold-face the title of the main application window as it is controlled by OS, not Qt.
   this->setWindowTitle( "QSim:  Easy-to-use Biomechanics Software" );

   // Specify the central widget (required).
   this->setCentralWidget( &myQSimGLViewWidget );
   myQSimGLViewWidget.SetQSimMainWindowThatHoldsQSimGLViewWidget( this );

   // Create the actions then add them to various menus and toolbars.
   this->AddAllActionsWhoAreChildrenOfQSimMainWindow();
   this->CreateMainWindowFileMenu();
   this->CreateMainWindowEditMenu();
   this->CreateMainWindowSimulateMenu();
   this->CreateMainWindowHelpMenu();
   this->CreateMainWindowToolbarEditEtc();    // Edit tool bar near the top and below menus.
   myToolBarGeometry.AddToolbarGeometryToMainWindow( *this );
   this->CreateMainWindowStatusBar();         
   this->CreateMainWindowDockWidgets();       // Create widgets that surround the central widget.

   // Size this window in pixels (possibly making it larger than usual or maximized) and show it.
   this->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding );
   this->resize( this->sizeHint() );
   const int screenWidth  = QApplication::desktop()->width();
   const int screenHeight = QApplication::desktop()->height();
   const int minimumWidgetWidth  = (int)( 0.85*(float)screenWidth  );  // Old minimumWidgetWidth  = 700;
   const int minimumWidgetHeight = (int)( 0.85*(float)screenHeight );  // Old minimumWidgetHeight = 500;
   const int naturalWidgetWidth  = this->width();
   const int naturalWidgetHeight = this->height();
   const int actualWidgetWidth   = naturalWidgetWidth  >= minimumWidgetWidth  ? naturalWidgetWidth  : minimumWidgetWidth;
   const int actualWidgetHeight  = naturalWidgetHeight >= minimumWidgetHeight ? naturalWidgetHeight : minimumWidgetHeight;
   if( actualWidgetWidth >= screenWidth || actualWidgetHeight >= screenHeight ) this->showMaximized();
   else { this->resize( actualWidgetWidth, actualWidgetHeight );  this->show(); }

   // Display a splash screen when application launches.
   this->DisplaySplashScreen();
}


//------------------------------------------------------------------------------
void  QSimMainWindow::AddAllActionsWhoAreChildrenOfQSimMainWindow()
{
   // Create actions associated with file menu.
   myNewFileAction.AddActionHelper(     tr("&New file"),          QKeySequence::New,           ":/TangoPublicDomainImages/document-new.png" );
   QObject::connect( &myNewFileAction,                     SIGNAL(triggered()), this, SLOT(NewFileSlot()) );

   myOpenFileAction.AddActionHelper(    tr("&Open file"),         QKeySequence::Open,          ":/TangoPublicDomainImages/document-open.png" );
   QObject::connect( &myOpenFileAction,                    SIGNAL(triggered()), this, SLOT(OpenFileSlot()) );

   mySaveFileAction.AddActionHelper(    tr("&Save file"),         QKeySequence::Save,          ":/TangoPublicDomainImages/document-save.png" );
   QObject::connect( &mySaveFileAction,                    SIGNAL(triggered()), this, SLOT(SaveFileSlot()) );

   mySaveFileAsAction.AddActionHelper(  tr("Save file as"),       QKeySequence::SaveAs,        ":/TangoPublicDomainImages/document-save-as.png" );
   QObject::connect( &mySaveFileAsAction,                  SIGNAL(triggered()), this, SLOT(SaveFileAsSlot()) );

   myPrintFileAction.AddActionHelper(   tr("&Print file"),        QKeySequence::Print,         ":/TangoPublicDomainImages/printer.png" );
   QObject::connect( &myPrintFileAction,                   SIGNAL(triggered()), this, SLOT(PrintFileSlot()) );

   myExitProgramAction.AddActionHelper( tr("&Quit/Exit program"), QKeySequence::Quit,          ":/TangoPublicDomainImages/system-shutdown.png" );
   QObject::connect( &myExitProgramAction,                 SIGNAL(triggered()), this, SLOT(ExitProgramSlot()) );


   // Create actions associated with edit menu.
   myEditCutAction.AddActionHelper(    tr("Cu&t"),               QKeySequence::Cut,           ":/TangoPublicDomainImages/edit-cut.png" );
   QObject::connect( &myEditCutAction,                     SIGNAL(triggered()), this, SLOT(EditCutSlot()) );

   myEditCopyAction.AddActionHelper(   tr("&Copy"),              QKeySequence::Copy,          ":/TangoPublicDomainImages/edit-copy.png" );
   QObject::connect( &myEditCopyAction,                    SIGNAL(triggered()), this, SLOT(EditCopySlot()) );

   myEditPasteAction.AddActionHelper(  tr("&Paste"),             QKeySequence::Paste,         ":/TangoPublicDomainImages/edit-paste.png" );
   QObject::connect( &myEditPasteAction,                   SIGNAL(triggered()), this, SLOT(EditPasteSlot()) );

   myEditDeleteAction.AddActionHelper( tr("&Delete"),            QKeySequence::Delete,        ":/TangoPublicDomainImages/edit-delete.png" );
   QObject::connect( &myEditDeleteAction,                  SIGNAL(triggered()), this, SLOT(EditDeleteSlot()) );


   // Create actions associated with simulate menu.
   mySimulateStartAction.AddActionHelper( tr("&Start"),                                          ":/TangoPublicDomainImages/media-playback-start.png" );
   QObject::connect( &mySimulateStartAction,               SIGNAL(triggered()), this, SLOT( SlotStartSimulationFromMainApplicationWindow()) );


   // Create actions associated with help menu.
   myHelpAboutAction.AddActionHelper(     tr("&About"),                                          ":/QSimApplicationIconC.ico" ); //or maybe ":../QSimApplicationIconC.ico" or ":/ApachePublicDomainImages/world1.png"
   QObject::connect( &myHelpAboutAction,                   SIGNAL(triggered()), this, SLOT(HelpAboutSlot()) );

   myHelpContentsAction.AddActionHelper(  tr("&Help"),              QKeySequence::HelpContents,  ":/TangoPublicDomainImages/help-browser.png" );
   QObject::connect( &myHelpContentsAction,                SIGNAL(triggered()), this, SLOT(HelpContentsSlot()) );

#if 0
   // Create actions associated with drawing geometry.
   myDrawSphereAction.AddActionHelper(   tr("&Sphere"),                                         ":/MiscImages/BlueSolidsPublicDomainSphereTransparent120Pixel.png" );
   QObject::connect( &myDrawSphereAction,                  SIGNAL(triggered()), this, SLOT(DrawSphereSlot()) );

   myDrawCubeAction.AddActionHelper(     tr("&Cube"),                                           ":/MiscImages/BlueSolidsPublicDomainCubeTransparent120Pixel.png" );
   QObject::connect( &myDrawCubeAction,                    SIGNAL(triggered()), this, SLOT(DrawCubeSlot()) );

   myDrawCylinderAction.AddActionHelper( tr("C&ylinder"),                                       ":/MiscImages/BlueSolidsPublicDomainCylinderTransparent120Pixel.png" );
   QObject::connect( &myDrawCylinderAction,                SIGNAL(triggered()), this, SLOT(DrawCylinderSlot()) );

   myDrawConeCapAction.AddActionHelper(  tr("C&oneCap"),                                        ":/MiscImages/BlueSolidsPublicDomainConeCapTransparent120Pixel.png" );
   QObject::connect( &myDrawConeCapAction,                 SIGNAL(triggered()), this, SLOT(DrawConeCapSlot()) );

   myDrawConeFullAction.AddActionHelper( tr("Co&neFull"),                                       ":/MiscImages/BlueSolidsPublicDomainConeFullTransparent120Pixel.png" );
   QObject::connect( &myDrawConeFullAction,                SIGNAL(triggered()), this, SLOT(DrawConeFullSlot()) );

   myDrawTorusAction.AddActionHelper(    tr("&Torus"),                                          ":/MiscImages/BlueSolidsPublicDomainTorusTransparent120Pixel.png" );
   QObject::connect( &myDrawTorusAction,                   SIGNAL(triggered()), this, SLOT(DrawTorusSlot()) );

   myDrawTorsoAndLowerExtremityAction.AddActionHelper( tr("Torso &and lower extremity"),                      ":/MiscImages/OpenSimTorsoAndLowerExtremityModel.png" );
   QObject::connect( &myDrawTorsoAndLowerExtremityAction,  SIGNAL(triggered()), this, SLOT(DrawTorsoAndLowerExtremityModelSlot()) );

   myDrawLowerExtremityOnlyAction.AddActionHelper(     tr("&Lower extremity"),                                ":/MiscImages/OpenSimLowerExtremityOnlyModel.png" );
   QObject::connect( &myDrawLowerExtremityOnlyAction,      SIGNAL(triggered()), this, SLOT(DrawLowerExtremityOnlyModelSlot()) );

   myDrawLowerLimbAction.AddActionHelper(              tr("Lo&wer limb"),                                     ":/MiscImages/OpenSimLowerLimbModelEdithArnold.png" );
   QObject::connect( &myDrawLowerLimbAction,               SIGNAL(triggered()), this, SLOT(DrawLowerLimbModelSlot()) );
#endif
}


//-----------------------------------------------------------------------------
void QSimMainWindow::CreateMainWindowFileMenu()
{
   // Create actions (user-interface objects inserted into widgets) that allow a program to standardize
   // performance and keeps in sync identical commands invoked via menus, toolbar buttons, and/or keyboard shortcuts.
   //---------------------------------------
   QMenuBar* mainWindowMenuBar = this->menuBar();                // Creates/Gets/Owns QMainWindow menuBar.
   QMenu* fileMenu = mainWindowMenuBar->addMenu( tr("&File") );  // Creates/Gets/Owns this menu.
   fileMenu->addAction( &myNewFileAction     );
   fileMenu->addAction( &myOpenFileAction    );
   fileMenu->addAction( &mySaveFileAction    );
   fileMenu->addAction( &mySaveFileAsAction  );
   fileMenu->addAction( &myPrintFileAction   );
   fileMenu->addSeparator();
   fileMenu->addAction( &myExitProgramAction );
}


//-----------------------------------------------------------------------------
void QSimMainWindow::CreateMainWindowEditMenu()
{
   // Create actions (user-interface objects inserted into widgets) that allow a program to standardize
   // performance and keeps in sync identical commands invoked via menus, toolbar buttons, and/or keyboard shortcuts.
   //---------------------------------------
   QMenuBar* mainWindowMenuBar = this->menuBar();                // Creates/Gets/Owns QMainWindow menuBar.
   QMenu* editMenu = mainWindowMenuBar->addMenu( tr("&Edit") );  // Creates/Gets/Owns this menu.
   editMenu->addAction( &myEditCutAction    );
   editMenu->addAction( &myEditCopyAction   );
   editMenu->addAction( &myEditPasteAction  );
   editMenu->addAction( &myEditDeleteAction );
}


//-----------------------------------------------------------------------------
void QSimMainWindow::CreateMainWindowHelpMenu()
{
   // Create actions (user-interface objects inserted into widgets) that allow a program to standardize
   // performance and keeps in sync identical commands invoked via menus, toolbar buttons, and/or keyboard shortcuts.
   //---------------------------------------
   QMenuBar* mainWindowMenuBar = this->menuBar();                // Creates/Gets/Owns QMainWindow menuBar.
   QMenu* helpMenu = mainWindowMenuBar->addMenu( tr("&Help") );  // Creates/Gets/Owns this menu.
   helpMenu->addAction( &myHelpAboutAction    );
   helpMenu->addAction( &myHelpContentsAction );
}


//-----------------------------------------------------------------------------
void QSimMainWindow::CreateMainWindowSimulateMenu()
{
   QMenuBar* mainWindowMenuBar = this->menuBar();                        // Creates/Gets/Owns QMainWindow menuBar.
   QMenu* simulateMenu = mainWindowMenuBar->addMenu( tr("&Simulate") );  // Creates/Gets/Owns this menu.
   simulateMenu->addAction( &mySimulateStartAction );
}


//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
void  QSimMainWindow::CreateMainWindowToolbarEditEtc()
{
   // Toolbars on main window (resource is allocated and probably deleted by QSimMainWindow).
   // setAllowedAreas are Qt::TopToolBarArea, BottomToolBarArea, Qt::LeftToolBarArea, Qt::RightToolBarArea.
   // The first line below always creates a toolbar at the Qt::TopToolBarArea (whether or not you want it there).
   // To move it elsewhere, you then must use:  this->addToolBar( Qt::SomeOtherToolBarArea, toolBar );
   QToolBar *toolBar = this->addToolBar( tr("Edit toolbar") );
   toolBar->setAllowedAreas( Qt::TopToolBarArea );
   toolBar->setMovable( false );
   toolBar->setFloatable( false );
   toolBar->addAction( &myEditCutAction     );
   toolBar->addAction( &myEditCopyAction    );
   toolBar->addAction( &myEditPasteAction   );
   toolBar->addAction( &myEditDeleteAction  );

   // If desirable, create another toolbar to the right of the previous one (on the same horizontal line).
   // Or if desirable, add a "line-break" to create a second horizontal row of toolbars/icons.
   // this->addToolBarBreak();
}


//------------------------------------------------------------------------------
void  QSimMainWindow::CreateTextEditor()
{
   // Set up the message window.
   myQSimMainWindowTextEdit.clear();

   // Add text to message window.
   QTextCursor cursor( myQSimMainWindowTextEdit.textCursor() );
   cursor.movePosition( QTextCursor::Start );
   for( int i=0;  i < 2;  i++ ) cursor.insertBlock(); // Blank lines.
   cursor.insertText("QSim:  Accessible, Extensible, Biomechanics Software" );
   
   // Size this window in pixels.
   myQSimMainWindowTextEdit.setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding );
   myQSimMainWindowTextEdit.resize( myQSimMainWindowTextEdit.sizeHint() );
   const int minimumWidgetHeight = (int)( 0.05*(float)myQSimGLViewWidget.height() ); // Fraction of the OpenGL Window height
   const int naturalWidgetHeight = myQSimMainWindowTextEdit.height();
   const int actualWidgetHeight  = naturalWidgetHeight >= minimumWidgetHeight ? naturalWidgetHeight : minimumWidgetHeight;
   const int actualWidgetWidth   = myQSimGLViewWidget.width();                       // Same as OpenGL Window width.
   myQSimMainWindowTextEdit.resize( actualWidgetWidth, minimumWidgetHeight ); 
}


//------------------------------------------------------------------------------
void  QSimMainWindow::CreateMainWindowDockWidgets()
{
  // Although there may be dockWidgets on top, left, right, and bottom of main widget,
  // there can be multiple rows or columns of dockWidgets by setDockNestingEnabled( true ).
  this->setDockNestingEnabled( false );

  // Make a text area under the main window (for now - later should be the RUN button).
  this->CreateTextEditor();

  // Initially put the date in the title (d, dd, ddd, dddd, M, MM, MM, MMMM, yy, yyyy are various format options).
  // Similarly for QTime::currentTime().toString("h m ss");
  QString currentDate = QDate::currentDate().toString("MMMM, d yyyy");
  QDockWidget *bottomDockWidget = new QDockWidget( tr("Messages") + ":  " + currentDate, this );
  bottomDockWidget->setAllowedAreas( Qt::BottomDockWidgetArea );
  bottomDockWidget->setWidget( &myQSimMainWindowTextEdit );

  // Do not allow widget under the OpenGL window to close, move, or float.
  bottomDockWidget->setFeatures( QDockWidget::NoDockWidgetFeatures );
  this->addDockWidget( Qt::BottomDockWidgetArea, bottomDockWidget );

  // Determine which dock widgets overlap the corners.
  this->setCorner( Qt::BottomLeftCorner,  Qt::BottomDockWidgetArea );
  this->setCorner( Qt::BottomRightCorner, Qt::BottomDockWidgetArea );
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
   mainWindowInApplication.setWindowTitle( "QSim Crazy Widget" );
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
   QDialog splashScreenDialog( this, Qt::Dialog );
   splashScreenDialog.setWindowTitle( "QSim:  Easy-to-use Biomechanics Software" );
   splashScreenDialog.setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding );

   // Create layout manager for splash screen.
   QVBoxLayout layoutManager( &splashScreenDialog );

   // Labels can contain pictures of various formats (e.g., BMP, GIF, JPG, PNG, PBM)
   QLabel logoLabel( &splashScreenDialog );
   QPixmap jpgLogoAsPixmap( ":/MiscImages/QSimLogoWithNames.jpg", "JPG" );
   logoLabel.setPixmap( jpgLogoAsPixmap );
   logoLabel.setAlignment( Qt::AlignHCenter );
   layoutManager.addWidget( &logoLabel );

   // Show the dialog box for a few seconds.
   splashScreenDialog.show();
   splashScreenDialog.repaint();
   SleepInMilliseconds(  2000 );
}


//-----------------------------------------------------------------------------
void QSimMainWindow::DisplayHelpAboutScreen()
{
   QDialog displayHelpAboutDialog( this, Qt::Dialog );
   displayHelpAboutDialog.setWindowTitle(  NULL  );
   displayHelpAboutDialog.setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding );

   // Create layout manager for splash screen.
   QVBoxLayout layoutManager( &displayHelpAboutDialog );

   // Labels can contain pictures of various formats (e.g., BMP, GIF, JPG, PNG, PBM)
   QLabel logoLabel( &displayHelpAboutDialog );
   QPixmap jpgLogoAsPixmap( ":/MiscImages/QSimLogoWithNames.jpg", "JPG" );
   logoLabel.setPixmap( jpgLogoAsPixmap );
   logoLabel.setAlignment( Qt::AlignHCenter );
   layoutManager.addWidget( &logoLabel );

   // Alow this dialog to be resized.
   displayHelpAboutDialog.setSizeGripEnabled( false );        // Do not allow this dialog to be resized.
   displayHelpAboutDialog.setWindowModality( Qt::NonModal );  // May be same as  displayHelpAboutDialog.setModal( false ); 

   // Show the dialog box for a few seconds.
   displayHelpAboutDialog.show();
   displayHelpAboutDialog.repaint();
   displayHelpAboutDialog.exec();
}





//-----------------------------------------------------------------------------
void  QSimMainWindow::OpenOrSaveOrSaveAsFile( const QFileDialog::AcceptMode acceptModeOpenOrSave )
{
   QFileDialog fileOpenDialog( this, Qt::Dialog );
   fileOpenDialog.setWindowTitle( acceptModeOpenOrSave== QFileDialog::AcceptOpen ? tr("Open file") : tr("Save file") );

   // setAcceptMode can be set to one of the following.
   // QFileDialog::AcceptOpen   dialog is for opening files.
   // QFileDialog::AcceptSave   dialog is for saving  files.
   fileOpenDialog.setAcceptMode( acceptModeOpenOrSave );

   // setFileMode can be set to one of the following.
   // QFileDialog::AnyFile        The name of a file, whether it exists or not (useful for Save As file dialog).
   // QFileDialog::ExistingFile   The name of a single existing file.
   // QFileDialog::Directory      The name of a directory. Both files and directories are displayed.
   // QFileDialog::ExistingFiles  The names of zero or more existing files.
   const bool tryToOpenFile =  acceptModeOpenOrSave == QFileDialog::AcceptOpen;
   const QFileDialog::FileMode fileMode =  tryToOpenFile ? QFileDialog::ExistingFile : QFileDialog::AnyFile;
   fileOpenDialog.setFileMode( fileMode );

   // setViewMode can be set to one of the following.
   // QFileDialog::Detail  Displays an icon, a name, and details for each item in the directory.
   // QFileDialog::List    Displays only an icon and a name for each item in the directory.
   fileOpenDialog.setViewMode( QFileDialog::Detail );

   // Note: Separate multiple filters with two semicolons, e.g.:  "Images (*.png *.jpg);;Text files (*.txt);;XML files (*.xml)"
   // fileOpenDialog.setNameFilter( tr("Image Files (*.png *.jpg *.bmp)") );

   // Start the navigation for this method using the previous folder (if one exists)
   if( myPreviousFileDialogWorkingDirectory.exists()  )
      fileOpenDialog.setDirectory( myPreviousFileDialogWorkingDirectory );

   // User may just cancel this file open or save operation.
   if( !fileOpenDialog.exec() )  return;

   // Determine if the user just cancelled this operation or is progressing.
   QStringList filenameList = fileOpenDialog.selectedFiles();
   if( filenameList.count() == 0 ) return;
   if( filenameList.count() == 1 ) myPreviousFileDialogWorkingDirectory = fileOpenDialog.directory();

   // Try to open the first file in read-only mode and as a QFile::Text (text, not binary file).
   // On Unix and Mac OS X, QFile::Text makes no difference, but on Windows, it ensures "\r\n" end-of-line sequences are converted to "\n" when reading.
   QString filenamei = filenameList[0];
   QFile filei( filenamei );
   if( true || !filei.open( QFile::ReadOnly | QFile::Text) )
   {
      QMessageBox::warning( this, tr("Application"), tr("Cannot read file %1:\n%2.") .arg(filenamei) .arg(filei.errorString()), QMessageBox::Ok, QMessageBox::NoButton );
      QMessageBox::information( this, tr("1st argument to information message box"), tr("2nd argument to information message box"), QMessageBox::Ok, QMessageBox::NoButton );
      QMessageBox::question( this, tr("1st argument to question message box"), tr("2nd argument to question message box"), QMessageBox::Ok, QMessageBox::NoButton );
      QMessageBox::critical( this, tr("1st argument to critical message box"), tr("2nd argument to critical message box"), QMessageBox::Ok, QMessageBox::NoButton );
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



#if 0
//-----------------------------------------------------------------------------
void QSimMainWindow::CreateToolbarGeometry()
{
   // Geometry toolbar is on the left-hand-side of the main window.
   // The first line below always creates a toolbar at the Qt::TopToolBarArea (whether or not you want it there).
   // To move it elsewhere, you then must use:  this->addToolBar( Qt::SomeOtherToolBarArea, toolBar );
   QToolBar *toolBarA = this->addToolBar( tr("Geometry toolbar A") );
   this->addToolBar( Qt::LeftToolBarArea, toolBarA );
   toolBarA->setAllowedAreas( Qt::LeftToolBarArea );
   toolBarA->setMovable( false );
   toolBarA->setFloatable( false );
   toolBarA->setContentsMargins( 0, 0, 0, 0 );  // Separation of contents (left,top,right,bottom)


   // Associate the tool buttons with their actions and size them.
   myDrawSphereToolButton.setDefaultAction( &myDrawSphereAction );  myDrawSphereToolButton.setIconSize( QSize(50,50) );
   myDrawCubeToolButton.setDefaultAction( &myDrawCubeAction );        myDrawCubeToolButton.setIconSize( QSize(50,50) );

   QFrame *frame1 = new QFrame( this );
   frame1->setFrameShape( QFrame::NoFrame );  // Or QFrame::Box or QFrame::Panel or QFrame::StyledPanel or ...
   frame1->setFrameShadow( QFrame::Plain );   // Or QFrame::Raised or QFrame::QFrame::Sunken
   frame1->setLineWidth( 0 );                 // Width of frame (if one is used).
   frame1->setContentsMargins( 0, 0, 0, 0 );  // Separation of contents (left,top,right,bottom)

   QGridLayout *gridLayout = new QGridLayout( this );
   gridLayout->setSpacing( 0 );
   QLabel *dumb1 = new QLabel( "Hello" );
   QLabel *dumb2 = new QLabel( "World" );
   gridLayout->addWidget( dumb1, 0, 0 );
   gridLayout->addWidget( dumb2, 0, 1 );
   gridLayout->addWidget( &myDrawSphereToolButton, 1, 0 );
   gridLayout->addWidget( &myDrawCubeToolButton,   1, 1 );
   frame1->setLayout( gridLayout );
   toolBarA->addWidget( frame1 );

#if 0
   toolBarA->setOrientation( Qt::Horizontal );
   toolBarA->addAction( &myDrawCubeAction     );
   toolBarA->addAction( &myDrawSphereAction   );
   toolBarA->addAction( &myDrawConeFullAction  );
   toolBarA->addAction( &myDrawTorsoAndLowerExtremityAction );
   toolBarA->addAction( &myDrawLowerExtremityOnlyAction     );
   toolBarA->addAction( &myDrawLowerLimbAction              );

   // Make the geometry icons a little larger.
   QSize iconSize = toolBarA->iconSize();
   toolBarA->setIconSize( 1.4 * iconSize );

   // Add a widget to group toolbuttons.
   QWidget *wildWidget = new QWidget( this );
   toolBarA->addWidget( wildWidget );
   QGridLayout *gridLayout = new QGridLayout( this );
   gridLayout->addWidget( &QToolButton(this) );
   gridLayout->addWidget( &QToolButton(this) );
//   gridLayout->addWidget( toolBarA->addAction(&myDrawLowerLimbAction) );

   // If desirable, create another toolbar below the previous one (on the same vertical line).
   // Or if desirable, add a "line-break" to create a second vertical column of toolbars/icons.
   this->addToolBarBreak();
   QToolBar *toolBarB = this->addToolBar( tr("Geometry toolbar B") );
   this->addToolBar( Qt::LeftToolBarArea, toolBarB );
   toolBarB->setAllowedAreas( Qt::LeftToolBarArea );
   toolBarB->setMovable( false );
   toolBarB->setFloatable( false );
   toolBarB->setContentsMargins( 0, 0, 0, 0 );  // Separation of contents (left,top,right,bottom)
   toolBarB->setOrientation( Qt::Horizontal );
   toolBarB->addAction( &myDrawCylinderAction );
   toolBarB->addAction( &myDrawConeCapAction  );
   toolBarB->addAction( &myDrawTorusAction    );
#endif
}
#endif



//------------------------------------------------------------------------------
}  // End of namespace QSim





