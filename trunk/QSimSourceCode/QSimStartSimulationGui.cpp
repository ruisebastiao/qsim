//-----------------------------------------------------------------------------
// File:     QSimStartSimulationGui.cpp
// Class:    QSimStartSimulation
// Parent:   QObject
// Purpose:  Catches the Qt widget signal that starts the simulation.
//           There are TWO .cpp files for this class.
//           QSimStartSimulationNoGui.cpp contains standard C++ (non-Qt) methods to run simulation.
//           QSimStartSimulationGui.cpp contains Qt methods to display/interact with simulation.
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
#include "QSimStartSimulation.h"
#include "QSimGenericFunctions.h"
#include <QtCore>
#include <QtGui>

//------------------------------------------------------------------------------
namespace QSim {


//------------------------------------------------------------------------------
void  QSimStartSimulation::SlotStartSimulationFromMainApplicationWindow( )
{
#if 0
   // Create simulation window.
   QWidget simulationWindow( this->GetParentWidget(), Qt::Popup );
   simulationWindow.setWindowTitle( "Simulation window" );
   simulationWindow.setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding );

   // Create layout manager for simulation window,
   QVBoxLayout simulationWindowLayoutManager( &simulationWindow );

   // Create button to start simulation.
   QPushButton widgetPushButtonToStartSimulation( "Push button to start simulation", &simulationWindow );
   widgetPushButtonToStartSimulation.resize( 600, 180 );
   QObject::connect( &widgetPushButtonToStartSimulation, SIGNAL( clicked() ), this, SLOT( SlotStartSimulationFromThisWindowNoGui() ) );
   simulationWindowLayoutManager.addWidget( &widgetPushButtonToStartSimulation );

   // Labels are widgets that contain text and that can be formatted with simple HTML-style formatting.
   QLabel widgetLabel( "<h1><b><i>Hello</i></b> &nbsp;&nbsp; <font color=blue>world!</font></h1> <h2><b><font color=blue><br>Scott, Sherm, Ayman, Peter, Matt, Chand, Mark, <br>Ajay, Sam, Edith, Jennifer, Joy, Jessie, Paul, Melanie, ...</font color><b><br></h2>", &simulationWindow );
   widgetLabel.setAlignment( Qt::AlignHCenter );
   simulationWindowLayoutManager.addWidget( &widgetLabel );

   // Show the simulation window and all its children.
   simulationWindow.show();
   simulationWindow.repaint();
   SleepInMilliseconds( 2000 );

   // Possibly load libraries.
   // QLibrary simbodyLibrary( "Simbody" );
   // simbodyLibrary.load();
#endif
   // Call functions that contain standard C++ (non-Qt) methods to run simulation.
   this->SlotStartSimulationFromThisWindowNoGui();
}



//------------------------------------------------------------------------------
}  // End of namespace QSim



