//-----------------------------------------------------------------------------
// File:     QSimSceneNode.h
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
#ifndef  QSIMSCENENODE_H__ 
#define  QSIMSCENENODE_H__
#include <QtCore>
#include <QtGui>
#include <QtOpenGL>
#include "qglview.h"
#include "qglscenenode.h"
#include "qglpainter.h"
#include "CppStandardHeaders.h"
#include "QSimGenericFunctions.h"


//------------------------------------------------------------------------------
namespace QSim {

// Forward declarations
class  QSimScenePickListAndPaint;
class  QSimGLViewWidget;


//------------------------------------------------------------------------------
class QSimSceneNode : public QObject
{
   Q_OBJECT

public:
   // Constructors and destructors.
   explicit QSimSceneNode( QGLSceneNode& sceneNode ) : QObject(&sceneNode), myQGLSceneNode(sceneNode)  { this->InitializeQSimSceneNode(); }
            QSimSceneNode( QGLSceneNode& sceneNode, QSimGLViewWidget& viewWidgetIfPickableOrNullIfNotPickable );
           ~QSimSceneNode() { this->SetSceneObjectPickable(NULL); }

   // This object can be rotated by a certain angle (in degrees) about a certain vector.
   void  SetRotationAngleInDegreesAndVector( const qreal newRotationAngleInDegrees, const QVector3D& newRotationVector ) { this->SetRotationAngleInDegrees(newRotationAngleInDegrees); this->SetRotationVector(newRotationVector); }

   // This object can be translated by a certain vector amount.
   QVector3D  GetPosition() const                          { return myPosition; }
   void       SetPosition( const QVector3D& newPosition )  { myQGLSceneNode.setPosition( myPosition = newPosition ); }

   // Material that is regularly displayed, or if object is pickable, when it is highlighted (e.g., mouse hovers on it).
   QGLMaterial*  GetMaterialStandard() const                       { return myMaterialStandard; }
   QGLMaterial*  GetMaterialHighlight() const                      { return myMaterialHighlight; }
   void          SetMaterialStandard(  QGLMaterial* newMaterial )  { myMaterialStandard  = newMaterial; }
   void          SetMaterialHighlight( QGLMaterial* newMaterial )  { myMaterialHighlight = newMaterial; }

   QGLAbstractEffect*  GetAbstractEffect() const                                 { return myAbstractEffect; }
   void                SetAbstractEffect( QGLAbstractEffect* newAbstractEffect ) { myAbstractEffect = newAbstractEffect; }

   // Determine whether or not this object can be picked by the user.
   void  SetSceneObjectPickable( QSimGLViewWidget* viewWidgetIfPickableOrNullIfNotPickable );
   bool  IsSceneObjectPickable( )  { return myViewWidgetIfPickableOrNullIfNotPickable != NULL; }

   // Each instance of this class is always associated with a QGLSceneNode.
         QGLSceneNode&  GetQGLSceneNode()        { return myQGLSceneNode; }
   const QGLSceneNode&  GetQGLSceneNode() const  { return myQGLSceneNode; }

   // When creating a new object, get a unique ID number.
   static unsigned long  GetNextUniqueID()   { return myNextUniqueID++; } 
   long  GetObjectId() const                 { return myObjectId; }
   long  SetObjectId( const long objectId )  { return myObjectId = objectId; }

   // Special information for initializing and drawing instances of this class.
   void  RegisterQSimSceneNodeToBePickable( QGLView& view )  { view.registerObject(myObjectId,this); }
   void  DrawOpenGLForQSimSceneNode( QGLPainter& painter );

signals:
   void  mouseButtonPressed();
   void  mouseButtonReleased();
   void  mouseButtonClicked();
   void  mouseButtonDoubleClicked();
   void  mouseHoverChanged();

protected:
   bool  event( QEvent *e );

private slots:
   void  ObjectWasSelected();

private:
   // Initialize all the relevant fields in this object.
   void  InitializeQSimSceneNode()  { myAbstractEffect = NULL;  myMaterialStandard = myMaterialHighlight = NULL;  myViewWidgetIfPickableOrNullIfNotPickable = NULL;  this->SetHoverStatus(false);  this->SetRotationAngleInDegreesAndVector( 0, QVector3D(1,0,0) );  this->SetPosition( QVector3D(1,0,0) );  this->SetScale(1.0);  this->SetObjectId( QSimSceneNode::GetNextUniqueID() ); }

   // This object can be rotated by a certain angle (in degrees) about a certain vector.
   qreal      myRotationAngleInDegrees;
   QVector3D  myRotationVector;
   qreal      GetRotationAngleInDegrees() const                                   { return myRotationAngleInDegrees; }
   QVector3D  GetRotationVector() const                                           { return myRotationVector; }
   void       SetRotationAngleInDegrees( const qreal newRotationAngleInDegrees )  { myRotationAngleInDegrees = newRotationAngleInDegrees; }
   void       SetRotationVector( const QVector3D& newRotationVector )             { myRotationVector = newRotationVector; }

   // This object can be translated by a certain vector amount.
   QVector3D  myPosition;

   // This object can be scaled.
   qreal  myScale;
   qreal  GetScale() const                  { return myScale; }
   void   SetScale( const qreal newScale )  { myScale = newScale; }

   // Keep track of whether or not the mouse entered or left an object.
   bool  myHoverStatus;
   void  SetHoverStatus( const bool newHoverStatus )  { myHoverStatus = newHoverStatus; }
   bool  GetHoverStatus()                             { return myHoverStatus; }

   // Need to check out what this is.
   QGLAbstractEffect* myAbstractEffect;

   // Each instance of this class is always associated with a QGLSceneNode.
   QGLSceneNode&  myQGLSceneNode;

   // Determine whether or not this scene object is pickable by the user (e.g., with a mouse click).
   QSimGLViewWidget*  myViewWidgetIfPickableOrNullIfNotPickable;

   // Material that is regularly displayed, or if object is pickable, when it is highlighted (e.g., mouse hovers on it).
   QGLMaterial*  myMaterialStandard;
   QGLMaterial*  myMaterialHighlight;

   // When creating a new object, get a unique ID number.
   long                  myObjectId;
   static unsigned long  myNextUniqueID;
};


//------------------------------------------------------------------------------
}  // End of namespace QSim
//--------------------------------------------------------------------------
#endif  // QSIMSCENENODE_H__
//--------------------------------------------------------------------------
