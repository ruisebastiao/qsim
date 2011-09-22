//-----------------------------------------------------------------------------
// File:     QImageViewerDialog.h
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
#ifndef  QIMAGEVIEWERDIALOG_H___ 
#define  QIMAGEVIEWERDIALOG_H___
#include <QtCore>
#include <QtGui>
#include "CppStandardHeaders.h"
#include "QActionHelper.h"
#include "QImageViewerLabel.h"
#include "qgltexture2d.h"


//------------------------------------------------------------------------------
namespace QSim {

// Forward declaration
class QSimRigidBodyTabWidget;

//-----------------------------------------------------------------------------
class QImageViewerDialog : public QDialog
{
   Q_OBJECT

public:
   // Constructors and destructors.
   QImageViewerDialog();
  ~QImageViewerDialog()  {;}

   // Set associated widget to catch signal.
  void  SetAssociatedWidgetIfTabDialog( const QSimRigidBodyTabWidget& associatedWidgetIfTabDialog );

private slots:
   bool  OpenFileNameAndAddImageToLayout();

private:
   void  ScaleImage( double factor );
   bool  SetWidgetToLayout();
   bool  SetImageAndAddWidgetToLayoutFromQPixmap( const QPixmap& pixmap );
   bool  SetImageAndAddWidgetToLayoutFromQImage( const QImage& image )   { return image.isNull() ? false :  this->SetImageAndAddWidgetToLayoutFromQPixmap( QPixmap::fromImage(image) ); }
   bool  SetImageAndAddWidgetToLayoutFromImageFilename( const QString& pathToGraphicsResource )  { QImage image(pathToGraphicsResource);  return this->SetImageAndAddWidgetToLayoutFromQImage(image); }

   double scaleFactor;

   // Keep track of how many labels have been used so far.
   static const unsigned int myMaximumNumberOfImages = 80;
   QImageViewerLabel  myImages[ myMaximumNumberOfImages ];
   unsigned int myCurrentNumberOfImages;

   // Many images are built-in.
   static const QPixmap*  GetStaticPixmap( const unsigned int i );
   void  SetStaticImagesAsWidgetsInLayout()  { unsigned int i=0;  const QPixmap* pixmapi;   while( (pixmapi = QImageViewerDialog::GetStaticPixmap(i++)) != NULL )  this->SetImageAndAddWidgetToLayoutFromQPixmap(*pixmapi); } 

   // At bottom of layout, add ability to upload a file.

   // Associated widget if this dialog is part of a tab dialog box.
   const QSimRigidBodyTabWidget*  myAssociatedWidgetIfTabDialog;

   // Layout manager for this dialog.
   QGridLayout  myGridLayout;

   // Button to push for user to upload an image file.
   QPushButton  myWidgetPushButtonToUploadImageFile;

   // Get the current row or column number for the next image in the layout.
   static const unsigned int  myNumberOfItemsPerRowForLayout = 8;
   unsigned int  GetRowNumberForCurrentNumberOfImages()  { return myCurrentNumberOfImages / myNumberOfItemsPerRowForLayout; }
   unsigned int  GetColNumberForCurrentNumberOfImages()  { return myCurrentNumberOfImages % myNumberOfItemsPerRowForLayout; }
};


//------------------------------------------------------------------------------
}  // End of namespace QSim
//--------------------------------------------------------------------------
#endif  // QIMAGEVIEWERDIALOG_H___
//--------------------------------------------------------------------------

