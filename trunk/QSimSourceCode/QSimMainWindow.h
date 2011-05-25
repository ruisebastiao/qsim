//-----------------------------------------------------------------------------
// File:     QSimMainWindow.h
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
#include "CppStandardHeaders.h"
#include "QSimStartSimulation.h"
#include <QtCore>
#include <QtGui>


//------------------------------------------------------------------------------
#ifndef  QSIMMAINWINDOW_H___ 
#define  QSIMMAINWINDOW_H___


//------------------------------------------------------------------------------
namespace QSim {


//-----------------------------------------------------------------------------
class QSimMainWindow : public QMainWindow
{
   Q_OBJECT

public:
   // Constructors and destructors.
   QSimMainWindow();
  ~QSimMainWindow() {;}

private slots:
   // Slots for file menu.
   void  NewFileSlot()     { ; }  
   void  OpenFileSlot()    { this->OpenOrSaveOrSaveAsFile( QFileDialog::AcceptOpen ); }
   void  SaveFileSlot()    { this->OpenOrSaveOrSaveAsFile( QFileDialog::AcceptSave ); }
   void  SaveFileAsSlot()  { this->OpenOrSaveOrSaveAsFile( QFileDialog::AcceptSave ); }
   void  PrintFileSlot()   { ; }
   void  ExitProgramSlot() { QCoreApplication::quit(); }
   
   // Slots for edit menu.
   void  EditCutSlot()     { ; }
   void  EditCopySlot()    { ; }
   void  EditPasteSlot()   { ; }
   void  EditDeleteSlot()  { ; }

   // Slots for help menu.
   void  HelpAboutSlot()     { this->CreateCrazyWidget(); }
   void  HelpContentsSlot()  { ; }

   // Slots for Simulate menu.
   void  SlotStartSimulationFromMainApplicationWindow() { StartAndRunSimulationMathematicsEngineNoGui(); }  

private:
   void  AddActionToMainWindowMenu( QAction& action, QMenu& mainWindowMenu, const QString& textName, const char *pathToIconFile );
   void  AddActionToMainWindowMenu( QAction& action, QMenu& mainWindowMenu, const QString& textName, const QKeySequence& keySequenceShortcut, const char *pathToIconFile )  { action.setShortcut( keySequenceShortcut );   this->AddActionToMainWindowMenu( action, mainWindowMenu, textName, pathToIconFile ); }
   void  CreateFileMenu();
   void  CreateEditMenu();
   void  CreateHelpMenu();
   void  CreateSimulateMenu();
   void  CreateCrazyWidget();
   void  DisplaySplashScreen();

   // void  CreateToolBars();
   // void  CreateStatusBar();

   // Actions for file menu.
   QAction  myExitProgramAction;
   QAction  myNewFileAction;
   QAction  myOpenFileAction;
   QAction  mySaveFileAction;
   QAction  mySaveFileAsAction;
   QAction  myPrintFileAction;

   // Actions for edit menu.
   QAction  myEditCutAction;
   QAction  myEditCopyAction;
   QAction  myEditPasteAction;
   QAction  myEditDeleteAction;

   // Actions for help menu.
   QAction  myHelpAboutAction;
   QAction  myHelpContentsAction;

   // Actions for Simulate menu.
   QAction  mySimulateStartAction;

   // Main routine for opening or saving files (restores previous directory).
   void  OpenOrSaveOrSaveAsFile( const QFileDialog::AcceptMode acceptModeOpenOrSave );

   // Keep track of the last folder that was used to open or save a file.
   const QDir&  GetPreviousFileDialogWorkingDirectory( void )             { return myPreviousFileDialogWorkingDirectory; }
   const QDir&  GetPreviousFileDialogWorkingDirectory( const QDir& dir )  { return myPreviousFileDialogWorkingDirectory = dir; }
   QDir  myPreviousFileDialogWorkingDirectory;

   // Currently the "central widget".
   QTextEdit  myQSimMainWindowTextEdit;
};





//------------------------------------------------------------------------------
}  // End of namespace QSim


//--------------------------------------------------------------------------
#endif  // QSIMMAINWINDOW_H___
//--------------------------------------------------------------------------
