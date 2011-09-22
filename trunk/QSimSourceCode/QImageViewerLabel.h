//-----------------------------------------------------------------------------
// File:     QImageViewerLabel.h
// Class:    QImageViewerLabel
// Parent:   QLabel
// Purpose:  Signals mouse event for QImageViewerDialog class.
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
#ifndef  QIMAGEVIEWERLABEL_H___ 
#define  QIMAGEVIEWERLABEL_H___
#include <QtCore>
#include <QtGui>
#include "CppStandardHeaders.h"


//------------------------------------------------------------------------------
namespace QSim {

// Forward declaration
class QSimRigidBodyTabWidget;


//-----------------------------------------------------------------------------
class QImageViewerLabel : public QLabel
{
   Q_OBJECT

public:
   // Constructors and destructors.
   QImageViewerLabel()  { myAssociatedWidgetToCatchSignal = NULL; }
  ~QImageViewerLabel()  {;}

   // Set associated widget to catch signal.
   void  SetAssociatedWidgetAndConnectSignal( const QSimRigidBodyTabWidget& associatedWidgetToCatchSignal );

   // Signals that connect to other signals or slots (no need to designate signals as private/protected/public).
signals:
   void  ImageChangedSignalInQImageViewLabel( const QPixmap& );

protected:
   // Override mouse events in QLabel class to handle user pressing mouse on label.
   bool event( QEvent *e );

   // Asociated QSimRigidBodyTabWidget to catch signal.
   const QSimRigidBodyTabWidget*  myAssociatedWidgetToCatchSignal;
};


//------------------------------------------------------------------------------
}  // End of namespace QSim
//--------------------------------------------------------------------------
#endif  // QIMAGEVIEWERLABEL_H___
//--------------------------------------------------------------------------

