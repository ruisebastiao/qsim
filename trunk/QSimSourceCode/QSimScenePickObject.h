//-----------------------------------------------------------------------------
// File:     QSimScenePickObject.h
// Class:    QSimScenePickObject  
// Parents:  QObject 
// Purpose:  The following classes work together to allow for picking on-screen objects.
//           QSimScenePickObject, QSimScenePickListAndPaint, QSimGLViewWidget.
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
#ifndef  QSIMSCENEPICKOBJECT_H__ 
#define  QSIMSCENEPICKOBJECT_H__
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


//------------------------------------------------------------------------------
class QSimScenePickObject : public QObject
{
   Q_OBJECT

public:
   explicit QSimScenePickObject( QGLSceneNode &sceneNode );
           ~QSimScenePickObject() {;}

    QVector3D  GetPosition() const                          { return myPosition; }
    void       SetPosition( const QVector3D &newPosition )  { myPosition = newPosition; }

    qreal  GetScale() const                  { return myScale; }
    void   SetScale( const qreal newScale )  { myScale = newScale; }

    qreal  GetRotationAngle() const                         { return myRotationAngle; }
    void   SetRotationAngle( const qreal newRotationAngle ) { myRotationAngle = newRotationAngle; }

    QVector3D  GetRotationVector() const                               { return myRotationVector; }
    void       SetRotationVector( const QVector3D& newRotationVector ) { myRotationVector = newRotationVector; }

    QGLMaterial*  GetMaterial() const                     { return myMaterial; }
    void          SetMaterial( QGLMaterial *newMaterial ) { myMaterial = myHoverMaterial = newMaterial; }

    QGLMaterial*  GetHoverMaterial() const                           { return myHoverMaterial; }
    void          SetHoverMaterial( QGLMaterial *newHoverMaterial )  { myHoverMaterial = newHoverMaterial; }

    QGLAbstractEffect*  GetAbstractEffect() const                                 { return myAbstractEffect; }
    void                SetAbstractEffect( QGLAbstractEffect *newAbstractEffect ) { myAbstractEffect = newAbstractEffect; }

    long  GetObjectId() const                 { return myObjectId; }
    void  SetObjectId( const long objectId )  { myObjectId = objectId; }

    void  initialize( QGLView *view, QGLPainter *painter )  { Q_UNUSED(painter);  if( myObjectId != -1 ) view->registerObject(myObjectId, this); }
    void  draw( QGLPainter *painter );

public: signals:
    void  mouseButtonPressed();
    void  mouseButtonReleased();
    void  mouseButtonClicked();
    void  mouseButtonDoubleClicked();
    void  mouseHoverChanged();

protected:
    bool  event( QEvent *e );

private:
    QGLSceneNode      &mySceneNode;
    QVector3D          myPosition;
    qreal              myScale;
    qreal              myRotationAngle;
    QVector3D          myRotationVector;
    QGLMaterial       *myMaterial;
    QGLMaterial       *myHoverMaterial;
    QGLAbstractEffect *myAbstractEffect;
    long               myObjectId;
    bool               myHoverStatus;

private:
   // Register the nodes that are pickable by the user.
   // void  RegisterPickableNodes();

   // When creating a new object, get a unique ID number.
   static unsigned long int  GetNextUniqueID()  { return myNextUniqueID++; } 
   static unsigned long int  myNextUniqueID;
};


//------------------------------------------------------------------------------
}  // End of namespace QSim
//--------------------------------------------------------------------------
#endif  // QSIMSCENEPICKOBJECT_H__
//--------------------------------------------------------------------------
