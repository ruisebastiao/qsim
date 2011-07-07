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
#include "qglcylinder.h"
#include "qglsphere.h"
#include "qglteapot.h"
#include "qglpicknode.h"
#include "qglcube.h"
// #include "qvector3darray.h"


//------------------------------------------------------------------------------
QSimGLViewWidget::QSimGLViewWidget( QWidget *parent ) : QGLView(parent)
{
   // Initialize class data.
   myNextUniqueID = 0;

   // Enable object picking (which is disabled by default).
   this->setOption( QGLView::ObjectPicking, true );

   // For debugging object picking, render objects with their pick colors instead of normal colors and materials (disabled by default).
   // this->setOption( QGLView::ShowPicking, true );

   // Ensure that a change to each of the objects contained in this to update the view.
   QObject::connect( &myMostParentSceneNode, SIGNAL(changed()), this, SLOT(updateGL()) );

   // For this widget, need one sceneNode from which all other sceneNodes descend.
   // myMostParentSceneNode.setParent( this );  // Unnecessary and perhaps wrong to do this.

   // Construct a triangle.
   QVector3D vertexA( 0,  0, 0);
   QVector3D vertexB( 2,  2, 0);
   QVector3D vertexC(-2,  2, 0);
   QGLSceneNode *triangleSceneNode = this->AddSceneNodeGeometryTriangle( myMostParentSceneNode, vertexA, vertexB, vertexC );
   triangleSceneNode->setPosition( QVector3D(0.0f, 1.0f, -2.0f) );

   // Construct a tetrahedron.
   QVector3D vertexD( 0,  2, -2 );
   QGLSceneNode *tetrahedronSceneNode = this->AddSceneNodeGeometryTetrahedron( myMostParentSceneNode, vertexA, vertexB, vertexC, vertexD );
   tetrahedronSceneNode->setPosition( QVector3D(5.0f, 0.0f, 1.0f) );

   // Sequential rotations to orient tetrahedron.  Otherwise use the following QMatrix4x4 methods.
   // void  rotate ( qreal angle, const QVector3D & vector )
   // void  rotate ( const QQuaternion & quaternion )
   // void  rotate ( qreal angle, qreal x, qreal y, qreal z = 0.0f )
   QMatrix4x4 mat44;
   QQuaternion q1 = QQuaternion::fromAxisAndAngle( 1.0f, 0.0f, 0.0f, 270.0f );
   QQuaternion q2 = QQuaternion::fromAxisAndAngle( 0.0f, 1.0f, 0.0f, 100.0f );
   mat44.rotate( q2 * q1 );
   tetrahedronSceneNode->setLocalTransform( mat44 );

   // Add the classic teapot to the scene.
   QGLSceneNode*  teapotSceneNode = this->AddSceneNodeGeometryTeapot( myMostParentSceneNode );
   teapotSceneNode->setPosition( QVector3D( 2.0f, 0.0f, 2.0f) );

   // Purely cosmetic effects (skip this if you like all white).
   QGLMaterial *mat = new QGLMaterial;
   mat->setDiffuseColor( QColor(255, 255, 0)   );    // Direct light is this color (Each RGB value is from 0 to 255)
   mat->setAmbientColor( QColor(0,   0,   255) );    // Shadows are this color     (Each RGB value is from 0 to 255)
   myMostParentSceneNode.setMaterial( mat );

   // Can move this scene node back so entire scene is initially visible.
   myMostParentSceneNode.setPosition( QVector3D(0.0f, 0.0f, 0.0f) );

   // Or move and aim the camera for better viewing (z direction is out of screen).
   QGLCamera *cameraForThisWidget = this->camera();
   cameraForThisWidget->setEye( QVector3D(5.0f, 0.0f, 25.0f) );
   cameraForThisWidget->rotateEye( cameraForThisWidget->pan(-5) );

   // this->setFocusPolicy( Qt::StrongFocus ) enables keyboard focus to process keyboard events.
   // Qt::TabFocus    if the widget accepts focus by tabbing.
   // Qt::ClickFocus  if the widget accepts focus by clicking.
   // Qt::StrongFocus if the widget accepts focus by either Tab or Click.
   // Qt::NoFocus     if the widget does not accept focus at all (the default).
   this->setFocusPolicy( Qt::StrongFocus );
}


//------------------------------------------------------------------------------
QGLSceneNode*  QSimGLViewWidget::AddSceneNodeGeometryCone( QGLSceneNode &parentSceneNode, qreal coneTopDiameter, qreal coneBottomDiameter, qreal coneHeight, const bool solidTopCap, const bool solidBottomCap )
{
   // Ensure dimensions are sensible on entry (set negative or zero arguments to 1).
   if( coneTopDiameter    <= 0 ) coneTopDiameter    = 1;
   if( coneBottomDiameter <= 0 ) coneBottomDiameter = 1;
   if( coneHeight         <= 0 ) coneHeight         = 1;

   // Construct a QGLBuilder on the stack.  When adding geometry, QGLBuilder automatically creates lighting normals.
   QGLBuilder builder;

   // Create the geometry for the cylinder/cone and add it to the builder.
   const int numberOfSlicesAlsoCalledFacetsThatRunLengthOfCylinder = 36;
   const int numberOfLayersThatDivideSidesOfCylinder = 3;
   builder << QGLCylinder( coneTopDiameter, coneBottomDiameter, coneHeight, numberOfSlicesAlsoCalledFacetsThatRunLengthOfCylinder, numberOfLayersThatDivideSidesOfCylinder, solidTopCap, solidBottomCap );

   // Finish the building of this geometry, optimize it for rendering, and return a pointer to the detached top-level scene node (root node).
   // Since the sceneNode is detached from the builder object, the builder may be deleted or go out of scope while sceneNode lives on.
   // finalizedSceneNode must be called once (and only once) after building a scene.
   QGLSceneNode *sceneNode = builder.finalizedSceneNode();

   // The calling method takes ownership of the returned sceneNode and should either explicitly call delete sceneNode when it is not longer needed,
   // or documentation claims if you call sceneNode->setParent(),  sceneNode will be implicitly cleaned up by Qt.
   // Note: parentSceneNode.addNode( sceneNode) will call sceneNode->setParent( &parentSceneNode ) if sceneNode does not have a parent.
   parentSceneNode.addNode( sceneNode );
   const bool isCylinder = coneTopDiameter == coneBottomDiameter;
   sceneNode->setObjectName( isCylinder ? "Cylinder" : "Cone" );

   // Move it for no particular reason.
   sceneNode->setPosition( QVector3D( isCylinder ? -1.0f : -2.5f, 0.0f, 0.0f) );

   // Update so geometry is visible before returning.
   this->QGLView::updateGL();
   return sceneNode;
}



//------------------------------------------------------------------------------
QGLSceneNode*  QSimGLViewWidget::AddSceneNodeGeometryRectangularBox( QGLSceneNode &parentSceneNode, qreal boxWidth, qreal boxHeight, qreal boxDepth )
{
#if 0
   QGLBuilder builderCube;
   builderCube << QGLCube(1.0f);
   QGLSceneNode *cubeSceneNode = builderCube.finalizedSceneNode();
#endif

   // Ensure dimensions are sensible on entry (set negative or zero arguments to 1).
   if( boxWidth  <= 0 ) boxWidth  = 1;
   if( boxHeight <= 0 ) boxHeight = 1;
   if( boxDepth  <= 0 ) boxDepth  = 1;

   // Construct a QGLBuilder on the stack.  When adding geometry, QGLBuilder automatically creates lighting normals.
   QGLBuilder builder;

   // Create the vertices for each corner of the bottom of the box.
   const QVector3D vertexA( 0,        0,        0 );     // Left,  bottom, back  corner of box.
   const QVector3D vertexB( boxWidth, 0,        0 );     // Right, bottom, back  corner of box.
   const QVector3D vertexC( boxWidth, 0, boxDepth );     // Right, bottom, front corner of box.
   const QVector3D vertexD( 0,        0, boxDepth );     // Left,  bottom, front corner of box.

   // Create each triangle on the bottom (with downward-facing outward normals) and add it to the builder.
   QGeometryData bottomOfBox;   bottomOfBox.appendVertex( vertexA, vertexB, vertexC, vertexD );
   QGeometryData topOfBox = bottomOfBox.translated( QVector3D(0,boxHeight,0) );

   // Three-step process to extrude the polygons into a box
   builder.addQuadsInterleaved( bottomOfBox, topOfBox );
   builder.addTriangulatedFace( bottomOfBox );
   builder.addTriangulatedFace( topOfBox.reversed() );

   // Finish the building of this geometry, optimize it for rendering, and return a pointer to the detached top-level scene node (root node).
   // Since the sceneNode is detached from the builder object, the builder may be deleted or go out of scope while sceneNode lives on.
   // finalizedSceneNode must be called once (and only once) after building a scene.
   QGLSceneNode *sceneNode = builder.finalizedSceneNode();

   // The calling method takes ownership of the returned sceneNode and should either explicitly call delete sceneNode when it is not longer needed,
   // or documentation claims if you call sceneNode->setParent(),  sceneNode will be implicitly cleaned up by Qt.
   // Note: parentSceneNode.addNode( sceneNode) will call sceneNode->setParent( &parentSceneNode ) if sceneNode does not have a parent.
   parentSceneNode.addNode( sceneNode );
   sceneNode->setObjectName( "Rectangular box" );

#if 0
   // Purely cosmetic effects (skip this if you like all white).
   // Also, should probably using a palette here.
   QGLMaterial *china = new QGLMaterial(this);
   china->setAmbientColor(  QColor(192, 150, 128) );
   china->setSpecularColor( QColor(60, 60, 60) );
   china->setShininess( 128 );
   sceneNode->setMaterial(china);
   sceneNode->setEffect( QGL::LitMaterial );
#endif

   // Move the cube a little for no particular reason.
   sceneNode->setPosition( QVector3D(-2.5f, 2.0f, 1.0f) );

   // Update so geometry is visible before returning.
   this->QGLView::updateGL();
   return sceneNode;
}


//------------------------------------------------------------------------------
QGLSceneNode*  QSimGLViewWidget::AddSceneNodeGeometrySphere( QGLSceneNode &parentSceneNode, qreal sphereDiameter, int smoothnessFactorDefaultIs5 )
{
   // Ensure dimensions are sensible on entry (set negative or zero argument to 1).
   if( sphereDiameter <= 0 ) sphereDiameter = 1;

   // Construct a QGLBuilder on the stack.  When adding geometry, QGLBuilder automatically creates lighting normals.
   QGLBuilder builder;

   // Create the geometry for a sphere and add it to the builder.
   // smoothnessFactorDefaultIs5 must be between 1 (rough but small) and 10 (smooth but large).
   // The default of 5 looks smooth to the eye and has a reasonably small number of triangles.
   // Here is the cost in number of triangles in ascending order from 1 to 10.
   // 1 64    2 128     3 256     4 512      5 1024     6 2048     7 4096    8 8192     9 16384     10 32768
   if(      smoothnessFactorDefaultIs5 < 1  )  smoothnessFactorDefaultIs5 = 1;
   else if( smoothnessFactorDefaultIs5 > 10 )  smoothnessFactorDefaultIs5 = 10;
   builder << QGLSphere( sphereDiameter, smoothnessFactorDefaultIs5 );

   // Finish the building of this geometry, optimize it for rendering, and return a pointer to the detached top-level scene node (root node).
   // Since the sceneNode is detached from the builder object, the builder may be deleted or go out of scope while sceneNode lives on.
   // finalizedSceneNode must be called once (and only once) after building a scene.
   QGLSceneNode *sceneNode = builder.finalizedSceneNode();

   // The calling method takes ownership of the returned sceneNode and should either explicitly call delete sceneNode when it is not longer needed,
   // or documentation claims if you call sceneNode->setParent(),  sceneNode will be implicitly cleaned up by Qt.
   // Note: parentSceneNode.addNode( sceneNode) will call sceneNode->setParent( &parentSceneNode ) if sceneNode does not have a parent.
   parentSceneNode.addNode( sceneNode );
   sceneNode->setObjectName( "Sphere" );

   // Move this a little bit.
   sceneNode->setPosition( QVector3D(-4.0f, 2.0f, 0.0f) );

   // Update so geometry is visible before returning.
   this->QGLView::updateGL();
   return sceneNode;
}


//------------------------------------------------------------------------------
QGLSceneNode*  QSimGLViewWidget::AddSceneNodeGeometryTeapot( QGLSceneNode &parentSceneNode )
{
   // Construct a QGLBuilder on the stack.  When adding geometry, QGLBuilder automatically creates lighting normals.
   QGLBuilder builder;

   // Create the geometry for a teapot and add it to the builder.
   builder << QGLTeapot();

   // Finish the building of this geometry, optimize it for rendering, and return a pointer to the detached top-level scene node (root node).
   // Since the sceneNode is detached from the builder object, the builder may be deleted or go out of scope while sceneNode lives on.
   // finalizedSceneNode must be called once (and only once) after building a scene.
   QGLSceneNode *sceneNode = builder.finalizedSceneNode();
   sceneNode->setObjectName( "Teapot" );

   // The calling method takes ownership of the returned sceneNode and should either explicitly call delete sceneNode when it is not longer needed,
   // or documentation claims if you call sceneNode->setParent(),  sceneNode will be implicitly cleaned up by Qt.
   // Note: parentSceneNode.addNode( sceneNode) will call sceneNode->setParent( &parentSceneNode ) if sceneNode does not have a parent.
   parentSceneNode.addNode( sceneNode );

   // Update so geometry is visible before returning.
   this->QGLView::updateGL();
   return sceneNode;
}


//------------------------------------------------------------------------------
QGLSceneNode*  QSimGLViewWidget::AddSceneNodeGeometryTriangle( QGLSceneNode &parentSceneNode, const QVector3D &vertexA, const QVector3D &vertexB, const QVector3D &vertexC )
{
   // Construct a QGLBuilder on the stack.  When adding geometry, QGLBuilder automatically creates lighting normals.
   QGLBuilder builder;

   // Create the geometry for a triangle and add it to the builder.
   QGeometryData triangleABC;   triangleABC.appendVertex( vertexA, vertexB, vertexC );   builder.addTriangles( triangleABC );

   // Finish the building of this geometry, optimize it for rendering, and return a pointer to the detached top-level scene node (root node).
   // Since the sceneNode is detached from the builder object, the builder may be deleted or go out of scope while sceneNode lives on.
   // finalizedSceneNode must be called once (and only once) after building a scene.
   QGLSceneNode *sceneNode = builder.finalizedSceneNode();
   sceneNode->setObjectName( "Triangle" );

   // The calling method takes ownership of the returned sceneNode and should either explicitly call delete sceneNode when it is not longer needed,
   // or documentation claims if you call sceneNode->setParent(),  sceneNode will be implicitly cleaned up by Qt.
   // Note: parentSceneNode.addNode( sceneNode) will call sceneNode->setParent( &parentSceneNode ) if sceneNode does not have a parent.
   parentSceneNode.addNode( sceneNode );

   // Register this object for object picking.
   this->registerObject( this->GetNextUniqueID(), sceneNode );

   // If there is
   // QObject::connect( sceneNode, SIGNAL(hoverChanged()), this, SIGNAL(changed()) );
   // QObject::connect( sceneNode, SIGNAL(clicked()),      this, SLOT(triangleClicked()));

   // Update so geometry is visible before returning.
   this->QGLView::updateGL();
   return sceneNode;
}


//------------------------------------------------------------------------------
QGLSceneNode*  QSimGLViewWidget::AddSceneNodeGeometryTetrahedron( QGLSceneNode &parentSceneNode, const QVector3D &vertexA, const QVector3D &vertexB, const QVector3D &vertexC, const QVector3D &vertexD )
{
   // Construct a QGLBuilder on the stack.  When adding geometry, QGLBuilder automatically creates lighting normals.
   QGLBuilder builder;

   // Create the geometry for each triangle and add it to the builder.
   QGeometryData triangle0;   triangle0.appendVertex( vertexA, vertexB, vertexC );    builder.addTriangles( triangle0 );
   QGeometryData triangle1;   triangle1.appendVertex( vertexA, vertexD, vertexB );    builder.addTriangles( triangle1 );
   QGeometryData triangle2;   triangle2.appendVertex( vertexA, vertexC, vertexD );    builder.addTriangles( triangle2 );
   QGeometryData triangle3;   triangle3.appendVertex( vertexB, vertexD, vertexC );    builder.addTriangles( triangle3 );

   // Finish the building of this geometry, optimize it for rendering, and return a pointer to the detached top-level scene node (root node).
   // Since the sceneNode is detached from the builder object, the builder may be deleted or go out of scope while sceneNode lives on.
   // finalizedSceneNode must be called once (and only once) after building a scene.
   QGLSceneNode *sceneNode = builder.finalizedSceneNode();
   sceneNode->setObjectName( "Tetrahedron" );

   // The calling method takes ownership of the returned sceneNode and should either explicitly call delete sceneNode when it is not longer needed,
   // or documentation claims if you call sceneNode->setParent(),  sceneNode will be implicitly cleaned up by Qt.
   // Note: parentSceneNode.addNode( sceneNode) will call sceneNode->setParent( &parentSceneNode ) if sceneNode does not have a parent.
   parentSceneNode.addNode( sceneNode );

   // Update so geometry is visible before returning.
   this->QGLView::updateGL();
   return sceneNode;
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
      this->updateGL();
   }
}


//------------------------------------------------------------------------------
void  QSimGLViewWidget::RemoveAllSceneNodes( void )
{
   QMessageBox::information( this, tr("Debug message"), tr("Draw Torus is changed to remove all nodes"), QMessageBox::Ok, QMessageBox::NoButton );

   // The next two calls remove all the children and disconnects them from their parent, but does not delete/free memory on them.
   QList<QGLSceneNode*> listOfAllChildrenNodesRecursive = myMostParentSceneNode.allChildren();
   myMostParentSceneNode.removeNodes( listOfAllChildrenNodesRecursive );

   // For some reason, each call to addNode adds two nodes to allChildren() list but only one to children.
   // For some reason, must delete the last nodes in the list (before the first) or else it will cause a segmentation fault.
   while( !listOfAllChildrenNodesRecursive.isEmpty() )
   {
      QGLSceneNode* sceneNodei = listOfAllChildrenNodesRecursive.takeLast();
//    this->deregisterObject( sceneNodei );
      delete sceneNodei;
   }
}


#if 0
//------------------------------------------------------------------------------
void  QSimGLViewWidget::RegisterPickableNodes()
{
   myMostParentSceneNode.generatePickNodes();
   QList<QGLPickNode*> pickList = myMostParentSceneNode.pickNodes();
   for( QList<QGLPickNode*>::const_iterator it = pickList.constBegin();  it != pickList.constEnd();  ++it )
   {
      QGLPickNode *pn = *it;
      pn->disconnect( this );
      QObject::connect( pn, SIGNAL(clicked()), this, SLOT(goPan()) );
      registerObject( pn->id(), pn );
   }
}
#endif
