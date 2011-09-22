//-----------------------------------------------------------------------------
// File:     QSimSceneNode.h
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
#include "QSimMaterialType.h"
#include "QSimRigidBodyTabWidget.h"


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
   QSimSceneNode( QGLSceneNode& sceneNode, QSimGLViewWidget& glViewWidget, const bool isObjectPickable, const char *objectNameOrNull );
  ~QSimSceneNode()  { this->SetSceneObjectPickableToFalseDeregisterDisconnect(); }

   // This object can be rotated by a certain angle (in degrees) about a certain vector.
   void  SetRotationAngleInDegreesAndVector( const qreal newRotationAngleInDegrees, const QVector3D& newRotationVector ) { this->SetRotationAngleInDegrees(newRotationAngleInDegrees); this->SetRotationVector(newRotationVector); }

   // This object can be translated by a certain vector amount.
   QVector3D  GetPosition() const                          { return myPosition; }
   void       SetPosition( const QVector3D& newPosition )  { myQGLSceneNode.setPosition( myPosition = newPosition ); }

   // Material that is regularly displayed, or if object is pickable, when it is highlighted (e.g., mouse hovers on it).
   const QSimMaterialType&  GetMaterialStandard() const                             { return myMaterialStandard;  }
   const QSimMaterialType&  GetMaterialHighlight() const                            { return myMaterialHighlight; }
   const QSimMaterialType&  GetMaterialBasedOnHoverStatus() const                   { return this->GetHoverStatus() ? this->GetMaterialHighlight() : this->GetMaterialStandard(); }
   void                     SetMaterialStandard(  const QGLMaterial& newMaterial )  { myMaterialStandard.SetQSimMaterialType( newMaterial ); }
   void                     SetMaterialHighlight( const QGLMaterial& newMaterial )  { myMaterialHighlight.SetQSimMaterialType( newMaterial ); }

   const QGLAbstractEffect*  GetAbstractEffect() const                                 { return myAbstractEffect; }
   void                      SetAbstractEffect( QGLAbstractEffect* newAbstractEffect ) { myAbstractEffect = newAbstractEffect; }

   // Determine whether or not this object can be picked by the user.
   void   SetObjectPickable( const bool isObjectPickable );
   bool   IsObjectPickable( )  { return myObjectIsPickable; }

   // Keep track of whether or not the object was selected (or should be de-selected).
   void  SetThisObjectWasSelectedAndDeselectOthers();
   void  SetObjectIsSelected( const bool isObjectSelected )  { myObjectIsSelected = isObjectSelected; }
   bool  IsObjectSelected()                                  { return myObjectIsSelected; }

   // Each instance of this class is always associated with an OpenGL view widget (set in constructor).
   QSimGLViewWidget&  GetSceneNodeQSimGLViewWidget()   { return mySceneNodeQSimGLViewWidget; }
   void               SetSceneObjectPickableToFalseDeregisterDisconnect();

   // Each instance of this class is always associated with a QGLSceneNode.
         QGLSceneNode&  GetQGLSceneNode()        { return myQGLSceneNode; }
   const QGLSceneNode&  GetQGLSceneNode() const  { return myQGLSceneNode; }

   // When creating a new object, get a unique ID number.
   static unsigned long  GetNextUniqueID()   { return myNextUniqueID++; } 
   long  GetObjectId() const                 { return myObjectId; }
   long  SetObjectId( const long objectId )  { return myObjectId = objectId; }

   // Get objectName[objectID], e.g., cylinder[2].
   void  GetObjectNameAndObjectIdInsideSquareBrackets( QString& objectNameAndIdInsideSquareBrackets )  { QTextStream( &objectNameAndIdInsideSquareBrackets ) << this->objectName() << "[" << this->GetObjectId() << "]"; }

   // Special information for initializing and drawing instances of this class.
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
   void  ObjectWasSoleSelected()    { this->SetThisObjectWasSelectedAndDeselectOthers(); }
   void  ObjectWasDoubleClicked();

private:
   // First set myObjectIsPickable to false, then initialize all the relevant fields in this object.
   void  InitializeQSimSceneNode()  { myObjectIsPickable = myObjectIsSelected = false;  myAbstractEffect = NULL;  this->SetMaterialStandard( QSimMaterialType::GetChinaMaterialStandard() );  this->SetMaterialHighlight( QSimMaterialType::GetChinaMaterialHighlight() );  this->SetHoverStatus(false);  this->SetRotationAngleInDegreesAndVector( 0, QVector3D(1,0,0) );  this->SetPosition( QVector3D(1,0,0) );  this->SetScale(1.0);  this->SetObjectId( QSimSceneNode::GetNextUniqueID() );  }

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
   bool  GetHoverStatus() const                       { return myHoverStatus; }

   // Keep track of whether or not the object is pickable.
   // Keep track of whether or not the object was selected (or should be de-selected).
   bool  myObjectIsPickable;
   bool  myObjectIsSelected;

   // Need to check out what this is.
   QGLAbstractEffect* myAbstractEffect;

   // Each instance of this class is always associated with a QGLSceneNode (set in constructor).
   QGLSceneNode&  myQGLSceneNode;

   // Each instance of this class is always associated with an OpenGL view widget (set in constructor).
   QSimGLViewWidget&  mySceneNodeQSimGLViewWidget;

   // Each instance of this class has one associated dialogue box for its properties.
   // Although this wastes some memory - it also ensures the dialogue boxes disappears when the object is deleted.
   QSimRigidBodyTabWidget  myRigidBodyTabWidget;
 
   // Material that is regularly displayed, or if object is pickable, when it is highlighted (e.g., mouse hovers on it).
   QSimMaterialType  myMaterialStandard;
   QSimMaterialType  myMaterialHighlight;

   // When creating a new object, get a unique ID number.
   long                  myObjectId;
   static unsigned long  myNextUniqueID;
};


//------------------------------------------------------------------------------
}  // End of namespace QSim
//--------------------------------------------------------------------------
#endif  // QSIMSCENENODE_H__
//--------------------------------------------------------------------------
