#ifndef _erCv_ANALYSIS_HPP_
#define  _erCv_ANALYSIS_HPP_

#include "erCvSegmentationParams.hpp"
#include "erCvFiltersParams.hpp"
#include "erCvTools.hpp"
#include "erCvBase.hpp"

#include<string>

/** \defgroup erAnalysis Analysis  */
/** \addtogroup erAnalysis */
/**\{*/
/** Classe de base pour l ensemble des analyse d erCv */
struct erAnalysis
{
  erAnalysis( );
  erAnalysis( std::string name, std::string infofile="info"); 
  void  create( ); 
  virtual bool doIt( std::string)=0;  /** < doIt pure virtuel pour utilisation dans BAME */
  std::string          infoFile; /** < Fichier de sortie des infos */
  std::string          name;     /** < Nom a donner a l analyse */
  std::string          dir_analysis; /** < Repertoire de la analyse en general name+_erCvAnalysis */  
};


/** Classe pour des analyse de macro gouttes : These Julien Chapuis */

struct erMacroDropAnalysis:public erAnalysis
{ 
  erMacroDropAnalysis( );
  erMacroDropAnalysis( std::string name, std::string infofile = "info");
  bool defineParametersUI( std::string image); /**\brief < Definition des parametre interactives */
  void defineParameters( CvRect, erCerc, erSmootP, erSmootP, erCannyP, erAdThrP); /**\brief < Passages Parametres en dur */
  bool doIt( std::string);  /**\brief < Analyse sur le fichier */
  void saveParameters( std::string);
  void loadParameters( std::string);
  CvRect         rectOI;
  erCerc         cercToStart;
  erSmootP       param_smooth1,param_smooth2;
  erCannyP       param_canny;
  erAdThrP       param_adaptive_threshold;
};


/**\}*/


#endif
