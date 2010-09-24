#ifndef _erCv_ANALYSIS_HPP_
#define  _erCv_ANALYSIS_HPP_

#include "erCvSegmentationParams.hpp"
#include "geometry/erCgalAlphaShape2.hpp"
#include "geometry/geometricalParams.hpp"
#include "erCvFiltersParams.hpp"
#include "erCvTools.hpp"
#include "erCalibration.hpp"
#include "erCvBase.hpp"

#include<string>

/** \defgroup erAnalysis Analysis  */
/** \addtogroup erAnalysis */
/**\{*/
/** Classe de base pour l ensemble des analyse d erCv, c est une classe purement virtuelle
 */
struct erAnalysis
{
  erAnalysis( );
  /**
     Constructeur 
     \param name : Nom de l analyse, genere automatiquement un repertoire avec 
                   name+'_erCvAnalysis'
		   Plusieurs analyses differents peuvent utiliser le meme nom.
		   Chaque analyse a un tag supplementaire:
		   - _mcr : pour une analyse macrodrop
		   - _mtl : pour metal transfert
		   - _wep : pour weld pool

     \param infoFile : nom du fichier ou sont ecrit le blabla
   */
  erAnalysis( std::string name, std::string infofile="info"); 
  void  create( ); 
  void  defineCalibration(std::string,std::string);
  virtual bool doIt( std::string)=0;  /** < doIt pure virtuel pour utilisation dans BAME */
  std::string          infoFile;      /** < Fichier de sortie des infos */
  std::string          name;          /** < Nom a donner a l analyse */
  std::string          dir_analysis;  /** < Repertoire de la analyse en general name+_erCvAnalysis */  
  erCalibration        _calibration;
  bool                 _with_calibration;  // Pour savoir si on active la calibration
};



/** \brief  Classe pour des analyse de macro gouttes : These Julien Chapuis 


    Cette classe encapsule les methodes pour obtenir le
    contour non ferme delimitant une macro goutte 
    observe en ombroscopie.
    Edward Romero (mettre article) a optimiser les filtrages et 
    les recherches de contours pour pouvoir en extraire des images.
 */

struct erMacroDropAnalysis:public erAnalysis
{ 
  erMacroDropAnalysis( );
  erMacroDropAnalysis( std::string name, std::string infofile = "info");
  bool defineParametersUI( std::string image); /** < Definition des parametre interactives */
  void defineParameters( CvRect, erCerc, erSmootP, erSmootP, erCannyP, erAdThrP, erEqualP equal=erEqualP(1)); /** < Passages Parametres en dur */
  bool doIt( std::string);  /** < Analyse sur le fichier */
  void saveParameters( std::string);
  void loadParameters( std::string);
  CvRect         rectOI;
  erCerc         cercToStart;
  erEqualP       param_equalizer_histogram;
  erSmootP       param_smooth1, param_smooth2; /**    */
  erCannyP       param_canny;
  erAdThrP       param_adaptive_threshold;
};

/** \brief  Classe pour des analyse des gouttes en vol : These Julien Chapuis 

    Cette classe encapsule les methodes pour obtenir le
    contour ferme delimitant une macro goutte 
    observe en ombroscopie.
    Edward Romero (mettre article) a optimiser les filtrages et 
    les recherches de contours pour pouvoir en extraire des images.


 */
struct erMetalTransfertAnalysis:public erAnalysis
{
  erMetalTransfertAnalysis();
  erMetalTransfertAnalysis( std::string name, std::string infofile = "info");
  bool defineParametersUI( std::string image);
  void defineParameters( CvRect, erSmootP, erSmootP, erCannyP, erAdThrP, erAlphaP); /** < Passages Parametres en dur */
  bool doIt( std::string);  /** < Analyse sur le fichier */
  void saveParameters( std::string);               /** < Sauvegarde des parametres utilises   */
  void loadParameters( std::string);               /** < Pas encore active */
  void setOutputGeometryFile(std::string);         /** < Methode pour reinitialiser le nom du fichier de geometrie
						         A chaque passage, l ancien fichier est ecrase      */
  CvRect         rectOI;                           /** <  Position de la zone d etude dans l image */
  erSmootP       param_smooth1, param_smooth2;     /** < Parametre de flitrage (mettre defaut)   */
  erCannyP       param_canny;                     
  erAdThrP       param_adaptive_threshold;         /** < Seuil adaptif */
  erAlphaP       param_alpha_shape;                /** < Parametre pour travailler avec les alpha shape de CGAL */  
  bool           output_geometry_characteristics;  /** <  Desactiviation des sorties geometriques */
  std::string    output_geometry_file;             /** <  Nom du fichier de sortie pour la geometrie */
};







/** \brief Class pour des analysis des bains de fusion

    Cette classe encapsule les methodes pour obtenir le 
    contour ferme du bain fusion observe par reflexion 
    speculaire. 
*/

struct erWeldPoolAnalysis:public erAnalysis
{
  erWeldPoolAnalysis();
  erWeldPoolAnalysis( std::string name, std::string infofile = "info");
  bool defineParametersUI( std::string image); /** < Definitions des parametres interactive */
  void defineParameters( CvRect, erWhitBP, erSmootP, erSmootP, erCannyP, erDilatP, erThresP, erTemplP, erAlphaP); /* < Passages Parametres en dur */
  bool doIt( std::string); /** < Analyse sur le ficher */
  void saveParameters( std::string);
  void loadParameters( std::string);
  void setOutputGeometryFile(std::string);         /** < Methode pour reinitialiser le nom du fichier de geometrie */

  CvRect   rectOI;
  erWhitBP param_white_blob;
  erSmootP param_smooth1, param_smooth2;
  erDilatP param_dilate;
  erCannyP param_canny;
  erThresP param_threshold;
  erTemplP param_template;
  erAlphaP param_alpha_shape;
  bool           output_geometry_characteristics;  /** <  Desactiviation des sorties geometriques  Initialiser a true*/
  std::string    output_geometry_file;             /** <  Nom du fichier de sortie pour la geometrie */
  bool           output_convex_polygon;           /** < Si on veut extraire le domaine convexe initialiser a true au depart */
};
/**\}*/

#endif
