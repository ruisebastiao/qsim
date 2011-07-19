//-----------------------------------------------------------------------------
// File:     QSimSceneNode.cpp
// Class:    QSimSceneNode
// Parents:  QObject
// Purpose:  QSimSceneNode and QSimGLViewWidget work together for painting/picking on-screen objects.
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
#include "qglpainter.h"
#include "qglview.h"
#include "QSimSceneNode.h"
#include "QSimGLViewWidget.h"


//------------------------------------------------------------------------------
namespace QSim {


//------------------------------------------------------------------------------
//  Initialize Class static data
unsigned long  QSimSceneNode::myNextUniqueID = 0;


//------------------------------------------------------------------------------
QSimSceneNode::QSimSceneNode( QGLSceneNode &sceneNode, QSimGLViewWidget& viewWidgetForPickableObject ) : QObject(&sceneNode), myQGLSceneNode(sceneNode)
{
   this->InitializeQSimSceneNode();
   this->SetSceneObjectPickable( &viewWidgetForPickableObject );
}


//------------------------------------------------------------------------------
void  QSimSceneNode::DrawOpenGLForQSimSceneNode( QGLPainter& painter )
{
   // Position the model at its designated position, scale, and orientation.
   painter.modelViewMatrix().push();

   // Possibly rotate, translate, or scale.
   if( this->GetRotationAngleInDegrees() != 0.0 ) painter.modelViewMatrix().rotate( this->GetRotationAngleInDegrees(), this->GetRotationVector() );
   if( this->GetPosition() != QVector3D(0,0,0) )  painter.modelViewMatrix().translate( this->GetPosition() );
   if( this->GetScale() != 1.0 )                  painter.modelViewMatrix().scale( this->GetScale() );

   // Apply the material and effect to the painter.
   QGLMaterial *material = this->GetHoverStatus() ? myMaterialHighlight : myMaterialStandard;
   const QColor diffuseColor = material ? material->diffuseColor() : QColor(0.8, 0.8, 0.8, 1.0);
   painter.setColor( diffuseColor );
   painter.setFaceMaterial( QGL::AllFaces, material );

   // Apply the designated (or standard) abstract effect to the painter.
   if( myAbstractEffect )  painter.setUserEffect( myAbstractEffect );
   else                    painter.setStandardEffect( QGL::LitMaterial );

   // Mark the object for object picking purposes.
   const int prevObjectId = painter.objectPickId();
   if( myObjectId != -1 ) painter.setObjectPickId( myObjectId );

   // Draw the geometry.
   myQGLSceneNode.draw( &painter );

   // Turn off the user effect, if present.
   if( myAbstractEffect ) painter.setStandardEffect( QGL::LitMaterial );

   // Revert to the previous object identifier.
   painter.setObjectPickId( prevObjectId );

   // Restore the modelview matrix.
   painter.modelViewMatrix().pop();
}


//------------------------------------------------------------------------------
bool  QSimSceneNode::event( QEvent *event )
{
   // Convert the raw event into a signal representing the user's action.
   if( event->type() == QEvent::MouseButtonPress )
   {
      QMouseEvent *mouseEvent = static_cast<QMouseEvent*>( event );
      if( mouseEvent->button() == Qt::LeftButton )  emit mouseButtonPressed();
   }
   else if( event->type() == QEvent::MouseButtonRelease )
   {
      QMouseEvent *mouseEvent = static_cast<QMouseEvent*>( event );
      if( mouseEvent->button() == Qt::LeftButton )
      {
         emit mouseButtonReleased();
         // Determine if click is inside or outside an object.
         // mouseEvent->x() is positive inside an object and negative outside.
         if( mouseEvent->x() >= 0 )  emit mouseButtonClicked();
      }
   }
   else if( event->type() == QEvent::MouseButtonDblClick )
   {
      emit mouseButtonDoubleClicked();
   }
   else if( event->type() == QEvent::Enter )
   {
      this->SetHoverStatus( true );
      emit mouseHoverChanged();
   }
   else if( event->type() == QEvent::Leave )
   {
      this->SetHoverStatus( false );
      emit mouseHoverChanged();
   }
   return QObject::event( event );
}


//------------------------------------------------------------------------------
void  QSimSceneNode::ObjectWasSelected()
{
   const QString objectName = this->objectName();
   const unsigned long objectId = this->GetObjectId();
   QString message;
   QTextStream( &message ) << "Object clicked.    Name = " << objectName << ".    ID = " << objectId;
   QMessageBox::information( NULL, tr("Debug message"), message, QMessageBox::Ok, QMessageBox::NoButton );
}


//------------------------------------------------------------------------------
void  QSimSceneNode::SetSceneObjectPickable( QSimGLViewWidget *viewWidgetIfPickableOrNullIfNotPickable )
{
   // If already registered and connected, deregister this object (must also do this before object is destroyed) and disconnect signals.
   if( myViewWidgetIfPickableOrNullIfNotPickable != NULL )
   {
      myViewWidgetIfPickableOrNullIfNotPickable->deregisterObject( this->GetObjectId() );
      this->disconnect();
      myViewWidgetIfPickableOrNullIfNotPickable = NULL;
   }

   // Possibly register this object for object picking and connect signals to listen to mouse/other events.
   if( viewWidgetIfPickableOrNullIfNotPickable != NULL )
   {
      myViewWidgetIfPickableOrNullIfNotPickable = viewWidgetIfPickableOrNullIfNotPickable;
      myViewWidgetIfPickableOrNullIfNotPickable->registerObject( this->GetObjectId(), &(this->GetQGLSceneNode()) );
      QObject::connect( this,  SIGNAL(mouseHoverChanged()),  myViewWidgetIfPickableOrNullIfNotPickable, SIGNAL(SignalToUpdateGL()) );
      QObject::connect( this,  SIGNAL(mouseButtonClicked()), this, SLOT(ObjectWasSelected())  );
   }
}


//------------------------------------------------------------------------------
}  // End of namespace QSim
