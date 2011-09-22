//-----------------------------------------------------------------------------
// File:     QSimStartSimulation.h
// Class:    QSimStartSimulation
// Parent:   QObject
// Purpose:  Catches the Qt widget signal that starts the simulation.
//           There are TWO .cpp files for this class.
//           QSimStartSimulationNoGui.cpp contains standard C++ (non-Qt) methods to run simulation.
//           QSimStartSimulationGui.cpp contains Qt methods to display/interact with simulation.
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
#ifndef  OPENSIMQTSTARTSIMULATION_H__ 
#define  OPENSIMQTSTARTSIMULATION_H__
#include <QObject>
#include "CppStandardHeaders.h"


//------------------------------------------------------------------------------
namespace QSim {

// The following ANSI-standard C++ function separates the Qt portion of this code
// with the portion of the code that does the simulation-mathematics.
bool  StartAndRunSimulationMathematicsEngineNoGui( const bool trueForSimbodyFalseForOpenSimApi );


//-----------------------------------------------------------------------------
class QSimStartSimulation : public QObject
{
   Q_OBJECT

public:
   // Constructors and destructors.
   QSimStartSimulation( QObject* parentWidget ) { this->setParent(parentWidget);}
  ~QSimStartSimulation() {;}

public slots:
   void  SlotStartSimulationFromThisWindowNoGuiSimbody()     { StartAndRunSimulationMathematicsEngineNoGui( true  ); }
   void  SlotStartSimulationFromThisWindowNoGuiOpenSimApi()  { StartAndRunSimulationMathematicsEngineNoGui( false ); }

private:
   // Disable default constructors and/or destructors unless they are needed.
   QSimStartSimulation();

};



//------------------------------------------------------------------------------
}  // End of namespace QSim
//--------------------------------------------------------------------------
#endif  // OPENSIMQTSTARTSIMULATION_H__
//--------------------------------------------------------------------------
