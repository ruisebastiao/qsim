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


//------------------------------------------------------------------------------
namespace QSim {


//-----------------------------------------------------------------------------
QSimMainWindow::QSimMainWindow() : myExitProgramAction(NULL), myNewFileAction(NULL), myOpenFileAction(NULL), mySaveFileAction(NULL), mySaveFileAsAction(NULL), myEditCopyAction(NULL), myEditCutAction(NULL), myEditPasteAction(NULL), myHelpAboutAction(NULL), myHelpContentsAction(NULL)
{
   // Complete the class construction.
   this->setCentralWidget( &myQSimMainWindowTextEdit );
   this->CreateFileMenu();
   this->CreateEditMenu();
   this->CreateHelpMenu();
}


//------------------------------------------------------------------------------
void  QSimMainWindow::AddActionToMainWindowMenu( QAction *action, QMenu *mainWindowMenu, const char *textName, const char *pathToIconFile )
{
   action->setParent( this );
   action->setText( tr(textName) );
// action->setIcon( QIcon(pathToIconFile) );
   mainWindowMenu->addAction( action );
}


//------------------------------------------------------------------------------
void  QSimMainWindow::AddActionToMainWindowMenu( QAction *action, QMenu *mainWindowMenu, const char *textName, const QKeySequence& keySequenceShortcut, const char *pathToIconFile )
{
   action->setShortcut( keySequenceShortcut );
   this->AddActionToMainWindowMenu( action, mainWindowMenu, textName, pathToIconFile );
}


//-----------------------------------------------------------------------------
void QSimMainWindow::CreateFileMenu()
{
   // Create actions (user-interface objects inserted into widgets) that allow a program to standardize
   // performance and keeps in sync identical commands invocable via menus, toolbar buttons, and/or keyboard shortcuts.
   //---------------------------------------
   QMenuBar* mainWindowMenuBar = this->menuBar();                // Creates/Gets/Owns QMainWindow menuBar.
   QMenu* fileMenu = mainWindowMenuBar->addMenu( tr("&File") );  // Creates/Gets/Owns this menu.

   this->AddActionToMainWindowMenu( &myNewFileAction,  fileMenu, "&New file",  QKeySequence::New,  ":/QSimIcons/NewFileIcon.png" );
   QObject::connect( &myNewFileAction, SIGNAL(triggered()), this, SLOT(NewFileSlot()) );

   this->AddActionToMainWindowMenu( &myOpenFileAction, fileMenu, "&Open file", QKeySequence::Open, ":/QSimIcons/OpenFileIcon.png" );
   QObject::connect( &myOpenFileAction, SIGNAL(triggered()), this, SLOT(OpenFileSlot()) );

   this->AddActionToMainWindowMenu( &mySaveFileAction, fileMenu, "&Save file", QKeySequence::Save, ":/QSimIcons/SaveFileIcon.png" );
   QObject::connect( &mySaveFileAction, SIGNAL(triggered()), this, SLOT(SaveFileSlot()) );

   this->AddActionToMainWindowMenu( &mySaveFileAsAction, fileMenu, "Save file as", QKeySequence::SaveAs, ":/QSimIcons/SaveFileAsIcon.png" );
   QObject::connect( &mySaveFileAsAction, SIGNAL(triggered()), this, SLOT(SaveFileAsSlot()) );

   fileMenu->addSeparator();
   this->AddActionToMainWindowMenu( &myExitProgramAction, fileMenu, "&Quit/Exit program", QKeySequence::Quit, ":/QSimIcons/QuitExitIcon.png" );
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

   this->AddActionToMainWindowMenu( &myEditCutAction,   editMenu, "&Cut",   QKeySequence::Cut,   ":/QSimIcons/EditCutIcon.png" );
   QObject::connect( &myEditCutAction,   SIGNAL(triggered()), this, SLOT(EditCutSlot()) );

   this->AddActionToMainWindowMenu( &myEditCopyAction,  editMenu, "&Copy",  QKeySequence::Copy,  ":/QSimIcons/EditCopyIcon.png" );
   QObject::connect( &myEditCopyAction,  SIGNAL(triggered()), this, SLOT(EditCopySlot()) );

   this->AddActionToMainWindowMenu( &myEditPasteAction, editMenu, "&Paste", QKeySequence::Paste, ":/QSimIcons/EditPasteIcon.png" );
   QObject::connect( &myEditPasteAction, SIGNAL(triggered()), this, SLOT(EditPasteSlot()) );
}


//-----------------------------------------------------------------------------
void QSimMainWindow::CreateHelpMenu()
{
   // Create actions (user-interface objects inserted into widgets) that allow a program to standardize
   // performance and keeps in sync identical commands invocable via menus, toolbar buttons, and/or keyboard shortcuts.
   //---------------------------------------
   QMenuBar* mainWindowMenuBar = this->menuBar();                // Creates/Gets/Owns QMainWindow menuBar.
   QMenu* helpMenu = mainWindowMenuBar->addMenu( tr("&Help") );  // Creates/Gets/Owns this menu.

   this->AddActionToMainWindowMenu( &myHelpAboutAction, helpMenu, "&About", ":/QSimIcons/HelpAboutIcon.png" );
   QObject::connect( &myHelpAboutAction,   SIGNAL(triggered()), this, SLOT(HelpAboutSlot()) );

   this->AddActionToMainWindowMenu( &myHelpContentsAction,  helpMenu, "&Help",  QKeySequence::HelpContents,  ":/QSimIcons/HelpContentsIcon.png" );
   QObject::connect( &myHelpContentsAction,   SIGNAL(triggered()), this, SLOT(HelpContentsSlot()) );
}




//------------------------------------------------------------------------------
}  // End of namespace QSim

