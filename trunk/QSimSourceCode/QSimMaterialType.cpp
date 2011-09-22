//-----------------------------------------------------------------------------
// File:     QSimMaterialType.cpp
// Class:    QSimMaterialType
// Parents:  QGLMaterial
// Purpose:  Standard material effects for QSim  (e.g., metal, wood, china)
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
#include "QSimMaterialType.h"


//------------------------------------------------------------------------------
namespace QSim {


//------------------------------------------------------------------------------
const QSimMaterialType&  QSimMaterialType::GetChinaMaterialStandard()   { static QSimMaterialType material( QColor(192,150,128), QColor(192,150,128), QColor( 60, 60, 60), 128 );  return material; }
const QSimMaterialType&  QSimMaterialType::GetChinaMaterialHighlight()  { static QSimMaterialType material( QColor(255,192,  0), QColor(255,192,  0), QColor( 60, 60,  0), 128 );  return material; }
const QSimMaterialType&  QSimMaterialType::GetMetalMaterialStandard()   { static QSimMaterialType material( QColor(255,255,255), QColor(150,150,150), QColor(255,255,255), 128 );  return material; }
const QSimMaterialType&  QSimMaterialType::GetMetalMaterialHighlight()  { static QSimMaterialType material( QColor(255,255, 96), QColor(150,150, 96), QColor(255,255,255), 128 );  return material; }


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


