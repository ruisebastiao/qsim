//-----------------------------------------------------------------------------
// File:     QSimRigidBodyPositionDialog.cpp
// Class:    QSimRigidBodyPositionDialog
// Parent:   QLabel
// Purpose:  Signals mouse event for QSimRigidBodyPositionDialog class.
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
#include "QSimRigidBodyPositionDialog.h"
#include "QSimRigidBodyTabWidget.h"


//------------------------------------------------------------------------------
namespace QSim {


//------------------------------------------------------------------------------
QSimRigidBodyPositionDialog::QSimRigidBodyPositionDialog() : QDialog(NULL)
{
   // Arrange the images in a grid with a little room between each image.
   this->setLayout( &myGridLayout );
   myGridLayout.setHorizontalSpacing( 8 );
   myGridLayout.setVerticalSpacing( 4 );

   // 0th row in dialog.
   myPositionLabel[0].setText( "<b>x = </b>" );
   myOrientationLabel[0].setText( "<b>Rx = </b>" );
   this->AddLabelInputLineSpaceLabelInputLine( 0 ) ;

   // 1st row in dialog.
   myPositionLabel[1].setText( "<b>y = </b>" );
   myOrientationLabel[1].setText( "<b>Ry = </b>" );
   this->AddLabelInputLineSpaceLabelInputLine( 1 ) ;

   // 2nd row in dialog.
   myPositionLabel[2].setText( "<b>z = </b>" );
   myOrientationLabel[2].setText( "<b>Rz = </b>" );
   this->AddLabelInputLineSpaceLabelInputLine( 2 ) ;
   
   // Add a vertical spacer to take up some vertical space.
   const unsigned int verticalSpacerPreferredWidth = 5;
   const unsigned int verticalSpacerPreferredHeight = 5;
   QSpacerItem* verticalSpacer = new QSpacerItem( verticalSpacerPreferredWidth, verticalSpacerPreferredHeight, QSizePolicy::Minimum, QSizePolicy::Minimum);
   myGridLayout.addItem( verticalSpacer, 3, 0 );

   // Add the OK and Cancel buttons.
   // myWidgetForOkAndCancelButtons.setParent( this );
   myWidgetForOkAndCancelButtons.setLayout( &myHorizontalBoxLayoutForOkAndCancelButtons ); 
   myOkButton.setText( QString("OK") );
   myCancelButton.setText( QString("Cancel") );
   myHorizontalBoxLayoutForOkAndCancelButtons.addWidget( &myOkButton );
   myHorizontalBoxLayoutForOkAndCancelButtons.addWidget( &myCancelButton );
   const unsigned int rowNumberForOkAndCancelButtons = 4;
   const unsigned int colNumberForOkAndCancelButtons = 1;
   const unsigned int colSpanForOkAndCancelButtons = 5;
   myGridLayout.addWidget( &myWidgetForOkAndCancelButtons, rowNumberForOkAndCancelButtons, colNumberForOkAndCancelButtons, colSpanForOkAndCancelButtons, Qt::AlignHCenter );

   // Add another vertical spacer to take up the remaining available space.
   verticalSpacer = new QSpacerItem( verticalSpacerPreferredWidth, verticalSpacerPreferredHeight, QSizePolicy::Minimum, QSizePolicy::Expanding );
   myGridLayout.addItem( verticalSpacer, 5, 0 );
#if 0
   // Add ability to upload a user-designated image file.
   myWidgetPushButtonToUploadImageFile.setParent(this);
   myWidgetPushButtonToUploadImageFile.setText( "Upload image file" );
   myWidgetPushButtonToUploadImageFile.resize( 300, 90 );
   myGridLayout.addWidget( &myWidgetPushButtonToUploadImageFile, startRowNumberforWidget, startColNumberForWidget, 1, spanColumns, Qt::AlignCenter );
   QObject::connect( &myWidgetPushButtonToUploadImageFile, SIGNAL( clicked() ), this, SLOT( OpenFileNameAndAddImageToLayout() ) );
#endif
}


//------------------------------------------------------------------------------
void   QSimRigidBodyPositionDialog::AddLabelInputLineSpaceLabelInputLine( const unsigned int rowNumber )
{
   // Ensure proper rowNumber on entry.
   if( rowNumber > 3 ) return;

   // Position label
   QLabel& positionLabel = myPositionLabel[ rowNumber ];
   positionLabel.setAlignment( Qt::AlignRight );
   positionLabel.setAlignment( Qt::AlignBottom );
   myGridLayout.addWidget( &positionLabel, rowNumber, 0 );

   // Position input line dialog box.
   QLineEdit& positionDialog = myPositionInputDialog[ rowNumber ];
   positionDialog.setMaxLength( 5 );
   positionDialog.setFrame( true );
   positionDialog.setText( "0.0" );
   myGridLayout.addWidget( &positionDialog, rowNumber, 1 );

   // Blank space
   QLabel* blankSpace = new QLabel( "  ", this );
   myGridLayout.addWidget( blankSpace, rowNumber, 2 );

   // Orientation label
   QLabel& orientationLabel = myOrientationLabel[ rowNumber ];
   orientationLabel.setAlignment( Qt::AlignRight );
   orientationLabel.setAlignment( Qt::AlignBottom );
   myGridLayout.addWidget( &orientationLabel, rowNumber, 3 );

   // Position input line dialog box.
   QLineEdit& orientationDialog = myOrientationInputDialog[ rowNumber ];
   orientationDialog.setMaxLength( 5 );
   orientationDialog.setText( "0.0" );
   myGridLayout.addWidget( &orientationDialog, rowNumber, 4 );

   // If this is a tab dialog and associated with another widget, hook slot from associated widget with signals from the label.
   // label.SetAssociatedWidgetAndConnectSignal( *myAssociatedWidgetIfTabDialog );
}



#if 0
//------------------------------------------------------------------------------
void  QSimRigidBodyPositionDialog::SetAssociatedWidgetAndConnectSignal( const QSimRigidBodyTabWidget& associatedWidgetToCatchSignal )
{
   myAssociatedWidgetToCatchSignal = &associatedWidgetToCatchSignal;
   QObject::connect( this, SIGNAL(ImageChangedSignalInQImageViewLabel(const QPixmap&)),  myAssociatedWidgetToCatchSignal, SLOT(TextureChangedSlot(const QPixmap&)) );
}


//------------------------------------------------------------------------------
bool  QSimRigidBodyPositionDialog::event( QEvent *e )
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
#endif


//------------------------------------------------------------------------------
}  // End of namespace QSim
//--------------------------------------------------------------------------

