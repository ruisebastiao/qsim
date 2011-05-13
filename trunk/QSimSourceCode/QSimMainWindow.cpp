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
QSimMainWindow::QSimMainWindow() : myExitProgramAction(NULL), myNewFileAction(NULL), myOpenFileAction(NULL), mySaveFileAction(NULL), mySaveFileAsAction(NULL)
{
   // Complete the class construction.
   this->setCentralWidget( &myQSimMainWindowTextEdit );
   this->CreateFileMenu();
}


//-----------------------------------------------------------------------------
void QSimMainWindow::CreateFileMenu()
{
   // Create actions (user-interface objects inserted into widgets) that allow a program to standardize
   // performance and keeps in sync identical commands invocable via menus, toolbar buttons, and/or keyboard shortcuts.
   //---------------------------------------
   QMenuBar* mainWindowMenuBar = this->menuBar();                // Creates/Gets/Owns QMainWindow menuBar.
   QMenu* fileMenu = mainWindowMenuBar->addMenu( tr("&File") );  // Creates/Gets/Owns this menu.

   myNewFileAction.setParent( this );
   myNewFileAction.setIconText( tr("&NewFile") );
   // myNewFileAction.setIcon( ":/QSimIcons/NewFileIcon.png" );
   myNewFileAction.setShortcuts( QKeySequence::New );
   QObject::connect( &myNewFileAction, SIGNAL(triggered()), this, SLOT(NewFileSlot()) );
   fileMenu->addAction( &myNewFileAction );

   myOpenFileAction.setParent( this );
   myOpenFileAction.setIconText( tr("&OpenFile") );
   // myOpenFileAction.setIcon( ":/QSimIcons/OpenFileIcon.png" );
   myNewFileAction.setShortcuts( QKeySequence::Open );
   QObject::connect( &myOpenFileAction, SIGNAL(triggered()), this, SLOT(OpenFileSlot()) );
   fileMenu->addAction( &myOpenFileAction );

   mySaveFileAction.setParent( this );
   mySaveFileAction.setIconText( tr("&SaveFile") );
   // mySaveFileAction.setIcon( ":/QSimIcons/SaveFileIcon.png" );
   mySaveFileAction.setShortcuts( QKeySequence::Save );
   QObject::connect( &mySaveFileAction, SIGNAL(triggered()), this, SLOT(SaveFileSlot()) );
   fileMenu->addAction( &mySaveFileAction );

   mySaveFileAsAction.setParent( this );
   mySaveFileAsAction.setIconText( tr("&SaveFileAs") );
   // mySaveFileAsAction.setIcon( ":/QSimIcons/SaveFileAsIcon.png" );
   mySaveFileAsAction.setShortcuts( QKeySequence::SaveAs );
   QObject::connect( &mySaveFileAsAction, SIGNAL(triggered()), this, SLOT(SaveFileAsSlot()) );
   fileMenu->addAction( &mySaveFileAsAction );

   myExitProgramAction.setParent( this );
   myExitProgramAction.setIconText( tr("&ExitProgram") );
   // myExitProgramAction.setIcon( ":/QSimIcons/ExitProgramIcon.png" );
   myNewFileAction.setShortcuts( QKeySequence::New );
   QObject::connect( &myNewFileAction, SIGNAL(triggered()), this, SLOT(NewFileSlot()) );
   fileMenu->addSeparator();
   fileMenu->addAction( &myExitProgramAction );

   // editMenu = menuBar()->addMenu(tr("&Edit"));
   // editMenu->addAction(cutAct);
   // editMenu->addAction(copyAct);
   // editMenu->addAction(pasteAct);
   //
   // menuBar()->addSeparator();
   //
   // helpMenu = menuBar()->addMenu(tr("&Help"));
   // helpMenu->addAction(aboutAct);
   // helpMenu->addAction(aboutQtAct);
}





//------------------------------------------------------------------------------
}  // End of namespace QSim

