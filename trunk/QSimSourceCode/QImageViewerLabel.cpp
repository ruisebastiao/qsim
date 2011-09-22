//-----------------------------------------------------------------------------
// File:     QImageViewerLabel.cpp
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
#include "QImageViewerLabel.h"
#include "QSimRigidBodyTabWidget.h"


//------------------------------------------------------------------------------
namespace QSim {


//------------------------------------------------------------------------------
void  QImageViewerLabel::SetAssociatedWidgetAndConnectSignal( const QSimRigidBodyTabWidget& associatedWidgetToCatchSignal )
{
   myAssociatedWidgetToCatchSignal = &associatedWidgetToCatchSignal;
   QObject::connect( this, SIGNAL(ImageChangedSignalInQImageViewLabel(const QPixmap&)),  myAssociatedWidgetToCatchSignal, SLOT(TextureChangedSlot(const QPixmap&)) );
}


//------------------------------------------------------------------------------
bool  QImageViewerLabel::event( QEvent *e )
{
   // Process parent event (if any).
   bool retValue = QLabel::event(e);
   if( e->type() == QEvent:: MouseButtonPress )
   {
      if( myAssociatedWidgetToCatchSignal != NULL )
      {
         const QPixmap *pixmapForThisLabel = this->pixmap();
         if( pixmapForThisLabel && !pixmapForThisLabel->isNull() )
            emit ImageChangedSignalInQImageViewLabel( *pixmapForThisLabel );
         retValue = true;
      }
   }
   return retValue;
}


//------------------------------------------------------------------------------
}  // End of namespace QSim
//--------------------------------------------------------------------------

