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
#ifndef  QSIMMAINWINDOW_H___ 
#define  QSIMMAINWINDOW_H___
#include "CppStandardHeaders.h"
#include "QActionHelper.h"
#include "QSimToolBarGeometry.h"
#include "QSimStartSimulation.h"
#include "QPlainTextReadWrite.h"
#include "QSimGLViewWidget.h"
#include <QtCore>
#include <QtGui>


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
   void  HelpAboutSlot()     { this->DisplayHelpAboutScreen(); }
   void  HelpContentsSlot()  { this->CreateCrazyWidget(); }

   // Slots for simulate menu.
   void  SlotStartSimulationFromMainApplicationWindow() { StartAndRunSimulationMathematicsEngineNoGui(); }  

#if 0
   // Slots for geometry toolbar.
   void  DrawSphereSlot()   { ; }
   void  DrawCubeSlot()     { ; }
   void  DrawCylinderSlot() { ; }
   void  DrawConeCapSlot()  { ; }
   void  DrawConeFullSlot() { ; }
   void  DrawTorusSlot()    { ; }
   void  DrawTorsoAndLowerExtremityModelSlot()  { ; }
   void  DrawLowerExtremityOnlyModelSlot()      { ; }
   void  DrawLowerLimbModelSlot()               { ; }
#endif

private:
   void  AddAllActionsWhoAreChildrenOfQSimMainWindow();
   void  AddActionAsChildOfThis( QAction& action, const QString& textName, const char *pathToIconFileOrNull );
   void  AddActionAsChildOfThis( QAction& action, const QString& textName, const QKeySequence& keySequenceShortcut, const char *pathToIconFileOrNull ) { this->AddActionAsChildOfThis( action, textName, pathToIconFileOrNull );  action.setShortcut( keySequenceShortcut ); }
   void  CreateFileMenu();
   void  CreateEditMenu();
   void  CreateHelpMenu();
   void  CreateSimulateMenu();
   void  CreateCrazyWidget();
   void  CreateToolbarEditEtc();
   void  CreateDockWidgets();
   void  CreateStatusBar();
   void  DisplaySplashScreen();
   void  DisplayHelpAboutScreen();
   void  CreateTextEditor();

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
#if 0
   QActionHelper  myDrawSphereAction;
   QActionHelper  myDrawCubeAction;
   QActionHelper  myDrawCylinderAction;
   QActionHelper  myDrawConeCapAction;
   QActionHelper  myDrawConeFullAction;
   QActionHelper  myDrawTorusAction;
   QActionHelper  myDrawTorsoAndLowerExtremityAction;
   QActionHelper  myDrawLowerExtremityOnlyAction;
   QActionHelper  myDrawLowerLimbAction;
   QToolButton myDrawSphereToolButton;
   QToolButton myDrawCubeToolButton;
#endif

   // Actions for Simulate menu.
   QActionHelper  mySimulateStartAction;

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
