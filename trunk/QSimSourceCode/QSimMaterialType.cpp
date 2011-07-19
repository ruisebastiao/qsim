//-----------------------------------------------------------------------------
// File:     QSimMaterialType.cpp
// Class:    QSimMaterialType
// Parents:  QGLMaterial
// Purpose:  Standard material effects for QSim  (e.g., metal, wood, china)
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
#include "QSimMaterialType.h"


//------------------------------------------------------------------------------
namespace QSim {


//------------------------------------------------------------------------------
QSimMaterialType::QSimMaterialType( QObject* parent, const QColor& ambientColorWhatYouSeeInShadow, const QColor& diffuseColorWhatYouSeeInDirectLight, const QColor& specularColorImportantIfShiny, const qreal shininessBetween0And128 ) : QGLMaterial(parent)
{
   this->setAmbientColor( ambientColorWhatYouSeeInShadow );
   this->setDiffuseColor( diffuseColorWhatYouSeeInDirectLight );
   this->setSpecularColor( specularColorImportantIfShiny );
   this->setShininess( shininessBetween0And128 );
}


//------------------------------------------------------------------------------
QSimMaterialType&  QSimMaterialType::GetChinaMaterialStandard()   { static QSimMaterialType material( NULL, QColor(192,150,128), QColor(192,150,128), QColor( 60, 60, 60), 128 );  return material; }
QSimMaterialType&  QSimMaterialType::GetChinaMaterialHighlight()  { static QSimMaterialType material( NULL, QColor(255,192,  0), QColor(255,192,  0), QColor( 60, 60,  0), 128 );  return material; }
QSimMaterialType&  QSimMaterialType::GetMetalMaterialStandard()   { static QSimMaterialType material( NULL, QColor(255,255,255), QColor(150,150,150), QColor(255,255,255), 128 );  return material; }
QSimMaterialType&  QSimMaterialType::GetMetalMaterialHighlight()  { static QSimMaterialType material( NULL, QColor(255,255, 96), QColor(150,150, 96), QColor(255,255,255), 128 );  return material; }


//------------------------------------------------------------------------------
}  // End of namespace QSim


//*********************************************************************************
//*********************************************************************************
#if 0
   china = new QGLMaterial(this);
   china->setAmbientColor(QColor(192, 150, 128));
   china->setSpecularColor(QColor(60, 60, 60));
   china->setShininess(128);

   chinaHighlight = new QGLMaterial(this);
   chinaHighlight->setAmbientColor(QColor(255, 192, 0));
   chinaHighlight->setSpecularColor(QColor(60, 60, 0));
   chinaHighlight->setShininess(128);

   metal = new QGLMaterial(this);
   metal->setAmbientColor(QColor(255, 255, 255));
   metal->setDiffuseColor(QColor(150, 150, 150));
   metal->setSpecularColor(QColor(255, 255, 255));
   metal->setShininess(128);

   metalHighlight = new QGLMaterial(this);
   metalHighlight->setAmbientColor(QColor(255, 255, 96));
   metalHighlight->setDiffuseColor(QColor(150, 150, 96));
   metalHighlight->setSpecularColor(QColor(255, 255, 255));
   metalHighlight->setShininess(128);

   // Purely cosmetic effects (skip this if you like all white).
   // Also, should probably using a palette here.
   QGLMaterial *china = new QGLMaterial(this);
   china->setAmbientColor(  QColor(192, 150, 128) );
   china->setSpecularColor( QColor(60, 60, 60) );
   china->setShininess( 128 );
   sceneNode->setMaterial(china);
   sceneNode->setEffect( QGL::LitMaterial );
#endif
//*********************************************************************************
//*********************************************************************************


