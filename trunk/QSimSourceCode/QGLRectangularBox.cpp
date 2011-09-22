//-----------------------------------------------------------------------------
// File:     QGLRectangularBox.cpp
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
#include "QGLRectangularBox.h"
#include "qvector3darray.h"
#include "qglcube.h"


//------------------------------------------------------------------------------
namespace QSim {


//------------------------------------------------------------------------------
QGLBuilder&  operator << ( QGLBuilder& builder, const QGLRectangularBox& rectangularBox )
{
   // Half the dimensions of the box to locate the centroid of the box and 0, 0, 0.
   const qreal xValue = 0.5 * rectangularBox.GetXDimension();
   const qreal yValue = 0.5 * rectangularBox.GetYDimension();
   const qreal zValue = 0.5 * rectangularBox.GetZDimension();

#if 0
   // One method to build rectangular box is by building a cube and scaling each vertex.
   QGLBuilder builderForCube;
   builderForCube << QGLCube( 1.0 );
   QGLSceneNode* sceneNode = builderForCube.finalizedSceneNode();
   QGeometryData cubeGeometryData = sceneNode->geometry();

   // Get a copy of the vertex position data.
   QVector3DArray arrayOfVertices = cubeGeometryData.vertices();
   const int numberOfVertices =  arrayOfVertices.size();
   for( int i=0;  i<numberOfVertices;  i++ )
   {
      QVector3D& vertexi = arrayOfVertices[i];
      vertexi.setX( xValue * vertexi.x() );
      vertexi.setY( yValue * vertexi.y() );
      vertexi.setZ( zValue * vertexi.z() );
   }

   // Call destructor on resources allocated for sceneNode.
   sceneNode->~QGLSceneNode();
   sceneNode = NULL;

#else
   // One method to build rectangular box is by specifying each vertex.
   // Create space for 6 faces * 4 vertices = 24 vertices of box (many are redundant) with a default vertex location of x=0, y=0, z=0.
   QVector3DArray arrayOfVertices( 24, QVector3D(0.0, 0.0, 0.0) );

   // Left face, outward normal is counter-clockwise when viewed from outside of box (or clockwise when viewed from inside box)
   arrayOfVertices.replace(  0, QVector3D(-xValue, -yValue, -zValue) );
   arrayOfVertices.replace(  1, QVector3D(-xValue, -yValue,  zValue) );
   arrayOfVertices.replace(  2, QVector3D(-xValue,  yValue,  zValue) );
   arrayOfVertices.replace(  3, QVector3D(-xValue,  yValue, -zValue) );

   // Top face, outward normal is counter-clockwise when viewed from outside of box (or clockwise when viewed from inside box)
   arrayOfVertices.replace(  4, QVector3D(-xValue,  yValue, -zValue) );
   arrayOfVertices.replace(  5, QVector3D(-xValue,  yValue,  zValue) );
   arrayOfVertices.replace(  6, QVector3D( xValue,  yValue,  zValue) );
   arrayOfVertices.replace(  7, QVector3D( xValue,  yValue, -zValue) );

   // Right face, outward normal is counter-clockwise when viewed from outside of box (or clockwise when viewed from inside box)
   arrayOfVertices.replace(  8, QVector3D( xValue,  yValue, -zValue) );
   arrayOfVertices.replace(  9, QVector3D( xValue,  yValue,  zValue) );
   arrayOfVertices.replace( 10, QVector3D( xValue, -yValue,  zValue) );
   arrayOfVertices.replace( 11, QVector3D( xValue, -yValue, -zValue) );

   // Bottom face, outward normal is counter-clockwise when viewed from outside of box (or clockwise when viewed from inside box)
   arrayOfVertices.replace( 12, QVector3D( xValue, -yValue, -zValue) );
   arrayOfVertices.replace( 13, QVector3D( xValue, -yValue,  zValue) );
   arrayOfVertices.replace( 14, QVector3D(-xValue, -yValue,  zValue) );
   arrayOfVertices.replace( 15, QVector3D(-xValue, -yValue, -zValue) );

   // Front face, outward normal is counter-clockwise when viewed from outside of box (or clockwise when viewed from inside box)
   arrayOfVertices.replace( 16, QVector3D( xValue, -yValue,  zValue) );
   arrayOfVertices.replace( 17, QVector3D( xValue,  yValue,  zValue) );
   arrayOfVertices.replace( 18, QVector3D(-xValue,  yValue,  zValue) );
   arrayOfVertices.replace( 19, QVector3D(-xValue, -yValue,  zValue) );

   // Back face, outward normal is counter-clockwise when viewed from outside of box (or clockwise when viewed from inside box)
   arrayOfVertices.replace( 20, QVector3D( xValue,  yValue, -zValue) );
   arrayOfVertices.replace( 21, QVector3D( xValue, -yValue, -zValue) );
   arrayOfVertices.replace( 22, QVector3D(-xValue, -yValue, -zValue) );
   arrayOfVertices.replace( 23, QVector3D(-xValue,  yValue, -zValue) );

   // Add vertices
   QGeometryData geometryData;
   geometryData.appendVertexArray( arrayOfVertices );

   // Create space for 4 corners of an arbitrary surface of the rectangular box.
   // Specify the 2D (x,y) texture coordinates on one face.
   // This one piece of data will be reused for each of the 6 faces in the rectangular parallelpiped (box).
   // I think these take on values from 0 to 1 with 1 meaning full stretch and 0 meaning no stretch.
   QVector2DArray singleFaceTextureCoordinatesArray( 4, QVector2D(0.0, 0.0) );
   singleFaceTextureCoordinatesArray.replace( 0, QVector2D( 1.0, 0.0 ) );
   singleFaceTextureCoordinatesArray.replace( 1, QVector2D( 1.0, 1.0 ) );
   singleFaceTextureCoordinatesArray.replace( 2, QVector2D( 0.0, 1.0 ) );
   singleFaceTextureCoordinatesArray.replace( 3, QVector2D( 0.0, 0.0 ) );

   // Create space for 24 corners of box (many are redundant) with a default initialization of x=0, y=0.
   for( int i = 0;  i < 6; ++i ) geometryData.appendTexCoordArray( singleFaceTextureCoordinatesArray );

   // Add geometryData to builder - through method that informs builder that provided data is 4-sided faces (Quads).
   builder.addQuads( geometryData );
#endif

   return builder;
}


//------------------------------------------------------------------------------
}  // End of namespace QSim


