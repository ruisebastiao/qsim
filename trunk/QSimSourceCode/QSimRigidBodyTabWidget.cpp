//-----------------------------------------------------------------------------
// File:     QSimRigidBodyTabWidget.cpp
// Class:    QSimRigidBodyTabWidget
// Parent:   QTabWidget
// Purpose:  Allow user to change properties of a rigid body.
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
#include "QSimRigidBodyTabWidget.h"
#include "QSimSceneNode.h"
#include "QSimGLViewWidget.h"


//------------------------------------------------------------------------------
namespace QSim {


//------------------------------------------------------------------------------
void  QSimRigidBodyTabWidget::ShowRigidBodyTabWidget( QSimSceneNode& boundToSceneNode )
{
   // Only need to populate this once.
   if( myBoundToSceneNode == NULL )
   {
      // Use object name and ID for title of dialogue box.
      QString objectNameAndId;
      (myBoundToSceneNode = &boundToSceneNode)->GetObjectNameAndObjectIdInsideSquareBrackets( objectNameAndId );
      this->setWindowTitle( objectNameAndId );

      // Add color properties (get current color from scene node.
      const QColor diffuseColor = myBoundToSceneNode->GetMaterialStandard().diffuseColor();
      myTabColorDialog.SetCurrentColor( diffuseColor );
      myTabWidget.addTab( &myTabColorDialog,  tr("Color") );
      QObject::connect( &myTabColorDialog,  SIGNAL(currentColorChanged(const QColor&)), this, SLOT(ColorChangedSlot(const QColor&)) );

      // Add texture properties tab.
      myTabWidget.addTab( &myTabTextureDialog, tr("Texture") );
      myTabTextureDialog.SetAssociatedWidgetIfTabDialog( *this );

      // Add geometry properties
      myTabWidget.addTab( &myTabRigidBodyGeometryDialog, tr("Geometry") );

      // Add position properties.
      myTabWidget.addTab( &myTabRigidBodyPositionDialog, tr("Position") );
      
      // Add velocity properties.
      myTabWidget.addTab( &myTabRigidBodyVelocityDialog, tr("Velocity") );

      // Create a layout manager and know that this takes ownership of the layout manager (calls its destructor, etc.)
      QVBoxLayout *mainLayout = new QVBoxLayout;
      mainLayout->addWidget( &myTabWidget );
      mainLayout->setSizeConstraint( QLayout::SetFixedSize );
      this->setLayout( mainLayout );

      // Even though dialog box is not modal, keep the dialog box on the top.
      this->setWindowFlags( Qt::WindowStaysOnTopHint );
   }

   // Has already been populated and shown - only need to reshow it.
   else
   {
      this->setVisible( true );
   }

   // Show this dialogue box.
   this->show();
   // this->repaint();
}


//------------------------------------------------------------------------------
void  QSimRigidBodyTabWidget::ColorChangedSlot( const QColor& color )
{
   // Make a copy of the material as it currently exists.
   QSimMaterialType newMaterial( myBoundToSceneNode->GetMaterialStandard() );

   // Change the relevant properties.
   newMaterial.setDiffuseColor( color );

   // Reset the material so it reflects the change in color.
   myBoundToSceneNode->SetMaterialStandard( newMaterial );

   // Repaint so user instantly sees changes.
   myBoundToSceneNode->GetSceneNodeQSimGLViewWidget().updateGL();
}


//------------------------------------------------------------------------------
void  QSimRigidBodyTabWidget::TextureChangedSlot( const QPixmap& pixmap )
{
   if( !pixmap.isNull() )
   {
      QImage image = pixmap.toImage();
      if( !image.isNull() )
      {
         // Add texture map.
         this->SetTexture( image );

         // Repaint so user instantly sees changes.
         myBoundToSceneNode->GetSceneNodeQSimGLViewWidget().updateGL();
      }
   }
}


//------------------------------------------------------------------------------
}  // End of namespace QSim


