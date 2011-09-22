//-----------------------------------------------------------------------------
// File:     CppStandardHeaders.h
// Purpose:  Includes standard C/C++ language and QSim header files.
//           Directly or indirectly, first header included in most source code files.
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
#ifndef  CPPSTANDARDHEADERS_H__
#define  CPPSTANDARDHEADERS_H__

//------------------------------------------------------------------------------
// Filename enclosed inside < >  means header file is in the Include directory.
// Filename enclosed inside " "  means header file is in the current directory.
#include <cmath>      // Mathematical Constants
#include <cstdarg>    // Variable Argument Lists
#include <cstdio>     // Standard Input/Output Functions
#include <cstdlib>    // Utility Functions
#include <ctime>      // Time and Date information
#include <cassert>    // Verify Program Assertion
#include <cstddef>    // Standard Definitions
#include <exception>  // Exception handling (e.g., try, catch throw)

//------------------------------------------------------------------------------
#define  QSIM_DEBUG__   1

//------------------------------------------------------------------------------
#ifdef _WIN32
   // Disable any possibly annoying warnings. 
   #pragma warning( disable: 4100 )    // For Microsoft Visual Studio 2008, disable warning for un-referenced formal parameter.
   #pragma warning( disable: 4189 )    // For Microsoft Visual Studio 2008, disable warning for un-referenced local variable.
   // If necessary to build .dll, enable DLLExport on windows.
   // #define DLLExport __declspec( dllexport )
#else
   #define DLLExport
#endif


//-----------------------------------------------------------------------------
#endif  // CPPSTANDARDHEADERS_H__
//-----------------------------------------------------------------------------

