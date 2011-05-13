//-----------------------------------------------------------------------------
// File:     CppStandardHeaders.h
// Purpose:  Includes standard C/C++ language and QSim header files.
//           Directly or indirectly, first header included in most source code files.
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

