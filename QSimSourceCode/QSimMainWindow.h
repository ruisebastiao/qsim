//-----------------------------------------------------------------------------
// File:     QSimMainWindow.h
// Class:    QSimMainWindow
// Parent:   QMainWindow
// Purpose:  Main window for Qt application.
/* ---------------------------------------------------------------------------- *
* QSim was developed with support from Simbios (NIH Center for Physics-Based    *
* Simulation of Biological Structures at Stanford) under NIH Roadmap for        *
* Medical Research grant U54 GM072970 and NCSRR (National Center for Simulation *
* in Rehabilitation Research) NIH research infrastructure grant R24 HD065690.   *
*                                                                               *
* To the extent possible under law, the author(s) and contributor(s) have       *
* dedicated all copyright and related and neighboring rights to this software   *
* to the public domain worldwide. This software is distributed without warranty.*
*                                                                               *
* Authors: Paul Mitiguy (2011)                                                  *
* Contributors: Ayman Habib, Michael Sherman                                    *
*                                                                               *
* Permission is granted, free of charge, to any person obtaining a copy of this *
* software and associated documentation files (the "Software"), to deal in the  *
* Software without restriction, including without limitation the rights to use, *
* copy, modify, merge, publish, distribute, sublicense, and/or sell copies of   *
* the Software and to permit persons to whom the Software is furnished to do so.*
*                                                                               *
* Include this sentence, the above public domain and permission notices, and the*
* following disclaimer in all copies or substantial portions of the Software.   *
*                                                                               *
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR    *
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,      *
* FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL THE  *
* AUTHORS OR CONTRIBUTORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,  *
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR  *
* IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. *
* ----------------------------------------------------------------------------- */
#ifndef  QSIMMAINWINDOW_H___ 
#define  QSIMMAINWINDOW_H___
#include <QtCore>
#include <QtGui>
#include "CppStandardHeaders.h"
#include "QActionHelper.h"
#include "QSimToolBarGeometry.h"
#include "QSimStartSimulation.h"
#include "QPlainTextReadWrite.h"
#include "QSimGLViewWidget.h"

//------------------------------------------------------------------------------
namespace QSim {


//-----------------------------------------------------------------------------
class QSimMainWindow : public QMainWindow
{
   Q_OBJECT

public:
   // Constructors and destructors.
   QSimMainWindow( const int numberOfCommandLineArguments, char *arrayOfCommandLineArguments[] )  { this->ConstructorQSimMainWindow(numberOfCommandLineArguments,arrayOfCommandLineArguments); }
   QSimMainWindow()  { this->ConstructorQSimMainWindow(0,NULL); }
  ~QSimMainWindow() {;}

   // Public method for accessing the main windows's GLWidget
   QSimGLViewWidget&  GetQSimMainWindowGLViewWidget()  { return myQSimGLViewWidget; }

   // Write a message to the status bar.
   void  WriteMessageToMainWindowStatusBar( const QString& message, const uint lengthOfTimeInMillisecondsOr0ForIndefinitely )  { this->statusBar()->showMessage(message,lengthOfTimeInMillisecondsOr0ForIndefinitely); }

private slots:
   // Slots for file menu.
   void  NewFileSlot()     { QMessageBox::information( this, tr("Debug message"), tr("New File Slot"), QMessageBox::Ok, QMessageBox::NoButton ); }  
   void  OpenFileSlot()    { this->OpenOrSaveOrSaveAsFile( QFileDialog::AcceptOpen ); }
   void  SaveFileSlot()    { this->OpenOrSaveOrSaveAsFile( QFileDialog::AcceptSave ); }
   void  SaveFileAsSlot()  { this->OpenOrSaveOrSaveAsFile( QFileDialog::AcceptSave ); }
   void  PrintFileSlot()   { QMessageBox::information( this, tr("Debug message"), tr("Print File Slot"), QMessageBox::Ok, QMessageBox::NoButton ); }
   void  ExitProgramSlot() { QCoreApplication::quit(); }
   
   // Slots for edit menu.
   void  EditCutSlot()     { QMessageBox::information( this, tr("Debug message"), tr("Edit Cut Slot"),    QMessageBox::Ok, QMessageBox::NoButton ); }
   void  EditCopySlot()    { QMessageBox::information( this, tr("Debug message"), tr("Edit Copy Slot"),   QMessageBox::Ok, QMessageBox::NoButton ); }    
   void  EditPasteSlot()   { QMessageBox::information( this, tr("Debug message"), tr("Edit Paste Slot"),  QMessageBox::Ok, QMessageBox::NoButton ); } 
   void  EditDeleteSlot()  { this->GetQSimMainWindowGLViewWidget().RemoveSelectedSceneNodesFromQSimGLViewWidget(); } 

   // Slots for help menu.
   void  HelpAboutSlot()     { this->DisplayHelpAboutScreen(); }
   void  HelpContentsSlot()  { this->CreateCrazyWidget(); }

   // Slots for simulate menu.
   void  SlotStartSimulationFromMainApplicationWindowSimbody()    { StartAndRunSimulationMathematicsEngineNoGui( true  ); }  
   void  SlotStartSimulationFromMainApplicationWindowOpenSimApi() { StartAndRunSimulationMathematicsEngineNoGui( false ); }  

private:
   void  AddAllActionsWhoAreChildrenOfQSimMainWindow();
   void  CreateMainWindowFileMenu();
   void  CreateMainWindowEditMenu();
   void  CreateMainWindowSimulateMenu();
   void  CreateMainWindowHelpMenu();
   void  CreateCrazyWidget();
   void  CreateMainWindowToolbarEditEtc();
   void  CreateMainWindowDockWidgets();
   void  DisplaySplashScreen();
   void  DisplayHelpAboutScreen();
   void  CreateTextEditor();

   // Add a status bar at the bottom of the very bottom of the application (helpful for notes, warnings, and messages).
   void  CreateMainWindowStatusBar()  { this->WriteMessageToMainWindowStatusBar( tr("Status message"), 0 ); }

   // All constructors call this method.
   void  ConstructorQSimMainWindow( const int numberOfCommandLineArguments, char *arrayOfCommandLineArguments[] );

   // Actions for file menu.
   QActionHelper  myExitProgramAction;
   QActionHelper  myNewFileAction;
   QActionHelper  myOpenFileAction;
   QActionHelper  mySaveFileAction;
   QActionHelper  mySaveFileAsAction;
   QActionHelper  myPrintFileAction;

   // Actions for edit menu.
   QActionHelper  myEditCutAction;
   QActionHelper  myEditCopyAction;
   QActionHelper  myEditPasteAction;
   QActionHelper  myEditDeleteAction;

   // Actions and buttons for geometry toolbar.
   QSimToolBarGeometry  myToolBarGeometry;

   // Actions for Simulate menu.
   QActionHelper  mySimulateStartSimbodyAction;
   QActionHelper  mySimulateStartOpenSimApiAction;

   // Actions for help menu.
   QActionHelper  myHelpAboutAction;
   QActionHelper  myHelpContentsAction;

   // Main routine for opening or saving files (restores previous directory).
   void  OpenOrSaveOrSaveAsFile( const QFileDialog::AcceptMode acceptModeOpenOrSave );

   // Keep track of the last folder that was used to open or save a file.
   const QDir&  GetPreviousFileDialogWorkingDirectory( void )             { return myPreviousFileDialogWorkingDirectory; }
   const QDir&  GetPreviousFileDialogWorkingDirectory( const QDir& dir )  { return myPreviousFileDialogWorkingDirectory = dir; }
   QDir  myPreviousFileDialogWorkingDirectory;

   // Currently the "central widget".
   QSimGLViewWidget  myQSimGLViewWidget;
   QPlainTextEdit myQSimMainWindowTextEdit;
//   QPlainTextReadWrite  myQSimMainWindowTextEdit;
};





//------------------------------------------------------------------------------
}  // End of namespace QSim
//--------------------------------------------------------------------------
#endif  // QSIMMAINWINDOW_H___
//--------------------------------------------------------------------------
