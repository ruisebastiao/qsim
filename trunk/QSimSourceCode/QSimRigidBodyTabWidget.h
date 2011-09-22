//-----------------------------------------------------------------------------
// File:     QSimRigidBodyTabWidget.h
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
#ifndef  QSIMRIGIDBODYTABWIDGET_H___ 
#define  QSIMRIGIDBODYTABWIDGET_H___
#include <QtCore>
#include <QtGui>
#include "CppStandardHeaders.h"
#include "QActionHelper.h"
#include "QImageViewerDialog.h"
#include "QSimRigidBodyGeometryDialog.h"
#include "QSimRigidBodyPositionDialog.h"
#include "QSimRigidBodyVelocityDialog.h"


//------------------------------------------------------------------------------
namespace QSim {

// Forward declarations.
class QSimSceneNode;


//-----------------------------------------------------------------------------
class TabPropertiesColorDialog : public QColorDialog
{
   Q_OBJECT

public:
   // Constructors and destructors.
   TabPropertiesColorDialog() : QColorDialog(NULL)  { this->setOption( QColorDialog::NoButtons, true );   this->SetCurrentColor( QColor(100,100,255,123) ); }
  ~TabPropertiesColorDialog()  {;}

   // Set the current color based on an object's color.
   // One of the constructors of QColor is QColor(red,green,blue,transparent) where
   // red, green, blue are set with integers from 0 to 255 and transparent is 0 (fully transparent) to 255 (fully opaque).
   void    SetCurrentColor( const QColor color )  { this->setCurrentColor(color); }
   QColor  GetCurrentColor()                      { return this->currentColor(); }
};


//-----------------------------------------------------------------------------
class TabPropertiesGeometryDialog : public QColorDialog
{
   Q_OBJECT

public:
   // Constructors and destructors.
   TabPropertiesGeometryDialog() : QColorDialog(NULL) { this->InitializeTabGeometryDialog(); }
  ~TabPropertiesGeometryDialog()                      {;}

private:
   // Override some of the default color dialog options.
   void InitializeTabGeometryDialog()  {;}
};


//-----------------------------------------------------------------------------
class QSimRigidBodyTabWidget : public QDialog
{
   Q_OBJECT

public:
   // Constructors and destructors.
   QSimRigidBodyTabWidget() : QDialog(NULL)  { this->InitializeQSimRigidBodyTabWidget(); }
  ~QSimRigidBodyTabWidget()                  { this->InitializeQSimRigidBodyTabWidget(); }

   // Show this dialog box.
   void  ShowRigidBodyTabWidget( QSimSceneNode& boundToSceneNode );
   void  HideRigidBodyTabWidget()  { this->setVisible(false); }

   // Get the texture associated with this object.
   const QGLTexture2D*  GetTextureOrNullIfEmpty() const  { return myGLTexture.isNull() || !myGLTexture.bind() ? NULL : &myGLTexture; }

private slots:
   void  ColorChangedSlot( const QColor& color );
   void  TextureChangedSlot( const QPixmap& pixmap );

private:
   // Initialize class data.
   void  InitializeQSimRigidBodyTabWidget()  { myBoundToSceneNode = NULL; }

   // Keep track of associated scene node.
   QSimSceneNode*  myBoundToSceneNode;

   // This dialogue box contains a QTabWidget, which itself contains tabs.
   QTabWidget                   myTabWidget;
   TabPropertiesColorDialog     myTabColorDialog;
   QImageViewerDialog           myTabTextureDialog;
   QSimRigidBodyGeometryDialog  myTabRigidBodyGeometryDialog;
   QSimRigidBodyPositionDialog  myTabRigidBodyPositionDialog;
   QSimRigidBodyVelocityDialog  myTabRigidBodyVelocityDialog;

   // Image associated with the current object (maybe be empty/null).
   QGLTexture2D  myGLTexture;
   const QGLTexture2D*  SetTexture( const QImage& image )  { myGLTexture.setImage(image);  return this->GetTextureOrNullIfEmpty(); }
};


//------------------------------------------------------------------------------
}  // End of namespace QSim
//--------------------------------------------------------------------------
#endif  // QSIMRIGIDBODYTABWIDGET_H___
//--------------------------------------------------------------------------
