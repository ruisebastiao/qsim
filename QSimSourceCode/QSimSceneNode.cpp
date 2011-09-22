//-----------------------------------------------------------------------------
// File:     QSimSceneNode.cpp
// Class:    QSimSceneNode
// Parents:  QObject
// Purpose:  QSimSceneNode and QSimGLViewWidget work together for painting/picking on-screen objects.
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
#include "qglpainter.h"
#include "qglview.h"
#include "QSimSceneNode.h"
#include "QSimGLViewWidget.h"
#include "QSimRigidBodyTabWidget.h"


//------------------------------------------------------------------------------
namespace QSim {


//------------------------------------------------------------------------------
//  Initialize Class static data
unsigned long  QSimSceneNode::myNextUniqueID = 0;


//------------------------------------------------------------------------------
QSimSceneNode::QSimSceneNode( QGLSceneNode &sceneNode, QSimGLViewWidget& glViewWidget, const bool isObjectPickable, const char *objectNameOrNull ) : QObject(&sceneNode), myQGLSceneNode(sceneNode), mySceneNodeQSimGLViewWidget(glViewWidget)
{
   // Immediately set object to not pickable and then set other default properties.
   this->InitializeQSimSceneNode();

   // Name the object or assign the default name "Object".
   this->setObjectName( objectNameOrNull != NULL ? objectNameOrNull : "Object" );

   // This actually determines whether or not the object is pickable.
   this->SetObjectPickable( isObjectPickable );
}


//------------------------------------------------------------------------------
void  QSimSceneNode::DrawOpenGLForQSimSceneNode( QGLPainter& painter )
{
   // If hovering on the object, update the status bar.
   if( this->GetHoverStatus() && this->IsObjectPickable()  )
   {
      QString messageToStatusBar;   this->GetObjectNameAndObjectIdInsideSquareBrackets( messageToStatusBar );
      this->GetSceneNodeQSimGLViewWidget().WriteMessageToMainWindowStatusBarFromGLViewWidget( messageToStatusBar, 0 );
   }

   // Position the model at its designated position, scale, and orientation.
   painter.modelViewMatrix().push();

   // Possibly rotate, translate, or scale.
   if( this->GetRotationAngleInDegrees() != 0.0 ) painter.modelViewMatrix().rotate( this->GetRotationAngleInDegrees(), this->GetRotationVector() );
   if( this->GetPosition() != QVector3D(0,0,0) )  painter.modelViewMatrix().translate( this->GetPosition() );
   if( this->GetScale() != 1.0 )                  painter.modelViewMatrix().scale( this->GetScale() );

   // Apply the material and effect to the painter.
   const QSimMaterialType& material = this->GetMaterialBasedOnHoverStatus();
   const QColor diffuseColor = material.diffuseColor();
   painter.setColor( diffuseColor );
   painter.setFaceMaterial( QGL::AllFaces, &material );

   // Apply the designated (or standard) abstract effect to the painter.
   if( this->GetAbstractEffect() )                            painter.setUserEffect( myAbstractEffect );
   else if( myRigidBodyTabWidget.GetTextureOrNullIfEmpty() )  painter.setStandardEffect( QGL::LitDecalTexture2D );
   else                                                       painter.setStandardEffect( QGL::LitMaterial );

   // Mark the object for object picking purposes.
   const int prevObjectId = painter.objectPickId();
   if( myObjectId != -1 ) painter.setObjectPickId( myObjectId );

   // Draw the geometry.
   myQGLSceneNode.draw( &painter );

   // Turn off the user effect, if present.
   if( this->GetAbstractEffect() || myRigidBodyTabWidget.GetTextureOrNullIfEmpty() )
      painter.setStandardEffect( QGL::LitMaterial );

   // Revert to the previous object identifier.
   painter.setObjectPickId( prevObjectId );

   // Restore the modelview matrix.
   painter.modelViewMatrix().pop();
}


//------------------------------------------------------------------------------
bool  QSimSceneNode::event( QEvent* event )
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
      // Maybe update status bar that no-longer hovering over object.
      if( this->GetHoverStatus() && this->IsObjectPickable()  )
         this->GetSceneNodeQSimGLViewWidget().WriteMessageToMainWindowStatusBarFromGLViewWidget( QString(""), 0 );

      this->SetHoverStatus( false );
      emit mouseHoverChanged();
   }
   return QObject::event( event );
}


//------------------------------------------------------------------------------
void  QSimSceneNode::ObjectWasDoubleClicked()
{
   // Each scene node may be associated with a rigid body.
   myRigidBodyTabWidget.ShowRigidBodyTabWidget( *this );

   this->SetThisObjectWasSelectedAndDeselectOthers();
}


//------------------------------------------------------------------------------
void  QSimSceneNode::SetThisObjectWasSelectedAndDeselectOthers()
{
   this->GetSceneNodeQSimGLViewWidget().DeselectAllPaintedObjectsInQSimGLViewWidget();
   this->SetObjectIsSelected( true );
}


//------------------------------------------------------------------------------
void  QSimSceneNode::SetSceneObjectPickableToFalseDeregisterDisconnect()
{
   // If already registered and connected, deregister this object (must also do this before object is destroyed) and disconnect signals.
   if( this->IsObjectPickable() )
   {
      mySceneNodeQSimGLViewWidget.deregisterObject( this->GetObjectId() );
      this->disconnect();
      myObjectIsPickable = false;
   }
}


//------------------------------------------------------------------------------
void  QSimSceneNode::SetObjectPickable( const bool isObjectPickable )
{
   // If already registered and connected, deregister this object (must also do this before object is destroyed) and disconnect signals.
   this->SetSceneObjectPickableToFalseDeregisterDisconnect();

   // Register this object for object picking and connect signals to listen to mouse/other events.
   if( (myObjectIsPickable = isObjectPickable) == true )
   {
      mySceneNodeQSimGLViewWidget.registerObject( this->GetObjectId(), this );
      QObject::connect( this,  SIGNAL(mouseHoverChanged()),        &mySceneNodeQSimGLViewWidget, SIGNAL(SignalToUpdateGL()) );
      QObject::connect( this,  SIGNAL(mouseButtonClicked()),       this,                         SLOT(ObjectWasSoleSelected())  );
      QObject::connect( this,  SIGNAL(mouseButtonDoubleClicked()), this,                         SLOT(ObjectWasDoubleClicked())  );
   }
}


//------------------------------------------------------------------------------
}  // End of namespace QSim
