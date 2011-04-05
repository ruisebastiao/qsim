//-----------------------------------------------------------------------------
// File:     OpenSimQtStartSimulation.h
// Class:    OpenSimQtStartSimulation.h
// Parent:   QObject
// Purpose:  Class that starts simulation.
/* ------------------------------------------------------------------------- *
*                                 OpenSimQt                                  *
* -------------------------------------------------------------------------- *
* OpenSimQt was developed with support from Simbios (the NIH National Center *
* for Physics-Based Simulation Biological Structures at Stanford) under NIH  *
* Roadmap for Medical Research grant U54 GM072970 and from NCSRR (National   *
* Center for Simulation in Rehabilitation Research) under NIH research       *
* infrastructure grant R24 HD065690.                                         *
*                                                                            *
* Portions copyright (c) 2011 the Authors and Stanford University.           *
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
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL    *
* THE AUTHORS, CONTRIBUTORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,    *
* DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR      *
* OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE  *
* USE OR OTHER DEALINGS IN THE SOFTWARE.                                     *
* -------------------------------------------------------------------------- */
#include "OpenSimQtStandardHeaders.h"
//#include "OpenSimQtStartSimulation.h"
#include <SimTKsimbody.h>
using namespace SimTK;

//------------------------------------------------------------------------------
namespace OpenSimQt {


//-----------------------------------------------------------------------------
// Prototypes for local functions (functions not called by code in other files)
//-----------------------------------------------------------------------------
bool  WriteExceptionToFile( const char* outputString, const char* exceptionStringOrNull )
{
   bool retValue = false;

#if __OPENSIM_QT_DEBUG__
   FILE *outputFile = fopen( "C:\\OpenSimQt\\ExceptionsThrown.txt", "a+" );
   if( outputFile && outputString )
   {
      retValue = fputs( outputString, outputFile ) != EOF;
      if( exceptionStringOrNull )
          retValue = retValue && fputs( exceptionStringOrNull, outputFile ) != EOF;
      fflush( outputFile );
      fclose( outputFile );
   }
#endif
   return retValue;
}


//-----------------------------------------------------------------------------
bool  StartAndRunSimulationMathematicsInsideExceptionHandling( )
{

   // Create the system, with subsystems for the bodies and some forces.
   MultibodySystem system;
   SimbodyMatterSubsystem matter(system);
   GeneralForceSubsystem forces(system);

   // Add gravity as a force element.
   Force::UniformGravity gravity(forces, matter, Vec3(0, -9.8, 0));

   // Create the body and some artwork for it.
   Body::Rigid pendulumBody(MassProperties(1.0, Vec3(0), Inertia(1)));
   pendulumBody.addDecoration(Transform(), DecorativeSphere(0.1).setColor(Red));

   // Add an instance of the body to the multibody system by connecting
   // it to Ground via a pin mobilizer.
   MobilizedBody::Pin pendulum(matter.updGround(), Transform(Vec3(0)),
                               pendulumBody, Transform(Vec3(0, 1, 0)));

   // Visualize with default options; ask for a report every 1/30 of a second
   // to match the Visualizer's default 30 frames per second rate.
   // The Simbody visualizer must be able to execute the program VisualizerGUI.exe
   // One way for Simbody to find this program is to set the environment variable
   // SimTK_INSTALL_DIR  with a value  FullPathTo/Simbody/bin  folder.
   Visualizer viz(system);
   system.addEventReporter(new Visualizer::Reporter(viz, 1./30));

   // Initialize the system and state.

   system.realizeTopology();
   State state = system.getDefaultState();
   pendulum.setOneU(state, 0, 1.0); // initial velocity 1 rad/sec

   // Simulate it.

   RungeKuttaMersonIntegrator integ(system);
   TimeStepper ts(system, integ);
   ts.initialize(state);
   ts.stepTo(10.0);


	 // Simulation completed properly
   return true;
}


//-----------------------------------------------------------------------------
bool  StartAndRunSimulationMathematics( )
{

   // The try-catch code in this main routine catches exceptions thrown by functions in the
   // try block, e.g., catching an exception that occurs when a NULL pointer is de-referenced.
   try
   {
      return StartAndRunSimulationMathematicsInsideExceptionHandling( );
   }

   // This catch statement handles certain types of exceptions
   catch( const std::exception &e )
   {
      WriteExceptionToFile( "\n\n Error: Programming error exception thrown:\n ", e.what() );
      return false;
   }

   // The exception-declaration statement (...) handles any type of exception,
   // including C exceptions and system/application generated exceptions.
   // This includes exceptions such as memory protection and floating-point violations.
   // An ellipsis catch handler must be the last handler for its try block.
   catch( ... )
   {
      WriteExceptionToFile( "\n\n Error: Programming error.  Unhandled exception.", NULL );
      return false;
   }


	 // Simulation completed properly
   return true;
}


//------------------------------------------------------------------------------
}  // End of namespace OpenSimQt



