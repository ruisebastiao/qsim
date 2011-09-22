//-----------------------------------------------------------------------------
// File:     QSimRigidBodyPositionDialog.h
// Class:    QSimRigidBodyPositionDialog
// Parent:   QDialog
// Purpose:  Dialog to modify existing geometry for an object. 
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
#ifndef  QSIMRIGIDBODYPOSITIONDIALOG_H___ 
#define  QSIMRIGIDBODYPOSITIONDIALOG_H___
#include <QtCore>
#include <QtGui>
#include "CppStandardHeaders.h"
#include "QActionHelper.h"
#include "QImageViewerLabel.h"
#include "qgltexture2d.h"


//------------------------------------------------------------------------------
namespace QSim {


//-----------------------------------------------------------------------------
class QSimRigidBodyPositionDialog : public QDialog
{
   Q_OBJECT

public:
   // Constructors and destructors.
   QSimRigidBodyPositionDialog();
  ~QSimRigidBodyPositionDialog()  {;}

private:

   // Add position label, line edit input box, orientation label, line edit input box.
   void   AddLabelInputLineSpaceLabelInputLine( const unsigned int rowNumber );

   // Layout manager for this dialog.
   QGridLayout  myGridLayout;

   // Input for x,y,z position and Euler BodyXYZ angles.
   QLabel    myPositionLabel[3];
   QLabel    myOrientationLabel[3];
   QLineEdit myPositionInputDialog[3];
   QLineEdit myOrientationInputDialog[3];

};


//------------------------------------------------------------------------------
}  // End of namespace QSim
//--------------------------------------------------------------------------
#endif  // QSIMRIGIDBODYPOSITIONDIALOG_H___
//--------------------------------------------------------------------------

