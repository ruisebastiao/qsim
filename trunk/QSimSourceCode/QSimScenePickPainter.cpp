//-----------------------------------------------------------------------------
// File:     QSimScenePickPainter.cpp
// Class:    QSimScenePickPainter
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
#include "QSimScenePickPainter.h"
#include "QSimScenePickHelper.h"


//------------------------------------------------------------------------------
namespace QSim {


//------------------------------------------------------------------------------
void  QSimScenePickPainter::initialize( QGLView *view, QGLPainter *painter )
{
   // Initialize all the children (which should all be of type QSimScenePickHelper).
   QList<QObject*> listOfChildren = this->children();
   for( QList<QObject*>::iterator it = listOfChildren.begin();  it != listOfChildren.end();  ++it )
   {
      QSimScenePickHelper *obj = qobject_cast<QSimScenePickHelper*>( *it );
      if( obj ) obj->initialize( view, painter );
   }
}


//------------------------------------------------------------------------------
void QSimScenePickPainter::draw( QGLPainter *painter )
{
   // Draw all the children (which should all be of type QSimScenePickHelper).
   QList<QObject*> listOfChildren = this->children();
   for( QList<QObject*>::iterator it = listOfChildren.begin();  it != listOfChildren.end();  ++it )
   {
      QSimScenePickHelper *obj = qobject_cast<QSimScenePickHelper*>( *it );
      if( obj ) obj->draw( painter );
   }
}


//------------------------------------------------------------------------------
}  // End of namespace QSim
