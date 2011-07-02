//-----------------------------------------------------------------------------
// File:     QSimGLViewWidget.cpp
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
#include "QSimGLViewWidget.h"
#include "qglcamera.h"
#include "qglcube.h"
#include "qglsphere.h"
#include "qglteapot.h"
#include "qglpicknode.h"


//------------------------------------------------------------------------------
QSimGLViewWidget::QSimGLViewWidget( QWidget *parent ) : QGLView(parent)
{
   // Create the single node from which all other nodes descend.
   myMostParentSceneNode.setParent( this );

   // Construct the geometry of a triangle.
   QVector3D a( 2,  2, 0);
   QVector3D b(-2,  2, 0);
   QVector3D c( 0, -2, 0);
   QGeometryData triangleABC;
   triangleABC.appendVertex( a, b, c );

   // Construct a triangle builder on the stack and create a triangleSceneNode.
   // When adding geometry, QGLBuilder automatically creates lighting normals.
   // Lastly, add the triangleSceneNode to myMostParentSceneNode.
   QGLBuilder builderTriangle;
   builderTriangle << triangleABC;
   QGLSceneNode *triangleSceneNode = builderTriangle.finalizedSceneNode();
   myMostParentSceneNode.addNode( triangleSceneNode );

   // Construct the geometry of a tetrahedron.
   QVector3D d( 0,  0, -2 );
   QGeometryData triangleABD;   triangleABD.appendVertex( a, b, d );
   QGeometryData triangleACD;   triangleACD.appendVertex( a, c, d );
   QGeometryData triangleBCD;   triangleBCD.appendVertex( b, c, d );
   QGLBuilder builderTetrahedron;
   builderTetrahedron.addTriangles( triangleABC );
   builderTetrahedron.addTriangles( triangleABD );
   builderTetrahedron.addTriangles( triangleACD );
   builderTetrahedron.addTriangles( triangleBCD );
   QGLSceneNode *tetrahedronSceneNode = builderTetrahedron.finalizedSceneNode();

   // Sequential rotations to orient tetrahedron.  Otherwise use the following QMatrix4x4 methods.
   // void  rotate ( qreal angle, const QVector3D & vector )
   // void  rotate ( const QQuaternion & quaternion )
   // void  rotate ( qreal angle, qreal x, qreal y, qreal z = 0.0f )
   QMatrix4x4 mat44;
   QQuaternion q1 = QQuaternion::fromAxisAndAngle( 1.0f, 0.0f, 0.0f, 270.0f );
   QQuaternion q2 = QQuaternion::fromAxisAndAngle( 0.0f, 1.0f, 0.0f, 100.0f );
   mat44.rotate( q2 * q1 );
   tetrahedronSceneNode->setLocalTransform( mat44 );
   tetrahedronSceneNode->setPosition( QVector3D(5.0f, 0.0f, 1.0f) );
   myMostParentSceneNode.addNode( tetrahedronSceneNode );

   // Construct a cube on the stack.
   QGLBuilder builderCube;
   builderCube << QGLCube(1.0f);
   QGLSceneNode *cubeSceneNode = builderCube.finalizedSceneNode();

   // Purely cosmetic effects (skip this if you like all white).
   QGLMaterial *china = new QGLMaterial(this);
   china->setAmbientColor( QColor(192, 150, 128) );
   china->setSpecularColor( QColor(60, 60, 60) );
   china->setShininess( 128 );
   cubeSceneNode->setMaterial(china);
   cubeSceneNode->setEffect( QGL::LitMaterial );

   // Move the cube a little before adding it to myMostParentSceneNode.
   cubeSceneNode->setPosition( QVector3D(-1.0f, 0.0f, 1.0f) );
   myMostParentSceneNode.addNode( cubeSceneNode );

   // Construct a sphere on the stack.
   QGLBuilder builderSphere;
   builderSphere << QGLSphere(1.3f);
   QGLSceneNode *sphereSceneNode = builderSphere.finalizedSceneNode();
   sphereSceneNode->setPosition( QVector3D(-3.0f, 0.0f, 1.0f) );
   myMostParentSceneNode.addNode( sphereSceneNode );

   // Add the classic teapot to the scene.
   QGLBuilder builderTeapot;
   builderTeapot << QGLTeapot();
   QGLSceneNode *teapotSceneNode = builderTeapot.finalizedSceneNode();
   teapotSceneNode->setPosition( QVector3D( 2.0f, 0.0f, 2.0f) );
   myMostParentSceneNode.addNode( teapotSceneNode );

   // Purely cosmetic effects (skip this if you like all white).
   QGLMaterial *mat = new QGLMaterial;
   mat->setDiffuseColor( QColor(255, 255, 0)   );    // Direct light is this color (Each RGB value is from 0 to 255)
   mat->setAmbientColor( QColor(0,   0,   255) );    // Shadows are this color     (Each RGB value is from 0 to 255)
   myMostParentSceneNode.setMaterial( mat );

   // Can move this scene node back so entire scene is initially visable.
   myMostParentSceneNode.setPosition( QVector3D(0.0f, 0.0f, 0.0f) );

   // Or move and aim the camera for better viewing.
   QGLCamera *cameraForThisWidget = this->camera();
   cameraForThisWidget->setEye( QVector3D(5.0f, 0.0f, 25.0f) );
   cameraForThisWidget->rotateEye( cameraForThisWidget->pan(-5) );
}


//------------------------------------------------------------------------------
void  QSimGLViewWidget::keyPressEvent( QKeyEvent *event )
{
   // To enable this code, set the following before the user presses any keys:  this->setFocusPolicy( Qt::StrongFocus );
   double multiplier = 1.0;
   switch( event->key() )
   {
      case Qt::Key_Plus:   multiplier = 1.5;   break;
      case Qt::Key_Minus:  multiplier = 0.7;   break;
   }

   // Resize and paint only if non-zero, non-unity multiplier.
   if( multiplier != 1.0 )
   {
      const int widgetWidth  = this->width();
      const int widgetHeight = this->height();
      this->resizeGL( multiplier * widgetWidth, multiplier * widgetHeight );
      this->paintGL( (QGLPainter*)this );
   }
}


#if 0
//------------------------------------------------------------------------------
void  QSimGLViewWidget::RegisterPickableNodes()
{
   myMostParentSceneNode.generatePickNodes();
   QList<QGLPickNode*> pickList = myMostParentSceneNode.pickNodes();
   QList<QGLPickNode*>::const_iterator it = pickList.constBegin();
   for( ; it != pickList.constEnd(); ++it )
   {
      QGLPickNode *pn = *it;
      pn->disconnect( this );
      QObject::connect( pn, SIGNAL(clicked()), this, SLOT(goPan()) );
      registerObject( pn->id(), pn );
   }
}
#endif
