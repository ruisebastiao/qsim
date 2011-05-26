//-----------------------------------------------------------------------------
// File:     QSimGLWidget.h
// Class:    QSimGLWidget
// Parent:   QGLWidget
// Purpose:  Main widget for OpenQL.
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
#ifndef  QSIMGLWIDGET_H__ 
#define  QSIMGLWIDGET_H__
#include "CppStandardHeaders.h"
#include <QtCore>
#include <QtGui>
#include <QtOpenGL>


//------------------------------------------------------------------------------
namespace QSim {

// Forward declaration.
class QtLogo *logo;


// Note: Qt's QGLWidget helps display OpenGL graphics in a Qt application. 
// To use it, choose between using QPainter and standard OpenGL rendering commands.
//-----------------------------------------------------------------------------
class QSimGLWidget : public QGLWidget
{
    Q_OBJECT

public:
   // Constructors and destructors.
   QSimGLWidget( QWidget* parentWidget ) { this->setParent(parentWidget);}
  ~QSimGLWidget() {;}
public:

   QSize minimumSizeHint() const;
   QSize sizeHint() const;

public slots:
   void  SetXRotationAngle( const int angle ) {;}
   void  SetYRotationAngle( const int angle ) {;}
   void  SetZRotationAngle( const int angle ) {;}

signals:
   void  xRotationAngleChanged( const int angle );
   void  yRotationAngleChanged( const int angle );
   void  zRotationAngleChanged( const int angle );

protected:
   // Override parent class QGLWidget virtual functions to perform typical OpenGL tasks.
   // initializeGL: Sets up the OpenGL rendering context, defines display lists, etc. Gets called once before the first time resizeGL() or paintGL() is called.
   // paintGL:      Renders the OpenGL scene.  Gets called whenever the widget needs to be updated.
   // resizeGL:     Sets up the OpenGL viewport, projection, etc. Gets called whenever the widget has been resized (or shown for the first time).
   void  initializeGL();
   void  paintGL();
   void  resizeGL( int width, int height );

   void  MousePressEvent( QMouseEvent *event );
   void  MouseMoveEvent( QMouseEvent *event );

private:
   QtLogo *logo;
   int xRot;
   int yRot;
   int zRot;
   QPoint lastPos;
   QColor qtGreen;
   QColor qtPurple;
};


//------------------------------------------------------------------------------
}  // End of namespace QSim


//--------------------------------------------------------------------------
#endif  // QSIMGLWIDGET_H__
//--------------------------------------------------------------------------

