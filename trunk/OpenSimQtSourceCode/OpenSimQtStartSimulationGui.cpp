//-----------------------------------------------------------------------------
// File:     OpenSimQtStartSimulationGui.cpp
// Class:    OpenSimQtStartSimulation
// Parent:   QObject
// Purpose:  Catches the Qt widget signal that starts the simulation.
//           There are TWO .cpp files for this class.
//           OpenSimQtStartSimulationNoGui.cpp contains standard C++ (non-Qt) methods to run simulation.
//           OpenSimQtStartSimulationGui.cpp contains Qt methods to display/interact with simulation.
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
#include "OpenSimQtStartSimulation.h"

//------------------------------------------------------------------------------
namespace OpenSimQt {


//------------------------------------------------------------------------------
void  OpenSimQtStartSimulation::StartSimulation( )
{
   // Qt provides four kinds of buttons: QPushButton, QCheckBox, QRadioButton, and QToolButton.
   // QPushButton widgetPushButtonToStartSimulation( "Push button to start simulation", 0 );
   // widgetPushButtonToQuit.resize( 600, 180 );
   // QObject::connect( &widgetPushButtonToStartSimulation, SIGNAL( clicked() ), &app, SLOT( quit() ) );
   // mainWindowLayoutManager.addWidget( &widgetPushButtonToQuit );

   // QLibrary simbodyLibrary( "Simbody" );
   // simbodyLibrary.load();
   StartAndRunSimulationMathematics();
}


//------------------------------------------------------------------------------
}  // End of namespace OpenSimQt



