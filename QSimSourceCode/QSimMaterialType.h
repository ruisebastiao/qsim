//-----------------------------------------------------------------------------
// File:     QSimMaterialType.h
// Class:    QSimMaterialType  
// Parents:  QGLMaterial 
// Purpose:  Standard material effects for QSim	 (e.g., metal, wood, china)
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
   // Constructors/destructors
   QSimMaterialType() : QGLMaterial(NULL)  { this->SetQSimMaterialType( QSimMaterialType::GetChinaMaterialStandard() ); }
   QSimMaterialType( const QSimMaterialType& materialToCopy ) : QGLMaterial(NULL)  { this->SetQSimMaterialType( materialToCopy ); }  
   QSimMaterialType( const QColor& ambientColorWhatYouSeeInShadow, const QColor& diffuseColorWhatYouSeeInDirectLight, const QColor& specularColorImportantIfShiny, const qreal shininessBetween0And128 ) : QGLMaterial(NULL)  { this->SetQSimMaterialType( ambientColorWhatYouSeeInShadow, diffuseColorWhatYouSeeInDirectLight, specularColorImportantIfShiny, shininessBetween0And128 ); }
  ~QSimMaterialType()  {;}

   // Set material properties from another QSimMaterialType.
   QSimMaterialType&  SetQSimMaterialType( const QGLMaterial& materialToCopy )  { return this->SetQSimMaterialType( materialToCopy.ambientColor(), materialToCopy.diffuseColor(), materialToCopy.specularColor(), materialToCopy.shininess() ); }

   // Set material properties individually.
   QSimMaterialType&  SetQSimMaterialType( const QColor& ambientColorWhatYouSeeInShadow, const QColor& diffuseColorWhatYouSeeInDirectLight, const QColor& specularColorImportantIfShiny, const qreal shininessBetween0And128 )
   {
      this->setAmbientColor( ambientColorWhatYouSeeInShadow );
      this->setDiffuseColor( diffuseColorWhatYouSeeInDirectLight );
      this->setSpecularColor( specularColorImportantIfShiny );
      this->setShininess( shininessBetween0And128 );
      return *this;
   }

   // Some standard materials for objects (built-in).
   static const QSimMaterialType&  GetChinaMaterialStandard(); 
   static const QSimMaterialType&  GetChinaMaterialHighlight(); 
   static const QSimMaterialType&  GetMetalMaterialStandard(); 
   static const QSimMaterialType&  GetMetalMaterialHighlight(); 
};


//------------------------------------------------------------------------------
}  // End of namespace QSim
//--------------------------------------------------------------------------
#endif  // QSIMMATERIALTYPE_H__
//--------------------------------------------------------------------------
