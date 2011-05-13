//-----------------------------------------------------------------------------
// File:     QSimStartSimulation.h
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
#include "CppStandardHeaders.h"
#include <QObject>


//------------------------------------------------------------------------------
#ifndef  OPENSIMQTSTARTSIMULATION_H__ 
#define  OPENSIMQTSTARTSIMULATION_H__


//------------------------------------------------------------------------------
namespace QSim {

// The following ANSI-standard C++ function separates the Qt portion of this code
// with the portion of the code that does the simulation-mathematics.
bool  StartAndRunSimulationMathematicsEngineNoGui( );

//-----------------------------------------------------------------------------
class QSimStartSimulation : public QObject
{
   Q_OBJECT

public:
   // Constructors and destructors.
   QSimStartSimulation( QWidget* parentWidget ) { this->SetParentWidget(parentWidget);}
  ~QSimStartSimulation() {;}

public slots:
   void  SlotStartSimulationFromMainApplicationWindow();  
   void  SlotStartSimulationFromThisWindowNoGui()  { StartAndRunSimulationMathematicsEngineNoGui(); }

private:
   // Disable default constructors and/or destructors unless they are needed.
   QSimStartSimulation();

   // Private Get/Set methods for class data.
   QWidget*  GetParentWidget()                         { return myParentWidget; }
   QWidget*  SetParentWidget( QWidget *parentWidget )  { return myParentWidget = parentWidget; }

   // Class data.
   QWidget*  myParentWidget;
};



//------------------------------------------------------------------------------
}  // End of namespace QSim


//--------------------------------------------------------------------------
#endif  // OPENSIMQTSTARTSIMULATION_H__
//--------------------------------------------------------------------------
