//-----------------------------------------------------------------------------
// File:     QGLTetrahedron.cpp
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
#include "QGLTetrahedron.h"
#include "qvector3darray.h"
#include <math.h>


//------------------------------------------------------------------------------
namespace QSim {


//------------------------------------------------------------------------------
QGLTetrahedron::QGLTetrahedron( const QVector3D& vertexA, const QVector3D& vertexB, const QVector3D& vertexC, const QVector3D& vertexD )
{
   myArrayOfVertices[0] = vertexA;
   myArrayOfVertices[1] = vertexB;
   myArrayOfVertices[2] = vertexC;
   myArrayOfVertices[3] = vertexD;

   // Figure out if the vertices need to be re-ordered.
   // Check to see that traversing vertex A, B, C is counter-clockwise when viewed from outside tetrahedron.
   // If not, reorder the vertices by switching vertices B and C.
   if( this->IsTetrahedron3DCheck() < 0 )
   {
      myArrayOfVertices[1] = vertexC;
      myArrayOfVertices[2] = vertexB;
   }
}


//------------------------------------------------------------------------------
QVector3D  QGLTetrahedron::CalculateNormalToPlaneContainingVerticesWithDirectionABcrossAC( unsigned int vertexIndexA, unsigned int vertexIndexB, unsigned int vertexIndexC )  const
{
   if( vertexIndexA > 3 || vertexIndexB > 3 || vertexIndexC > 3 ) return QVector3D(0,0,0);
   const QVector3D vectorAB = this->GetVertex( vertexIndexB ) - this->GetVertex( vertexIndexA );
   const QVector3D vectorAC = this->GetVertex( vertexIndexC ) - this->GetVertex( vertexIndexA );
   return QVector3D::crossProduct( vectorAB, vectorAC );
}


//------------------------------------------------------------------------------
qreal  QGLTetrahedron::CalculateTetrahedronVolume( )  const
{
   // Create normal to the plane containing first three vertices in tetrahedron.
   const QVector3D normalToBasePlane = this->CalculateNormalToPlaneContainingVerticesWithDirectionABcrossAC( 0, 1, 2 );

   // Calculate "signed" volume of tetrahedron.  May be negative, 0, or positive - but is non-negative if tetrahedron constructor complete.
   const QVector3D vector03 = this->GetVertex(3) - this->GetVertex(0);
   const qreal signedVolumeOfTetrahedron = -1.0 / 6.0 * QVector3D::dotProduct( normalToBasePlane, vector03 );
   return signedVolumeOfTetrahedron;
}



//------------------------------------------------------------------------------
qreal  QGLTetrahedron::IsTetrahedron3DCheck( )  const
{
   // Calculate "signed" volume of tetrahedron (may be positive or negative).
   const qreal signedVolumeOfTetrahedron = this->CalculateTetrahedronVolume();
   if( signedVolumeOfTetrahedron == 0.0 ) return 0.0;

   // Find the lengths of first three sides of tetrahedron.
   const QVector3D vector01 = this->GetVertex(1) - this->GetVertex(0);
   const QVector3D vector02 = this->GetVertex(2) - this->GetVertex(0);
   const QVector3D vector03 = this->GetVertex(3) - this->GetVertex(0);
   const qreal length01Squared = vector01.lengthSquared();
   const qreal length02Squared = vector02.lengthSquared();
   const qreal length03Squared = vector03.lengthSquared();

   // Find the maximum length of any side of tetrahedron.
   qreal maxLengthSquared = length01Squared > length02Squared ? length01Squared : length02Squared;
   if( length03Squared > maxLengthSquared ) maxLengthSquared = length03Squared;
   const qreal maxLength = sqrt( maxLengthSquared );

   // Calculate the volume of a tetrahedron with all sides having maximum length, with all angles at vertex0 being 90 degrees.
   // Since volume is 1/6*Dot( a, Cross(b,c) ), this is a maximum volume possible.
   const qreal volumeOfIdealComparisonTetrahedron = 1.0 / 6.0 * maxLength * maxLength * maxLength;

   // Return value is positive if traversing the vertices ordered 0, 1, 2 is counter-clockwise as viewed from outside the tetrahedron.
   // Return value is negative if traversing the vertices ordered 0, 1, 2 is clockwise as viewed from outside the tetrahedron.
   // Absolute value of return value is 1 if tetrahedron is perfectly ideal and near 1 (e.g., 0.1) if well proportioned,
   // and closer to 0 if the tetrahedron is closer to a sliver-thin 2D plane rather than fat 3D tetrahedron.
   const qreal measureOfIdealnessOfActualTetrahedron = signedVolumeOfTetrahedron / volumeOfIdealComparisonTetrahedron;
   return measureOfIdealnessOfActualTetrahedron;
}


//------------------------------------------------------------------------------
QGLBuilder&  operator << ( QGLBuilder& builder, const QGLTetrahedron& tetrahedron )
{
#if 0
   // Less efficient (but easier-to-understand) method for doing this is to create the geometry for each triangle and add it to the builder.
   const QVector3D& vertexA = tetrahedron.GetVertex(0);
   const QVector3D& vertexB = tetrahedron.GetVertex(1);
   const QVector3D& vertexC = tetrahedron.GetVertex(2);
   const QVector3D& vertexD = tetrahedron.GetVertex(3);
   QGeometryData triangle0;   triangle0.appendVertex( vertexA, vertexB, vertexC );    builder.addTriangles( triangle0 );
   QGeometryData triangle1;   triangle1.appendVertex( vertexA, vertexD, vertexB );    builder.addTriangles( triangle1 );
   QGeometryData triangle2;   triangle2.appendVertex( vertexA, vertexC, vertexD );    builder.addTriangles( triangle2 );
   QGeometryData triangle3;   triangle3.appendVertex( vertexB, vertexD, vertexC );    builder.addTriangles( triangle3 );
   return builder;
#else

   // Create space for 4 faces * 3 vertices = 12 vertices of tetrahedron (many are redundant) with a default vertex location of x=0, y=0, z=0.
   QVector3DArray arrayOfVertices( 12, QVector3D(0.0, 0.0, 0.0) );

   // FaceA, outward normal is counter-clockwise when viewed from outside of box (or clockwise when viewed from inside box)
   arrayOfVertices.replace(  0, tetrahedron.GetVertex(0) );
   arrayOfVertices.replace(  1, tetrahedron.GetVertex(1) );
   arrayOfVertices.replace(  2, tetrahedron.GetVertex(2) );

   // FaceB, outward normal is counter-clockwise when viewed from outside of box (or clockwise when viewed from inside box)
   arrayOfVertices.replace(  3, tetrahedron.GetVertex(0) );
   arrayOfVertices.replace(  4, tetrahedron.GetVertex(3) );
   arrayOfVertices.replace(  5, tetrahedron.GetVertex(1) );

   // FaceC, outward normal is counter-clockwise when viewed from outside of box (or clockwise when viewed from inside box)
   arrayOfVertices.replace(  6, tetrahedron.GetVertex(0) );
   arrayOfVertices.replace(  7, tetrahedron.GetVertex(2) );
   arrayOfVertices.replace(  8, tetrahedron.GetVertex(3) );

   // FaceD, outward normal is counter-clockwise when viewed from outside of box (or clockwise when viewed from inside box)
   arrayOfVertices.replace(  9, tetrahedron.GetVertex(1) );
   arrayOfVertices.replace( 10, tetrahedron.GetVertex(3) );
   arrayOfVertices.replace( 11, tetrahedron.GetVertex(2) );

   // Add vertices
   QGeometryData geometryData;
   geometryData.appendVertexArray( arrayOfVertices );

   // Add geometryData to builder - through method that informs builder that provided data is 4-sided faces (Quads).
   builder.addTriangles( geometryData );
   return builder;
#endif
}


//------------------------------------------------------------------------------
}  // End of namespace QSim


