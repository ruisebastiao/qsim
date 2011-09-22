//-----------------------------------------------------------------------------
// File:     QGLRectangularBox.h
// Class:    QGLRectangularBox  
// Parents:  None 
// Purpose:  Makes a rectangular box for Qt/3D and OpenGL
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
#ifndef  QGLRECTANGULARBOX_H__ 
#define  QGLRECTANGULARBOX_H__
#include "qt3dglobal.h"
#include <QtGui/qvector2d.h>
#include "qvector2darray.h"
#include "qglbuilder.h"


//------------------------------------------------------------------------------
namespace QSim {


//------------------------------------------------------------------------------
class QGLRectangularBox
{

public:
   // Constructors and destructors.
   QGLRectangularBox( const qreal xWidth, const qreal yHeight, const qreal zDepth )  { this->SetXDimension(xWidth);  this->SetYDimension(yHeight);  this->SetZDimension(zDepth); }

   // Set/Get dimensions of rectangular parallelpiped.
   qreal  GetXDimension() const  { return myDimensions[0]; }
   qreal  GetYDimension() const  { return myDimensions[1]; }
   qreal  GetZDimension() const  { return myDimensions[2]; }
   void   SetXDimension( const qreal xWidth  )  { myDimensions[0] = xWidth  > 0 ? xWidth  : 1.0; }
   void   SetYDimension( const qreal yHeight )  { myDimensions[1] = yHeight > 0 ? yHeight : 1.0; }
   void   SetZDimension( const qreal zHeight )  { myDimensions[2] = zHeight > 0 ? zHeight : 1.0; }

private:
   // Dimensions of rectangular parallelpiped, which when not rotated mean:
   // xDimension is width,  yDimension is height,  zDimension is depth.
   qreal myDimensions[3];

};


//------------------------------------------------------------------------------
QGLBuilder& operator << ( QGLBuilder& builder, const QGLRectangularBox& rectangularBox );


//------------------------------------------------------------------------------
}  // End of namespace QSim
//--------------------------------------------------------------------------
#endif  // QGLRECTANGULARBOX_H__
//--------------------------------------------------------------------------
