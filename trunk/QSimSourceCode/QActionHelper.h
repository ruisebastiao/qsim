//-----------------------------------------------------------------------------
// File:     QActionHelper.h
// Class:    QActionHelper
// Parent:   QAction
// Purpose:  Utility helper class for populating QAction.
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
#ifndef  QACTIONHELPER_H___ 
#define  QACTIONHELPER_H___
#include <QtCore>
#include <QtGui>
#include "CppStandardHeaders.h"


//-----------------------------------------------------------------------------
namespace QSim {


//-----------------------------------------------------------------------------
class QActionHelper : public QAction
{
   Q_OBJECT

public:
   // Constructors and destructors.
   QActionHelper() : QAction(NULL) {;}
  ~QActionHelper() {;}

   //--------------------------------------------------------------------------
   void  AddActionHelper( const QString& textName, const QKeySequence& keySequenceShortcut, const char *pathToIconFileOrNull )  { this->AddActionHelper( textName, pathToIconFileOrNull );  this->setShortcut( keySequenceShortcut ); }
   void  AddActionHelper( const QString& textName, const char *pathToIconFileOrNull )
   {
      this->setText( textName );
      if( pathToIconFileOrNull && *pathToIconFileOrNull )
      {
         myActionIcon.addFile( pathToIconFileOrNull );
         if( !myActionIcon.isNull() )  this->setIcon( myActionIcon );
      }
   }

private:
   // Actions for edit menu.
   QIcon  myActionIcon;
    
};


//-----------------------------------------------------------------------------
}  // End of namespace QSim
//-----------------------------------------------------------------------------
#endif  // QACTIONHELPER_H___
//-----------------------------------------------------------------------------
