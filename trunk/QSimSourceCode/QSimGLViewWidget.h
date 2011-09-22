//-----------------------------------------------------------------------------
// File:     QSimGLViewWidget.h
// Class:    QSimGLViewWidget
// Parents:  QGLView -> QGLWidget -> QWidget -> (QObject and QPaintDevice)
// Purpose:  Main Qt widget for OpenQL with 3D camera viewing.
// Notes:    3D camera views are modified by keyboard and mouse control.
//           Left-mouse-button drag rotates the camera's position around the viewed object. 
//           Shift-key and left-mouse-button pans the view in a plane without rotating the viewed object.
//           Control-key and left-mouse-button drag up/down will zoom in and out.
//           Mouse wheel (if one is available) will also zoom the view in and out.
//           Keyboard arrow keys left, right, up, and down keys shift the camera's position around the viewed object.
//           Shift and Control modify keys the same way they modify the left mouse button above. 
//           Keyboard Home-key causes the camera position to be reset to its original position.
//           QGLView also supports stereo viewing (see documentation) but is off by default.
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
#ifndef  QSIMGLVIEWWIDGET_H__ 
#define  QSIMGLVIEWWIDGET_H__
#include <QtCore>
#include <QtGui>
#include <QtOpenGL>
#include "qglview.h"
#include "qglscenenode.h"
#include "qglbuilder.h"
#include "CppStandardHeaders.h"
#include "QSimGenericFunctions.h"
#include "QSimSceneNode.h"

//------------------------------------------------------------------------------
namespace QSim {

// Forward declarations
class QSimMainWindow;

//------------------------------------------------------------------------------
class QSimGLViewWidget : public QGLView
{
   Q_OBJECT

public:
   QSimGLViewWidget( QWidget *parent = NULL );
  ~QSimGLViewWidget() {;}

   // Add various geometry objects to top-level myMostParentSceneNode.
   QSimSceneNode*  AddTopLevelSceneNodeGeometryCone(     qreal coneTopDiameter, qreal coneBottomDiameter, qreal coneHeight, const bool solidTopAndBottomCaps )  { return this->AddSceneNodeGeometryCone( myMostParentSceneNode, true, coneTopDiameter, coneBottomDiameter, coneHeight, solidTopAndBottomCaps, solidTopAndBottomCaps ); }
   QSimSceneNode*  AddTopLevelSceneNodeGeometryCylinder( qreal cylinderDiameter, qreal cylinderHeight, const bool solidTopAndBottomCaps )                       { return this->AddSceneNodeGeometryCylinder( myMostParentSceneNode, true, cylinderDiameter, cylinderHeight, solidTopAndBottomCaps, solidTopAndBottomCaps ); }
   QSimSceneNode*  AddTopLevelSceneNodeGeometryRectangularBox( qreal boxWidth, qreal boxHeight, qreal boxDepth )                                                { return this->AddSceneNodeGeometryRectangularBox( myMostParentSceneNode, true, boxWidth, boxHeight, boxDepth ); }
   QSimSceneNode*  AddTopLevelSceneNodeGeometrySphere( qreal sphereDiameter, int smoothnessFactorDefaultIs5 = 5 )                                               { return this->AddSceneNodeGeometrySphere( myMostParentSceneNode, true, sphereDiameter, smoothnessFactorDefaultIs5 ); }
   QSimSceneNode*  AddTopLevelSceneNodeGeometryEllipsoid( qreal xDiameter, qreal yDiameter, qreal zDiameter, unsigned int smoothnessFactorDefaultIs5 = 5 )      { return this->AddSceneNodeGeometryEllipsoid( myMostParentSceneNode, true, xDiameter, yDiameter, zDiameter, smoothnessFactorDefaultIs5 ); }
   QSimSceneNode*  AddTopLevelSceneNodeGeometryTeapot( )                                                                                                        { return this->AddSceneNodeGeometryTeapot( myMostParentSceneNode, true ); }

   // When user re-selects one or more objects, sometimes all others must be deselected.
   void  DeselectAllPaintedObjectsInQSimGLViewWidget();

   // Remove all the nodes that were added directly or indirectly to myMostParentSceneNode.
   void  RemoveAllSceneNodes( void );

   // User may select one or more objects for deletion.
   void  RemoveSelectedSceneNodesFromQSimGLViewWidget();

   // Associate this QSimGLViewWidget with the widget it contains.
   void             SetQSimMainWindowThatHoldsQSimGLViewWidget( QSimMainWindow* windowThatHoldsThis )  { myQSimMainWindowThatHoldsThisQSimGLViewWidget = windowThatHoldsThis; }
   QSimMainWindow*  GetQSimMainWindowThatHoldsQSimGLViewWidget()   { return myQSimMainWindowThatHoldsThisQSimGLViewWidget; }
   void             WriteMessageToMainWindowStatusBarFromGLViewWidget( const QString& message, const uint lengthOfTimeInMillisecondsOr0ForIndefinitely );

protected:
   // Override parent class QGLView virtual functions to perform typical OpenGL tasks.
   // initializeGL: Sets up the OpenGL rendering context, defines display lists, etc. Gets called once before the first time resizeGL() or paintGL() is called.
   // paintGL:      Renders the OpenGL scene.  Gets called whenever the widget needs to be updated.
   // resizeGL:     Sets up the OpenGL viewport, projection, etc. Gets called whenever the widget has been resized (or shown for the first time).  resizeGL is implemented in QSimGLView class.
   virtual void  initializeGL( QGLPainter *painter ) { if( painter ) { painter->setStandardEffect( QGL::LitMaterial );   this->InitializeAllDrawObjectsInQSimGLViewWidget(*painter);} }
   virtual void  paintGL( QGLPainter *painter )      { if( painter ) this->DrawAllObjectsInQSimGLViewWidget(*painter); }
   void  resizeGL( int width, int height )           { this->QGLView::resizeGL( width, height ); }

   // Override parent class QGLWidget virtual functions to detect mouse or key-pressed events.
   // virtual void  mousePressEvent( QMouseEvent* event )  { myLastPos = event->pos(); }
   // virtual void  mouseMoveEvent(  QMouseEvent* event );
   virtual void  keyPressEvent( QKeyEvent* event );

private:
   // Add various geometry objects  to this widget.
   QSimSceneNode*  AddSceneNodeGeometryFromBuilder( QGLSceneNode& parentSceneNode, QGLBuilder& builder, const char* objectNameOrNull );
   QSimSceneNode*  AddSceneNodeGeometryCone(            QGLSceneNode& parentSceneNode, const bool shouldUpdateGL, qreal coneTopDiameter, qreal coneBottomDiameter, qreal coneHeight, const bool solidTopCap, const bool solidBottomCap );
   QSimSceneNode*  AddSceneNodeGeometryCylinder(        QGLSceneNode& parentSceneNode, const bool shouldUpdateGL, qreal cylinderDiameter, qreal cylinderHeight, const bool solidTopCap, const bool solidBottomCap )   { return this->AddSceneNodeGeometryCone( parentSceneNode, shouldUpdateGL, cylinderDiameter, cylinderDiameter, cylinderHeight, solidTopCap, solidBottomCap ); }
   QSimSceneNode*  AddSceneNodeGeometryExtrudedPolygon( QGLSceneNode& parentSceneNode, const bool shouldUpdateGL );
   QSimSceneNode*  AddSceneNodeGeometryRectangularBox(  QGLSceneNode& parentSceneNode, const bool shouldUpdateGL, qreal boxWidth, qreal boxHeight, qreal boxDepth );
   QSimSceneNode*  AddSceneNodeGeometrySphere(          QGLSceneNode& parentSceneNode, const bool shouldUpdateGL, qreal sphereDiameter, int smoothnessFactorDefaultIs5 = 5 );
   QSimSceneNode*  AddSceneNodeGeometryEllipsoid(       QGLSceneNode& parentSceneNode, const bool shouldUpdateGL, qreal xDiameter, qreal yDiameter, qreal zDiameter, unsigned int smoothnessFactorDefaultIs5 = 5 );
   QSimSceneNode*  AddSceneNodeGeometryTeapot(          QGLSceneNode& parentSceneNode, const bool shouldUpdateGL );
   QSimSceneNode*  AddSceneNodeGeometryTriangle(        QGLSceneNode& parentSceneNode, const bool shouldUpdateGL, const QVector3D& vertexA, const QVector3D& vectexB, const QVector3D& vertexC );
   QSimSceneNode*  AddSceneNodeGeometryTetrahedron(     QGLSceneNode& parentSceneNode, const bool shouldUpdateGL, const QVector3D& vertexA, const QVector3D& vertexB, const QVector3D& vertexC, const QVector3D& vertexD );

   // For this widget, need one sceneNode from which all other sceneNodes descend.
   // Note: The QGLSceneNode class only inherits from QObject.
   QGLSceneNode  myMostParentSceneNode;

   // List of all on-screen objects that need to be painted.
   QList<QSimSceneNode*>  myListOfAllObjectsThatNeedToBePainted;
   void  AddQSimSceneNodeToListOfObjectsThatNeedToBePainted( QSimSceneNode* qSimSceneObject )        { myListOfAllObjectsThatNeedToBePainted.append( qSimSceneObject ); }
   void  RemoveQSimSceneNodeToListOfObjectsThatNeedToBePainted( QSimSceneNode* qSimSceneObject )     { myListOfAllObjectsThatNeedToBePainted.removeAll( qSimSceneObject ); }
   void  InitializeAllDrawObjectsInQSimGLViewWidget( QGLPainter& painter )                           {;} 
   void  DrawAllObjectsInQSimGLViewWidget( QGLPainter& painter )                                     { for( QList<QSimSceneNode*>::iterator it = myListOfAllObjectsThatNeedToBePainted.begin();  it != myListOfAllObjectsThatNeedToBePainted.end();  ++it )  { QSimSceneNode* obj = *it;  if(obj) obj->DrawOpenGLForQSimSceneNode( painter ); } }

   // Associate this QSimGLViewWidget with the widget it contains.
   QSimMainWindow*  myQSimMainWindowThatHoldsThisQSimGLViewWidget;

   // Signals that connect to other signals or slots (no need to designate signals as private/protected/public).
signals:
   void SignalToUpdateGL();
};


//------------------------------------------------------------------------------
}  // End of namespace QSim
//--------------------------------------------------------------------------
#endif  // QSIMGLVIEWWIDGET_H__
//--------------------------------------------------------------------------
