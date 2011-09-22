//-----------------------------------------------------------------------------
// File:     QSimToolBarGeometry.h
// Class:    QSimToolBarGeometry
// Parent:   QSimToolBar
// Purpose:  Geometry toolbar in main window for Qt application.
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
#ifndef  QSIMTOOLBARGEOMETRY_H___ 
#define  QSIMTOOLBARGEOMETRY_H___
#include <QtCore>
#include <QtGui>
#include "CppStandardHeaders.h"
#include "QActionHelper.h"


//------------------------------------------------------------------------------
namespace QSim {

// Forward declaration
class QSimMainWindow;


//-----------------------------------------------------------------------------
class QSimToolBarGeometry : public QToolBar
{
   Q_OBJECT

public:
   // Constructors and destructors.
   QSimToolBarGeometry() { myMainWindow = NULL; }
  ~QSimToolBarGeometry() { myMainWindow = NULL; }

   // Completes construction of the class and adds this to the mainWindow.
   void  AddToolbarGeometryToMainWindow( QSimMainWindow &mainWindow );

private slots:
   // Slots for geometry toolbar.
   void  DrawConeCapSlot();
   void  DrawConeFullSlot();
   void  DrawCylinderSlot();
   void  DrawRectangularBoxSlot();
   void  DrawSphereSlot();
   void  DrawTorusSlot();
   void  DrawTorsoAndLowerExtremityModelSlot()  { QMessageBox::information( this, tr("Debug message"), tr("Draw Torso and lower extremity Slot"), QMessageBox::Ok, QMessageBox::NoButton ); }
   void  DrawLowerExtremityOnlyModelSlot()      { QMessageBox::information( this, tr("Debug message"), tr("Draw LowerExtremity only Slot"), QMessageBox::Ok, QMessageBox::NoButton ); }
   void  DrawLowerLimbModelSlot();

private:
   // Keep track of the mainWindow.
   QSimMainWindow  *myMainWindow;

   // Widget for this toolbar.
   QFrame  myToolbarGeometryContainerWidget;
   
   // Layout for this toolbar.
   QGridLayout  myGridLayout;

   // Actions for geometry toolbar.
   QActionHelper  myDrawSphereAction;
   QActionHelper  myDrawRectangularBoxAction;
   QActionHelper  myDrawCylinderAction;
   QActionHelper  myDrawConeCapAction;
   QActionHelper  myDrawConeFullAction;
   QActionHelper  myDrawTorusAction;
   QActionHelper  myDrawTorsoAndLowerExtremityAction;
   QActionHelper  myDrawLowerExtremityOnlyAction;
   QActionHelper  myDrawLowerLimbAction;

   // Buttons for geometry toolbar.
   QToolButton  myDrawSphereToolButton;
   QToolButton  myDrawRectangularBoxToolButton;
   QToolButton  myDrawCylinderButton;
   QToolButton  myDrawConeCapButton;
   QToolButton  myDrawConeFullButton;
   QToolButton  myDrawTorusButton;
   QToolButton  myDrawTorsoAndLowerExtremityButton;
   QToolButton  myDrawLowerExtremityOnlyButton;
   QToolButton  myDrawLowerLimbButton;
};


//------------------------------------------------------------------------------
}  // End of namespace QSim
//--------------------------------------------------------------------------
#endif  // QSIMTOOLBARGEOMETRY_H___
//--------------------------------------------------------------------------
