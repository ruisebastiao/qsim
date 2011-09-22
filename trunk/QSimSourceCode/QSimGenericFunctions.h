//-----------------------------------------------------------------------------
// File:     QSimGenericFunctions.h
// Purpose:  Generically useful ANSI C++ standard functions.
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
#ifndef  QSIMGENERICFUNCTIONS_H__
#define  QSIMGENERICFUNCTIONS_H__
#include "CppStandardHeaders.h"


//------------------------------------------------------------------------------
namespace QSim {

   // Random integer in the range from min to max.
   inline int  GetRandomIntegerInRange( const int min, const int max )  { srand( (unsigned int)(time(NULL)) );  const int range = max + 1 - min;  return min + (rand() % range); } 

   // Suspend program execution for designated number of milliseconds.
   inline void  SleepInMilliseconds( const unsigned long numMillisecondsToSleep )  { const clock_t stopClock = numMillisecondsToSleep + std::clock();  while( std::clock() < stopClock ) {;} }

   // Enumerated types related to just x, y, z or signed directions -z -y, -x, +x, +y, +z
   enum UnsignedXYZDirection{ UnsignedXDirection=0, UnsignedYDirection, UnsignedZDirection };
   enum SignedXYZDirection{ NegativeZDirection=0, NegativeYDirection, NegativeXDirection, positiveXDirection, positiveYDirection, positiveZDirection };
    
//------------------------------------------------------------------------------
}  // End of namespace OpenSimQT


//-----------------------------------------------------------------------------
#endif  // QSIMGENERICFUNCTIONS_H__
//-----------------------------------------------------------------------------
