//-----------------------------------------------------------------------------
// File:     QImageViewerDialog.cpp
// Class:    QImageViewerDialog
// Parent:   QDialog
// Purpose:  Selects an image from built-in images or file.
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
#include "QImageViewerDialog.h"


//------------------------------------------------------------------------------
namespace QSim {


//------------------------------------------------------------------------------
QImageViewerDialog::QImageViewerDialog() : QDialog(NULL)
{
   // Initialize class data.
   myAssociatedWidgetIfTabDialog = NULL;

   // Arrange the images in a grid with a little room between each image.
   this->setLayout( &myGridLayout );
   myGridLayout.setSpacing( 1 );

   // Initialize the number of images in the layout to 0.
   myCurrentNumberOfImages = 0;

   // First image allows the user to select no texture.
   QString noTextureString( "<br><b>None</b>" );
   myImages[0].setText( noTextureString );
   this->SetWidgetToLayout();

   // The next images are built-in (stored in the program's resources).
   this->SetStaticImagesAsWidgetsInLayout();

   // Add ability to upload a user-designated image file.
   myWidgetPushButtonToUploadImageFile.setParent(this);
   myWidgetPushButtonToUploadImageFile.setText( "Upload image file" );
   myWidgetPushButtonToUploadImageFile.resize( 300, 90 );
   const unsigned int  currentRowNumber = this->GetRowNumberForCurrentNumberOfImages();
   const unsigned int  currentColNumber = this->GetColNumberForCurrentNumberOfImages();
   const unsigned int  startRowNumberforWidget = currentRowNumber + (currentColNumber == 0 ? 1 : 2);
   const unsigned int  startColNumberForWidget = 2;
   const unsigned int  spanColumns = myNumberOfItemsPerRowForLayout - 2*startColNumberForWidget;
   myGridLayout.addWidget( &myWidgetPushButtonToUploadImageFile, startRowNumberforWidget, startColNumberForWidget, 1, spanColumns, Qt::AlignCenter );
   QObject::connect( &myWidgetPushButtonToUploadImageFile, SIGNAL( clicked() ), this, SLOT( OpenFileNameAndAddImageToLayout() ) );

   // Resize the dialog which resizes the images so they fit comfortably on screen.
   this->resize( 500, 400 );
}


//------------------------------------------------------------------------------
const QPixmap*  QImageViewerDialog::GetStaticPixmap( const unsigned int i )
{
   static unsigned int myNumberOfStaticPixmaps = 0;
   static QPixmap      myStaticPixmaps[ 50 ];

   // First call to this method creates and stores all the QPixmaps.
   if( myNumberOfStaticPixmaps == 0 )
   {
      // Create a suitably size array of names.
      const char*  imageFilenames[ 50 ];
      unsigned int numberOfFiles = 0;

      // These images are built-in (although they are huge and should be down-scaled).
      imageFilenames[ numberOfFiles++ ] =  ":/TextureGraphics/TextureBlueRays.jpg";
      imageFilenames[ numberOfFiles++ ] =  ":/TextureGraphics/TextureBlueSky.jpg";
      imageFilenames[ numberOfFiles++ ] =  ":/TextureGraphics/TextureSkyBlueWithClouds.jpg";
      imageFilenames[ numberOfFiles++ ] =  ":/TextureGraphics/TexturePoolWater.jpg";
      imageFilenames[ numberOfFiles++ ] =  ":/TextureGraphics/TextureSeaBed.jpg";
      imageFilenames[ numberOfFiles++ ] =  ":/TextureGraphics/TextureGrassAndSky.jpg";
      imageFilenames[ numberOfFiles++ ] =  ":/TextureGraphics/TextureGreenGrassLong.jpg";
      imageFilenames[ numberOfFiles++ ] =  ":/TextureGraphics/TextureGreenGrassShort.jpg";
      imageFilenames[ numberOfFiles++ ] =  ":/TextureGraphics/TexturePalmLeaf.jpg";
      imageFilenames[ numberOfFiles++ ] =  ":/TextureGraphics/TextureGreenHedge.jpg";
      imageFilenames[ numberOfFiles++ ] =  ":/TextureGraphics/TextureGreenMoss.jpg";
      imageFilenames[ numberOfFiles++ ] =  ":/TextureGraphics/TextureFlowerGarden.jpg";
      imageFilenames[ numberOfFiles++ ] =  ":/TextureGraphics/TextureRedTulips.jpg";
      imageFilenames[ numberOfFiles++ ] =  ":/TextureGraphics/TextureOranges.jpg";
      imageFilenames[ numberOfFiles++ ] =  ":/TextureGraphics/TextureTreesPinkBloom.jpg";
      imageFilenames[ numberOfFiles++ ] =  ":/TextureGraphics/TextureSunsetSerengeti.jpg";
      imageFilenames[ numberOfFiles++ ] =  ":/TextureGraphics/TextureMapleLeaf.jpg";
      imageFilenames[ numberOfFiles++ ] =  ":/TextureGraphics/TextureWarmBackground.jpg";
      imageFilenames[ numberOfFiles++ ] =  ":/TextureGraphics/TextureRedAbstract1.jpg";
      imageFilenames[ numberOfFiles++ ] =  ":/TextureGraphics/TextureRedAbstract2.jpg";
      imageFilenames[ numberOfFiles++ ] =  ":/TextureGraphics/TexturePinkFeather.jpg";
      imageFilenames[ numberOfFiles++ ] =  ":/TextureGraphics/TextureRainbowAbstract.jpg";
      imageFilenames[ numberOfFiles++ ] =  ":/TextureGraphics/TextureFire1.jpg";
      imageFilenames[ numberOfFiles++ ] =  ":/TextureGraphics/TextureFire2.jpg";
      imageFilenames[ numberOfFiles++ ] =  ":/TextureGraphics/TextureIceCubes.jpg";
      imageFilenames[ numberOfFiles++ ] =  ":/TextureGraphics/TextureSnow1.jpg";
      imageFilenames[ numberOfFiles++ ] =  ":/TextureGraphics/TextureSnow2.jpg";
      imageFilenames[ numberOfFiles++ ] =  ":/TextureGraphics/TextureSand.jpg";
      imageFilenames[ numberOfFiles++ ] =  ":/TextureGraphics/TextureSoil.jpg";
      imageFilenames[ numberOfFiles++ ] =  ":/TextureGraphics/TextureSoilCracked.jpg";
      imageFilenames[ numberOfFiles++ ] =  ":/TextureGraphics/TextureBrickWall1.jpg";
      imageFilenames[ numberOfFiles++ ] =  ":/TextureGraphics/TextureBrickWall2.jpg";
      imageFilenames[ numberOfFiles++ ] =  ":/TextureGraphics/TextureStoneWall1.jpg";
      imageFilenames[ numberOfFiles++ ] =  ":/TextureGraphics/TextureStoneWall2.jpg";
      imageFilenames[ numberOfFiles++ ] =  ":/TextureGraphics/TextureWoodBoardwalk.jpg";
      imageFilenames[ numberOfFiles++ ] =  ":/TextureGraphics/TextureWoodOak.jpg";
      imageFilenames[ numberOfFiles++ ] =  ":/TextureGraphics/TextureWoodGrain.jpg";
      imageFilenames[ numberOfFiles++ ] =  ":/TextureGraphics/TextureWoodSlats.jpg";
      imageFilenames[ numberOfFiles++ ] =  ":/TextureGraphics/TextureWoodWalnut.jpg";
      imageFilenames[ numberOfFiles++ ] =  ":/TextureGraphics/TexturePaperCrumpled.jpg";
      imageFilenames[ numberOfFiles++ ] =  ":/TextureGraphics/TexturePaperRough.jpg";
      imageFilenames[ numberOfFiles++ ] =  ":/TextureGraphics/TexturePaperSmooth.jpg";
      imageFilenames[ numberOfFiles++ ] =  ":/TextureGraphics/TextureCanvasMaterial.jpg";
      imageFilenames[ numberOfFiles++ ] =  ":/TextureGraphics/TextureMetalChain.jpg";
      imageFilenames[ numberOfFiles++ ] =  ":/TextureGraphics/TextureMetalPebbled.jpg";
      imageFilenames[ numberOfFiles++ ] =  ":/TextureGraphics/TextureSolarPanels.jpg";
      imageFilenames[ numberOfFiles++ ] =  ":/TextureGraphics/TextureChocolate.jpg";
      imageFilenames[ numberOfFiles++ ] =  ":/TextureGraphics/TextureSoccerBall.jpg";
      imageFilenames[ numberOfFiles++ ] =  ":/MiscImages/QSimLogo.jpg";

      // Increment myNumberOfStaticPixmaps if the image loaded propertly, otherwise reuse the current array element again.
      for( unsigned int fileNumber=0;  fileNumber < numberOfFiles;  fileNumber++ )
      {
         QString imageFilenameAsString( imageFilenames[fileNumber] );
         const bool loadWasSuccessful = myStaticPixmaps[ myNumberOfStaticPixmaps ].load( imageFilenameAsString );
         if( loadWasSuccessful ) myNumberOfStaticPixmaps++;
      }
   }

   // Return NULL if i is out of range.
   return i < myNumberOfStaticPixmaps ? &myStaticPixmaps[i] : NULL;
}


//------------------------------------------------------------------------------
bool  QImageViewerDialog::OpenFileNameAndAddImageToLayout()
{
   // Request an image file from the user.
   QString fileName = QFileDialog::getOpenFileName( this, tr("Open File"), QDir::currentPath() );
   if( fileName.isEmpty() ) return false;

   // Try to process the image file designated by the user.
   const bool retValue = this->SetImageAndAddWidgetToLayoutFromImageFilename( fileName );
   if( retValue ) this->resize( 500, 400 );
   else  QMessageBox::information( this, tr("Image Viewer"), tr("Cannot load %1.").arg(fileName) );
   return retValue;
}


//------------------------------------------------------------------------------
void QImageViewerDialog::ScaleImage( double factor )
{
   Q_ASSERT( myImages[0].pixmap() );
   scaleFactor *= factor;
   myImages[0].resize( scaleFactor * myImages[0].pixmap()->size() );
}


//------------------------------------------------------------------------------
void  QImageViewerDialog::SetAssociatedWidgetIfTabDialog( const QSimRigidBodyTabWidget& associatedWidgetIfTabDialog )
{
   myAssociatedWidgetIfTabDialog = &associatedWidgetIfTabDialog;
   for( unsigned int i=0;  i<myCurrentNumberOfImages;  i++ )
   {
      QImageViewerLabel& label = myImages[ i ];
      label.SetAssociatedWidgetAndConnectSignal( associatedWidgetIfTabDialog );
   }
}


//------------------------------------------------------------------------------
bool  QImageViewerDialog::SetImageAndAddWidgetToLayoutFromQPixmap( const QPixmap& pixmap )
{
   if( pixmap.isNull() || myCurrentNumberOfImages >= myMaximumNumberOfImages ) return false;
   myImages[ myCurrentNumberOfImages ].setPixmap( pixmap );
   return this->SetWidgetToLayout();
}


//------------------------------------------------------------------------------
bool  QImageViewerDialog::SetWidgetToLayout()
{
   // Do not add another widget if the array has been exceeded.
   if( myCurrentNumberOfImages >= myMaximumNumberOfImages ) return false;

   QImageViewerLabel& label = myImages[ myCurrentNumberOfImages ];
   label.setAlignment( Qt::AlignHCenter );
   label.setBackgroundRole( QPalette::Base );
   label.setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
   label.setScaledContents( true );

   // If this is a tab dialog and associatd with another widget, hook slot from associated widget with signals from the label.
   if( myAssociatedWidgetIfTabDialog )
      label.SetAssociatedWidgetAndConnectSignal( *myAssociatedWidgetIfTabDialog );

   // Determine which row/column gets the next label.
   myGridLayout.addWidget( &label, this->GetRowNumberForCurrentNumberOfImages(), this->GetColNumberForCurrentNumberOfImages() );

   // Increment the number of images that are currently in play.
   ++myCurrentNumberOfImages;

   return true;
}


//------------------------------------------------------------------------------
}  // End of namespace QSim
//--------------------------------------------------------------------------

