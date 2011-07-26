//-----------------------------------------------------------------------------
// File:     QSimToolBarGeometry.cpp
// Class:    QSimToolBarGeometry
// Parent:   QToolBar
// Purpose:  Geometry toolbar in main window for Qt application.
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
#include "QSimToolbarGeometry.h"
#include "QSimMainWindow.h"


//------------------------------------------------------------------------------
namespace QSim {


//------------------------------------------------------------------------------
void  QSimToolBarGeometry::AddToolbarGeometryToMainWindow( QSimMainWindow &mainWindow )
{
   // Keep track of this's main window.
   myMainWindow = &mainWindow;

   // Create actions associated with drawing geometry.
   myDrawSphereAction.AddActionHelper(                 tr("&Sphere"),                                         ":/MiscImages/BlueSolidsPublicDomainSphereTransparent120Pixel.png" );
   QObject::connect( &myDrawSphereAction,                  SIGNAL(triggered()), this, SLOT(DrawSphereSlot()) );

   myDrawRectangularBoxAction.AddActionHelper(         tr("&Rectangular box"),                                ":/MiscImages/BlueSolidsPublicDomainCubeTransparent120Pixel.png" );
   QObject::connect( &myDrawRectangularBoxAction,          SIGNAL(triggered()), this, SLOT(DrawRectangularBoxSlot()) );

   myDrawCylinderAction.AddActionHelper(               tr("C&ylinder"),                                       ":/MiscImages/BlueSolidsPublicDomainCylinderTransparent120Pixel.png" );
   QObject::connect( &myDrawCylinderAction,                SIGNAL(triggered()), this, SLOT(DrawCylinderSlot()) );

   myDrawConeCapAction.AddActionHelper(                tr("C&oneCap"),                                        ":/MiscImages/BlueSolidsPublicDomainConeCapTransparent120Pixel.png" );
   QObject::connect( &myDrawConeCapAction,                 SIGNAL(triggered()), this, SLOT(DrawConeCapSlot()) );

   myDrawConeFullAction.AddActionHelper(               tr("Co&neFull"),                                       ":/MiscImages/BlueSolidsPublicDomainConeFullTransparent120Pixel.png" );
   QObject::connect( &myDrawConeFullAction,                SIGNAL(triggered()), this, SLOT(DrawConeFullSlot()) );

   myDrawTorusAction.AddActionHelper(                  tr("&Torus"),                                          ":/MiscImages/BlueSolidsPublicDomainTorusTransparent120Pixel.png" );
   QObject::connect( &myDrawTorusAction,                   SIGNAL(triggered()), this, SLOT(DrawTorusSlot()) );

   myDrawTorsoAndLowerExtremityAction.AddActionHelper( tr("Torso &and lower extremity"),                      ":/MiscImages/OpenSimTorsoAndLowerExtremityModel.png" );
   QObject::connect( &myDrawTorsoAndLowerExtremityAction,  SIGNAL(triggered()), this, SLOT(DrawTorsoAndLowerExtremityModelSlot()) );

   myDrawLowerExtremityOnlyAction.AddActionHelper(     tr("&Lower extremity"),                                ":/MiscImages/OpenSimLowerExtremityOnlyModel.png" );
   QObject::connect( &myDrawLowerExtremityOnlyAction,      SIGNAL(triggered()), this, SLOT(DrawLowerExtremityOnlyModelSlot()) );

   myDrawLowerLimbAction.AddActionHelper(              tr("Lo&wer limb"),                                     ":/MiscImages/OpenSimLowerLimbModelEdithArnold.png" );
   QObject::connect( &myDrawLowerLimbAction,               SIGNAL(triggered()), this, SLOT(DrawLowerLimbModelSlot()) );

   // Associate the tool buttons with their actions and size them.
               myDrawSphereToolButton.setDefaultAction( &myDrawSphereAction );                              myDrawSphereToolButton.setIconSize( QSize(50,50) );
       myDrawRectangularBoxToolButton.setDefaultAction( &myDrawRectangularBoxAction );              myDrawRectangularBoxToolButton.setIconSize( QSize(50,50) );
                 myDrawCylinderButton.setDefaultAction( &myDrawCylinderAction );                              myDrawCylinderButton.setIconSize( QSize(50,50) );
                  myDrawConeCapButton.setDefaultAction( &myDrawConeCapAction );                                myDrawConeCapButton.setIconSize( QSize(50,50) );
                 myDrawConeFullButton.setDefaultAction( &myDrawConeFullAction );                              myDrawConeFullButton.setIconSize( QSize(50,50) );
                    myDrawTorusButton.setDefaultAction( &myDrawTorusAction );                                    myDrawTorusButton.setIconSize( QSize(50,50) );
   myDrawTorsoAndLowerExtremityButton.setDefaultAction( &myDrawTorsoAndLowerExtremityAction );  myDrawTorsoAndLowerExtremityButton.setIconSize( QSize(50,50) );
       myDrawLowerExtremityOnlyButton.setDefaultAction( &myDrawLowerExtremityOnlyAction );          myDrawLowerExtremityOnlyButton.setIconSize( QSize(50,50) );
                myDrawLowerLimbButton.setDefaultAction( &myDrawLowerLimbAction );                            myDrawLowerLimbButton.setIconSize( QSize(50,50) );

   myToolbarGeometryContainerWidget.setFrameShape( QFrame::NoFrame );  // Or QFrame::Box or QFrame::Panel or QFrame::StyledPanel or ...
   myToolbarGeometryContainerWidget.setFrameShadow( QFrame::Plain );   // Or QFrame::Raised or QFrame::QFrame::Sunken
   myToolbarGeometryContainerWidget.setLineWidth( 0 );                 // Width of frame (if one is used).
   myToolbarGeometryContainerWidget.setContentsMargins( 0, 0, 0, 0 );  // Separation of contents (left,top,right,bottom)
   myToolbarGeometryContainerWidget.setLayout( &myGridLayout );

   myGridLayout.setSpacing( 0 );
   myGridLayout.addWidget( &myDrawSphereToolButton,             0, 0 );
   myGridLayout.addWidget( &myDrawRectangularBoxToolButton,     0, 1 );
   myGridLayout.addWidget( &myDrawCylinderButton,               1, 0 );
   myGridLayout.addWidget( &myDrawTorusButton,                  1, 1 );
   myGridLayout.addWidget( &myDrawConeFullButton,               2, 0 );
   myGridLayout.addWidget( &myDrawConeCapButton,                2, 1 );
   myGridLayout.addWidget( &myDrawTorsoAndLowerExtremityButton, 3, 0 );
   myGridLayout.addWidget( &myDrawLowerExtremityOnlyButton,     3, 1 );
   myGridLayout.addWidget( &myDrawLowerLimbButton,              4, 0 );


   this->addWidget( &myToolbarGeometryContainerWidget );

   // Geometry toolbar is on the left-hand-side of the main window.
   // The first line below always creates a toolbar at the Qt::TopToolBarArea (whether or not you want it there).
   // To move it elsewhere, you then must use:  this->addToolBar( Qt::SomeOtherToolBarArea, toolBar );
   this->setWindowTitle( tr("Geometry toolbar") );
   mainWindow.addToolBar( Qt::LeftToolBarArea, this );
   this->setAllowedAreas( Qt::LeftToolBarArea );
   this->setMovable( false );
   this->setFloatable( false );
   this->setContentsMargins( 0, 0, 0, 0 );  // Separation of contents (left,top,right,bottom)
}


//------------------------------------------------------------------------------
void  QSimToolBarGeometry::DrawConeCapSlot()         { myMainWindow->GetQSimMainWindowGLViewWidget().AddTopLevelSceneNodeGeometryCone(  2, 1,    2, true ); }
void  QSimToolBarGeometry::DrawConeFullSlot()        { myMainWindow->GetQSimMainWindowGLViewWidget().AddTopLevelSceneNodeGeometryCone(  2, 0.01, 2, true ); }
void  QSimToolBarGeometry::DrawCylinderSlot()        { myMainWindow->GetQSimMainWindowGLViewWidget().AddTopLevelSceneNodeGeometryCylinder(    1, 1, true ); }
void  QSimToolBarGeometry::DrawSphereSlot()          { myMainWindow->GetQSimMainWindowGLViewWidget().AddTopLevelSceneNodeGeometrySphere(1); }
void  QSimToolBarGeometry::DrawRectangularBoxSlot()  { myMainWindow->GetQSimMainWindowGLViewWidget().AddTopLevelSceneNodeGeometryRectangularBox( 2, 1, 1 ); }
void  QSimToolBarGeometry::DrawLowerLimbModelSlot()  { myMainWindow->GetQSimMainWindowGLViewWidget().AddTopLevelSceneNodeGeometryTeapot(); }
void  QSimToolBarGeometry::DrawTorusSlot()           { myMainWindow->GetQSimMainWindowGLViewWidget().RemoveAllSceneNodes(); }


//------------------------------------------------------------------------------
}  // End of namespace QSim


