//-----------------------------------------------------------------------------
// File:     QSimMaterialType.h
// Class:    QSimMaterialType  
// Parents:  QGLMaterial 
// Purpose:  Standard material effects for QSim	 (e.g., metal, wood, china)
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
#ifndef  QSIMMATERIALTYPE_H__ 
#define  QSIMMATERIALTYPE_H__
#include <QtCore>
#include <QtGui>
#include <QtOpenGL>
#include "qglmaterial.h"


//------------------------------------------------------------------------------
namespace QSim {



//------------------------------------------------------------------------------
class QSimMaterialType : public QGLMaterial
{
   Q_OBJECT

public:
   QSimMaterialType( QObject* parent, const QColor& ambientColorWhatYouSeeInShadow, const QColor& diffuseColorWhatYouSeeInDirectLight, const QColor& specularColorImportantIfShiny, const qreal shininessBetween0And128 );
  ~QSimMaterialType()  {;}

   // Some standard materials for objects (built-in).
   static QSimMaterialType&  GetChinaMaterialStandard(); 
   static QSimMaterialType&  GetChinaMaterialHighlight(); 
   static QSimMaterialType&  GetMetalMaterialStandard(); 
   static QSimMaterialType&  GetMetalMaterialHighlight(); 
};


//------------------------------------------------------------------------------
}  // End of namespace QSim
//--------------------------------------------------------------------------
#endif  // QSIMMATERIALTYPE_H__
//--------------------------------------------------------------------------
