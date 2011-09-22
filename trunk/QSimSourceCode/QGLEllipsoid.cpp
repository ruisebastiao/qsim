//-----------------------------------------------------------------------------
// File:     QGLEllipsoid.cpp
// Class:    QGLEllipsoid
// Parents:  None
// Purpose:  Makes an ellipsoid for Qt/3D and OpenGL
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
#include "QGLEllipsoid.h"
#include "qvector3darray.h"
#include <QtCore/qmath.h>


//------------------------------------------------------------------------------
namespace QSim {


//------------------------------------------------------------------------------
QGLBuilder&  operator << ( QGLBuilder& builder, const QGLEllipsoid& ellipsoid )
{
   // Determine the number of slices and stacks to generate.
   static int const numberOfSlicesForSubdivisionDepth[] = { 8, 8, 16, 16, 32, 32, 64, 64, 128, 128 };
   static int const numberOfStacksForSubdivisionDepth[] = { 4, 8,  8, 16, 16, 32, 32, 64,  64, 128 };
   const unsigned int numberOfSlices = numberOfSlicesForSubdivisionDepth[ ellipsoid.GetSubdivisionDepth() - 1 ];
   const unsigned int numberOfStacks = numberOfStacksForSubdivisionDepth[ ellipsoid.GetSubdivisionDepth() - 1 ];

   // Precompute sin/cos values for the slices.
   const unsigned int maxSlices = 128 + 1;
   const unsigned int maxStacks = 128 + 1;
   qreal sliceSin[ maxSlices ];
   qreal sliceCos[ maxSlices ];
   for( unsigned int slice = 0;  slice < numberOfSlices;  ++slice )
   {
       const qreal angle = 2 * M_PI * (numberOfSlices - 1 - slice) / numberOfSlices;
       sliceSin[slice] = qFastSin(angle);
       sliceCos[slice] = qFastCos(angle);
   }
   // Join first and last slice.
   sliceSin[numberOfSlices] = sliceSin[0];
   sliceCos[numberOfSlices] = sliceCos[0];


   // Precompute sin/cos values for the stacks.
   qreal stackSin[ maxStacks ];
   qreal stackCos[ maxStacks ];
   for( unsigned int stack = 0;  stack <= numberOfStacks;  ++stack )
   {
       // Efficiently handle end-points which also ensure geometry comes to a point at the poles (no round-off).
       if(      stack == 0 )               { stackSin[stack] = 0.0f;  stackCos[stack] =  1.0f; }
       else if( stack == numberOfStacks )  { stackSin[stack] = 0.0f;  stackCos[stack] = -1.0f; }
       else
       {
          const qreal angle = M_PI * stack / numberOfStacks;
          stackSin[stack] = qFastSin(angle);
          stackCos[stack] = qFastCos(angle);
       }
   }

   // Half the dimensions of the ellipsoid for calculations below (centroid of ellipsoid is 0, 0, 0.)
   const qreal xRadius = 0.5 * ellipsoid.GetXDiameter();
   const qreal yRadius = 0.5 * ellipsoid.GetYDiameter();
   const qreal zRadius = 0.5 * ellipsoid.GetZDiameter();
   const qreal oneOverXRadiusSquared = 1.0 / (xRadius * xRadius);
   const qreal oneOverYRadiusSquared = 1.0 / (yRadius * yRadius);
   const qreal oneOverZRadiusSquared = 1.0 / (zRadius * zRadius);


   // Create the stacks.
   for( unsigned int stack = 0;  stack < numberOfStacks;  ++stack )
   {
      QGeometryData quadStrip;
      for( unsigned int slice = 0;  slice <= numberOfSlices; ++slice )
      {
          // Equation for ellipsoid surface is x^2/xRadius^2 + y^2/yRadius^2 + z^2/zRadius^2 = 1
          // Location of vertices can be specified in terms of "polar coordinates".
          const qreal nextx = xRadius * stackSin[stack+1] * sliceSin[slice];
          const qreal nexty = yRadius * stackSin[stack+1] * sliceCos[slice];
          const qreal nextz = zRadius * stackCos[stack+1];
          quadStrip.appendVertex( QVector3D( nextx, nexty, nextz) );

          // Equation for ellipsoid surface is  Surface = x^2/xRadius^2 + y^2/yRadius^2 + z^2/zRadius^2 - 1
          // Gradient for ellipsoid is  x/xRadius^2*Nx>  +  y/yRadius^2*Ny>  +  z/zRadius^2*Nz>
          // Gradient for sphere simplifies to  x*Nx> + y*Ny> + z*Nz>
          // const qreal nextGradientx =  stackSin[stack+1] * sliceSin[slice];
          // const qreal nextGradienty =  stackSin[stack+1] * sliceCos[slice];
          // const qreal nextGradientz =  stackCos[stack+1];
          const qreal nextGradientx = nextx * oneOverXRadiusSquared;
          const qreal nextGradienty = nexty * oneOverYRadiusSquared;
          const qreal nextGradientz = nextz * oneOverZRadiusSquared;
          const qreal nextGradientMagSquared = nextGradientx * nextGradientx + nextGradienty * nextGradienty + nextGradientz * nextGradientz;
          const qreal oneOverNextGradientMagnitude = 1.0 / sqrt( nextGradientMagSquared );
          quadStrip.appendNormal( oneOverNextGradientMagnitude * QVector3D( nextGradientx,  nextGradienty, nextGradientz ) );
          quadStrip.appendTexCoord( QVector2D(1.0f - qreal(slice) / numberOfSlices, 1.0f - qreal(stack + 1) / numberOfStacks) );

          const qreal x = xRadius * stackSin[stack] * sliceSin[slice];
          const qreal y = yRadius * stackSin[stack] * sliceCos[slice];
          const qreal z = zRadius * stackCos[stack];
          quadStrip.appendVertex( QVector3D( x, y, z) );

          // const qreal gradientx =  stackSin[stack] * sliceSin[slice];
          // const qreal gradienty =  stackSin[stack] * sliceCos[slice];
          // const qreal gradientz =  stackCos[stack];
          const qreal gradientx = x * oneOverXRadiusSquared;
          const qreal gradienty = y * oneOverYRadiusSquared;
          const qreal gradientz = z * oneOverZRadiusSquared;
          const qreal gradientMagSquared = gradientx * gradientx + gradienty * gradienty + gradientz * gradientz;
          const qreal oneOverGradientMagnitude = 1.0 / sqrt( gradientMagSquared );
          quadStrip.appendNormal( oneOverGradientMagnitude * QVector3D(  gradientx, gradienty, gradientz) );
          quadStrip.appendTexCoord( QVector2D(1.0f - qreal(slice) / numberOfSlices,  1.0f - qreal(stack) / numberOfStacks) );
      }

      // The quad strip stretches from pole to pole.
      builder.addQuadStrip( quadStrip );
   }


   return builder;
}


//------------------------------------------------------------------------------
}  // End of namespace QSim


