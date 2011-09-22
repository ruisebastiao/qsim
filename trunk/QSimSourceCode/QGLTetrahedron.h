//-----------------------------------------------------------------------------
// File:     QGLTetrahedron.h
// Class:    QGLTetrahedron  
// Parents:  None 
// Purpose:  Makes a tetrahedron for Qt/3D and OpenGL
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
#ifndef  QGLTETRAHEDRON_H__ 
#define  QGLTETRAHEDRON_H__
#include "qt3dglobal.h"
#include <QtGui/qvector2d.h>
#include "qvector2darray.h"
#include "qglbuilder.h"


//------------------------------------------------------------------------------
namespace QSim {


//------------------------------------------------------------------------------
class QGLTetrahedron
{

public:
   // Constructors and destructors.  Note, the order of vertex B and C are switched if tetrahedron not in "canonical" form.
   QGLTetrahedron( const QVector3D& vertexA, const QVector3D& vertexB, const QVector3D& vertexC, const QVector3D& vertexD );

   // Set/Get dimensions of rectangular parallelpiped.
   const QVector3D&  GetVertex( const unsigned int i )  const  { return myArrayOfVertices[ i <= 3 ? i : 0 ]; }

   // Return normal (not unitNormal) to plane containing 3 vertices with direction determined by cross product of CrossProduct( vectorAB, vectorAC )
   QVector3D  CalculateNormalToPlaneContainingVerticesWithDirectionABcrossAC( unsigned int vertexIndexA, unsigned int vertexIndexB, unsigned int vertexIndexC )  const;

   // Calculate signed volume of tetrahedron.
   // Return value is 0 if all the vertices lie in the same plane.
   // Return value is positive if traversing the vertices ordered 0, 1, 2 is counter-clockwise as viewed from outside the tetrahedron.
   // Return value is negative if traversing the vertices ordered 0, 1, 2 is         clockwise as viewed from outside the tetrahedron.
   qreal  CalculateTetrahedronVolume( )  const;

   // Return value is positive if traversing the vertices ordered 0, 1, 2 is counter-clockwise as viewed from outside the tetrahedron.
   // Return value is negative if traversing the vertices ordered 0, 1, 2 is clockwise as viewed from outside the tetrahedron.
   // Absolute value of return value is 1 if tetrahedron is perfectly ideal and near 1 (e.g., 0.1) if well proportioned, 
   // and closer to 0 if the tetrahedron is closer to a sliver-thin 2D plane rather than fat 3D tetrahedron.      
   qreal  IsTetrahedron3DCheck( )  const;

private:
   // Store array of vertices for tetrahedron.
   QVector3D  myArrayOfVertices[4];

};


//------------------------------------------------------------------------------
QGLBuilder& operator << ( QGLBuilder& builder, const QGLTetrahedron& rectangularBox );


//------------------------------------------------------------------------------
}  // End of namespace QSim
//--------------------------------------------------------------------------
#endif  // QGLTETRAHEDRON_H__
//--------------------------------------------------------------------------
