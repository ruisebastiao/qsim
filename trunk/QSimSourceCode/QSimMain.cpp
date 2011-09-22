//------------------------------------------------------------------------------
// File:     QSimMain.cpp
// Class:    None
// Parent:   None
// Purpose:  Start of program and catches any un-handled exceptions.
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
#include "QSimGui.h"


//-----------------------------------------------------------------------------
// The executable program starts here
//-----------------------------------------------------------------------------
int  main( int numberOfCommandLineArguments, char *arrayOfCommandLineArguments[] )
{
   // Default value is program succeeded.
   int programSucceededIs0 = 0;

   // The try-catch code in this main routine catches exceptions thrown by functions in the
   // try block, e.g., catching an exception that occurs when a NULL pointer is de-referenced.
   try
   {
      programSucceededIs0 = QSim::QSimGui( numberOfCommandLineArguments, arrayOfCommandLineArguments );
   }

#if 0 && OPENSIM_QT_DEBUG__
   // This catch statement handles certain types of exceptions
   catch( const exception &e )
   {
      // printf( "\n\n Error: Programming error encountered.\n The exception thrown is: %s\n", e.what() );
      // getchar();  // Keeps the screen displayed until the user presses the Enter (or Return) key.
      programSucceededIs0 = 2;
   }
#endif

   // The exception-declaration statement (...) handles any type of exception,
   // including C exceptions and system/application generated exceptions.
   // This includes exceptions such as memory protection and floating-point violations.
   // An ellipsis catch handler must be the last handler for its try block.
   catch( ... )
   {
      programSucceededIs0 = 1;
   }

   // The value returned by the main function is the exit status of the program.
   // A normal program exit returns 0 (other return values usually signal an error).
   return programSucceededIs0;
}

