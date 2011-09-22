//-----------------------------------------------------------------------------
// File:     QGLEllipsoid.h
// Class:    QGLEllipsoid  
// Parents:  None 
// Purpose:  Makes a ellipsoid for Qt/3D and OpenGL
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
#ifndef  QGLELLIPSOID_H__ 
#define  QGLELLIPSOID_H__
#include "qt3dglobal.h"
#include <QtGui/qvector2d.h>
#include "qvector2darray.h"
#include "qglbuilder.h"


//------------------------------------------------------------------------------
namespace QSim {


//------------------------------------------------------------------------------
class QGLEllipsoid
{

public:
   // Constructors and destructors.
   QGLEllipsoid( const qreal xDiameter, const qreal yDiameter, const qreal zDiameter, const unsigned int subdivisionDepth=5 )  { this->SetXDiameter(xDiameter);  this->SetYDiameter(yDiameter);  this->SetZDiameter(zDiameter);  this->SetSubdivisionDepth(subdivisionDepth); }

   // Set/Get dimensions of rectangular parallelpiped.
   qreal         GetXDiameter()  const        { return myXDiameter; }
   qreal         GetYDiameter()  const        { return myYDiameter; }
   qreal         GetZDiameter()  const        { return myZDiameter; }
   unsigned int  GetSubdivisionDepth() const  { return mySubdivisionDepth; }
   void          SetXDiameter(  const qreal xDiameter )                { myXDiameter = xDiameter > 0 ? xDiameter : 1.0; }
   void          SetYDiameter(  const qreal yDiameter )                { myYDiameter = yDiameter > 0 ? yDiameter : 1.0; }
   void          SetZDiameter(  const qreal zDiameter )                { myZDiameter = zDiameter > 0 ? zDiameter : 1.0; }
   unsigned int  SetSubdivisionDepth( unsigned int subdivisionDepth )  { if( subdivisionDepth < 1 ) subdivisionDepth = 1;  else if( subdivisionDepth > 10 ) subdivisionDepth = 10;  return mySubdivisionDepth = subdivisionDepth; }

private:
   // Dimensions of rectangular parallelpiped.
   qreal myXDiameter, myYDiameter, myZDiameter;

   // Maximum depth for ellipsoid subdivision into triangles with values 1=rough to 10 refined and default=5.
   unsigned int  mySubdivisionDepth;

};


//------------------------------------------------------------------------------
QGLBuilder& operator << ( QGLBuilder& builder, const QGLEllipsoid& ellipsoid );


//------------------------------------------------------------------------------
}  // End of namespace QSim
//--------------------------------------------------------------------------
#endif  // QGLELLIPSOID_H__
//--------------------------------------------------------------------------
