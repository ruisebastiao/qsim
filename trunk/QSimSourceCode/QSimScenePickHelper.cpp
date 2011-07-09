//-----------------------------------------------------------------------------
// File:     QSimScenePickHelper.cpp
// Class:    QSimScenePickHelper
// Parents:  QObject
// Purpose:  The following classes work together to allow for picking on-screen objects.
//           QSimScenePickHelper, QSimScenePickPainter, QSimGLViewWidget.
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
#include "QSimScenePickHelper.h"


//------------------------------------------------------------------------------
namespace QSim {


//------------------------------------------------------------------------------
//  Class static data
unsigned long QSimScenePickHelper::myNextUniqueID = 0;


//------------------------------------------------------------------------------
QSimScenePickHelper::QSimScenePickHelper( QGLSceneNode &sceneNode ) : mySceneNode(sceneNode)
{
   myScale = 1.0f;
   myRotationAngle = 0.0f;
   myAbstractEffect = 0;
   myObjectId = -1;
   myHoverStatus = false;
   myMaterial = 0;
   myHoverMaterial = 0;
}


//------------------------------------------------------------------------------
void  QSimScenePickHelper::draw( QGLPainter *painter )
{
   // Position the model at its designated position, scale, and orientation.
   painter->modelViewMatrix().push();
   painter->modelViewMatrix().translate( myPosition );

   if( myScale != 1.0f ) painter->modelViewMatrix().scale( myScale );
   if( myRotationAngle != 0.0f )  painter->modelViewMatrix().rotate( myRotationAngle, myRotationVector );

   // Apply the material and effect to the painter.
   QGLMaterial *material = myHoverStatus ? myHoverMaterial : myMaterial;
   painter->setColor( material->diffuseColor() );
   painter->setFaceMaterial( QGL::AllFaces, material );
   if( myAbstractEffect )  painter->setUserEffect( myAbstractEffect );
   else                    painter->setStandardEffect( QGL::LitMaterial );

   // Mark the object for object picking purposes.
   int prevObjectId = painter->objectPickId();
   if( myObjectId != -1 ) painter->setObjectPickId( myObjectId );

   // Draw the geometry.
   mySceneNode.draw( painter );

   // Turn off the user effect, if present.
   if( myAbstractEffect ) painter->setStandardEffect( QGL::LitMaterial );

   // Revert to the previous object identifier.
   painter->setObjectPickId( prevObjectId );

   // Restore the modelview matrix.
   painter->modelViewMatrix().pop();
}


//------------------------------------------------------------------------------
bool  QSimScenePickHelper::event( QEvent *event )
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
      myHoverStatus = true;
      emit mouseHoverChanged();
   }
   else if( event->type() == QEvent::Leave )
   {
      myHoverStatus = false;
      emit mouseHoverChanged();
   }
   return QObject::event( event );
}


//------------------------------------------------------------------------------
}  // End of namespace QSim
