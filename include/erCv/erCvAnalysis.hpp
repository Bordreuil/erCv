// Copyright Universite Montpellier 2/CNRS 
// Contributor(s) : 
//         Edward Romero 
//         Cyril Bordreuil
// Contact: cyril.bordreuil@univ-montp2.fr
// 
// This software is a computer program whose purpose is to [describe
//  functionalities and technical features of your software].
//
// This software is governed by the CeCILL license under French law and
// abiding by the rules of distribution of free software.  You can  use, 
// modify and/ or redistribute the software under the terms of the CeCILL
// license as circulated by CEA, CNRS and INRIA at the following URL
// "http://www.cecill.info". 
//
// As a counterpart to the access to the source code and  rights to copy,
// modify and redistribute granted by the license, users are provided only
// with a limited warranty  and the software's author,  the holder of the
// economic rights,  and the successive licensors  have only  limited
// liability. 
//
// In this respect, the user's attention is drawn to the risks associated
// with loading,  using,  modifying and/or developing or reproducing the
// software by the user in light of its specific status of free software,
// that may mean  that it is complicated to manipulate,  and  that  also
// therefore means  that it is reserved for developers  and  experienced
// professionals having in-depth computer knowledge. Users are therefore
// encouraged to load and test the software's suitability as regards their
// requirements in conditions enabling the security of their systems and/or 
// data to be ensured and,  more generally, to use and operate it in the 
// same conditions as regards security. 
// 
// The fact that you are presently reading this means that you have had
// knowledge of the CeCILL license and that you accept its terms.
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
/* \brief This  module encapsulated different methods in order to perform analysis
   on images during arc welding */
/*

 \brief Base class to others. Pure virtual.

 */

typedef std::list< CgalSegmt> SegmentList;

struct erAnalysis
{
  erAnalysis( );
  /**
     Constructor 
     \param name : Nom de l analyse, genere automatiquement un repertoire avec 
                   name+'_erCvAnalysis'
		   Plusieurs analyses differents peuvent utiliser le meme nom.
		   Chaque analyse a un tag supplementaire:
		   - _mcr : pour une analyse macrodrop
		   - _mtl : pour metal transfert
		   - _wep : pour weld pool

     \param infoFile : file name where informations will be written
   */
  erAnalysis( std::string name, std::string infofile="info"); 
  /**
     Methode permettant de creer l'analyse dans les classes derivees
   */
  void  create( ); 

  /** Creation de la matrix de calibration pour les images
   */
  void        defineCalibration( std::string, std::string);
  char*       currentFileName();
  void        setCurrentFileName(char*);
  void        setOutputGeometryFile(std::string);
  void        writeOutGeometry(SegmentList&);
  std::string outputGeometryFile();
  bool        outputGeometry();
  bool        outputConvex();
  void        setOutputConvex(bool);
  void        setOuputGeometry(bool);
  bool        outputAxisymmetricGeometry();
  void        setOutputIntermediateImages(bool);
  bool        outputIntermediateImages();
  void        setOutputAxisymmetricGeometry(bool);
  /* \brief Application de l Analysis avec des parametres introduit dans le ficher de finition de l 'experiance.
   */
  virtual bool doIt     ( std::string)=0; 
  virtual bool doItImage(erImage&)   =0;
  std::string          infoFile;      /** < Fichier de sortie des infos */
  std::string          name;          /** < Nom a donner a l analyse */
  std::string          dir_analysis;  /** < Repertoire de la analyse en general name+_erCvAnalysis */  
  std::string          output_name;  /** < Nom du fichier de sortie des resultats*/
  erCalibration        _calibration;
  bool                 _with_calibration;  // Pour savoir si on active la calibration
  bool                 _output_geometry_characteristics;
  bool                 _output_axisymmetric;
  bool                 _output_convex;
  bool                 _output_intermediate_images;
  std::string          _output_geometry_file;
  char* file_name;
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
  /** \brief Constructeur par defaul */
  erMacroDropAnalysis( ); 
  /** Constructeur a partir du nom de l image 
      \param std::string : nom de l image
      \param std::string : nom des fichers sortie
  */
  erMacroDropAnalysis( std::string name, std::string infofile = "info");
  /** Definition des paramettres interactive
      \param std::string : nom de l image
  */     
  bool defineParametersUI( std::string image); 
  /** Passage des parametres dans le ficher a compiler macro_drop_python.cpp 
      \param CvRect       : rectangle de la zone d interet 
      \param erCerc       : cercle du debut de la curve a extraire
      \param erSmootP     : premier parametre de lissage
      \param erSmoothP    : seconde parametre de lissage
      \param erCannyP     : parametre du filtre de canny
      \param erAdThrP     : parametre du seuil adapte par zones
      \param erEqualP     : equalizateur d histogrames
   */
  void defineParameters( CvRect, erCerc, erSmootP, erSmootP, erCannyP, erAdThrP, erEqualP equal=erEqualP(1)); /** < Passages Parametres en dur */

  bool doIt( std::string);  /** < Analyse sur le fichier */
  virtual bool doItImage(erImage&);
  void saveParameters( std::string);
  void loadParameters( std::string);
  CvRect         rectOI;                       /*< Rectangle qui demarque la zone d interet  */
  erCerc         cerc_to_start;                  /* < Cercle qui demarque le debut de la curve que sousligne le profil de la macro goutte */
  erEqualP       param_equalizer_histogram;    /* < 0 si l equalizateur est active: Augmente le contraste de l image ( image en niveau des gris)
						    1 si l equalizateur n'est pas active: Contraste naturel de l image 
					       */
  erSmootP       param_smooth1, param_smooth2; /** 
						   Premier lissage du type BLUR: Augmente ou diminue 
						   l homegenite de l image. Valeurs possibles numeros
						   impairs: 1, 3, 5, ..., 2n+1 avec n Naturel.						   
						   Pour    +> Uniformise les niveaux de gris a l interieur
						   du la macro goutte
						   Contre +> Rendre difficil la detection du bord 
						   entre la macro goutte et les zones dans l espace a faible contraste
						   
						   Pour    <- Plus facile la detection du contour 
						   de la macro goutte dans les zones a faible contraste
						   Contre <- Reduit l unfirmite a l interieur 
						   de la macro goutte, donc plus difficile de
						   determiner quelle est la macro goutte
						   
						   Deuxieme lissage du type MEDIAN 
						   Valeurs possibles numeros impairs: 1, 3, 5, ...,
						   2n+1 avec n Naturel.
						   Pour    +> Unifie les zones a egal niveau de gris, 
						   en reduisant les espace blanche entre les dites zones, 
						   si celle-ci sont minoritaires et rares
						   
						   Contre +> Peut ajouter des elements externes a 
						   la macro goutte et modifier sa forme et taille, 
						   notament vers les extremites de l image
						   
						   Pour    <- Ameliore la perception 
						   de la taille reel de la macro goutte
						   Contre <- Peut  modifier la forme de la macro goutte
					       */
  erCannyP       param_canny;                  /** 
						   Valeurs pour discriminer les bords 
						   principaux selon le filtre de canny (Threshold I et II):
						   Valeurs possibles [0, 500]						   
						   Pour    +> Reduit le nombre de bords secondaire detectes par la filtre 
						   Contre +> Reduit la posibilite d obtenir un 
						   contour continue sur le profil de la macro goutte 
						   ( si le bord n'est pas bien definie)
						   Pour    <- Ameliore la posibilite d obtenier un contour continue
						   Contre <- Augmente le nombre de bord secondaire 
						   qui aparetraint dans l image final
					       */
  erAdThrP       param_adaptive_threshold;     /** 
						   Seuil adaptative par zones
						   Valeurs possibles [0, 255]

						   Seuil applique par zones:
						   Pour    +> Ameliore la detection de la macro 
						   goutte dans le zones de faible contraste (aux 
						   extremes et somet de la goutte)
						   Contre +> Peut mixer le profil de la macroi goutte 
						   avec les zones a forte contraste dans l espace interelectrode
						   Pour    <- Empeche la confusion du profil de la 
						   macro goutte avec des elements externes dans l espace interelectrode
						   Contre <- 

						   Zone d application du seuillage:
						   Pour    +> Ameliore la densite de la macro goutte 
						   (reunis le zones non conexes de la macro goutte)
						   
						   Contre +> Reunis toutes le zones de l image dans un seul
						   niveau de gris (seuil maximal de gris)
						   
						   Pour    <- Permet de ajuster le mieu la taille reel de la macro goutte
						   Contre <- Reunis toutes les zones de l image dans une seul niveau (blanche)
					       */
};
/** \brief  Comportement du liquide residuel en bout de fil MIG


    Cette classe encapsule les methodes pour obtenir le
    contour non ferme delimitant le contour du fil par 
    une methode d  ombroscopie
 */
class erWireAnalysis:public erMacroDropAnalysis
{
public:
  erWireAnalysis(std::string name, std::string infofile = "info"); 
  void setEndZone(erCerc);
  void setBeginZone(erCerc);
  bool doItImage(erImage&);
  erCerc    cerc_to_end;
  erAlphaP  param_alpha_shape; 
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
  /** Constructeur par defaul */
  erMetalTransfertAnalysis( );
  /** Cosntructeur a partir du nom de l image 
      \param std::string : nom de l image
      \param std::string : nom des fichers sortie
  */
  erMetalTransfertAnalysis( std::string name, std::string infofile = "info");
    /** Definition des paramettres interactive
      \param std::string : nom de l image
  */     
  bool defineParametersUI( std::string image);
  /** Passage des parametres dans le ficher a compiler drop_python.cpp 
      \param CvRect       : rectangle de la zone d interet 
      \param erCerc       : cercle du debut de la curve a extraire
      \param erSmootP     : premier parametre de lissage
      \param erSmoothP    : seconde parametre de lissage
      \param erCannyP     : parametre du filtre de canny
      \param erAdThrP     : parametre du seuil adapte par zones
      \param erEqualP     : valeur de l alpha shape
   */
  void defineParameters( CvRect, erSmootP, erSmootP, erCannyP, erAdThrP, erAlphaP);

  /** Application de l analyse
      \param std::string : nom de l image
   */
  bool doIt( std::string);
  bool doItImage(erImage&);
  /** Enregistrement des parametres
      \param std::string : nom de l image
  */
  void saveParameters( std::string);             

  /** Charger les parametres
   */
  void loadParameters( std::string);               /** <  Pas encore active */


  //void setOutputGeometryFile(std::string);         /** <  Methode pour reinitialiser le nom du fichier de geometrie
  //						          A chaque passage, l ancien fichier est ecrase      */
  CvRect         rectOI;                           /** <  Position de la zone d etude dans l image */
  erSmootP       param_smooth1, param_smooth2;     /**  
							Premier lissage du type BLUR: Augmente ou diminue l homegenite de l image.
							Valeurs possibles numeros impairs: 1, 3, 5, ..., 2n+1 avec n Naturel.						   
							Pour    +> Uniformise les niveaux de gris a l interieur du la goutelette
							Contre +> Rendre difficil la detection du bord entre
							la goutelette et les zones dans l espace a faible contraste
							Pour    <- Plus facil la detection du contour de la goutelette
							dans les zones a faible contraste
							Contre <- Reduit l unfirmite a l interieur de la goutelette, 
							donc plus difficil de determiner quelle est la macro goutte
							
							Deuxieme lissage du type MEDIAN 
							Valeurs possibles numeros impairs: 1, 3, 5, ..., 2n+1 avec n Naturel.
							Pour    +> Unifie les zones a egal niveau de gris,
							en reduisant les espace blanche entre les dites zones,
							si celle-ci sont minoritaires et rares
							
							Contre +> Peut ajouter des elements externes a la goutelette
							et modifier sa forme et taille, notament vers les extremites de l image
							Pour    <- Ameliore la perception de la taille reel de la macro goutte
							Contre <- Peut  modifier la forme de la goutelette
						   */
  erCannyP       param_canny;                      /**  
							Valeurs pour discriminer les bordes principaux 
							selon le filtre de canny (Threshold I et II):
							Valeurs possibles [0, 500]						   
							Pour    +> Reduit le nombre de bords secondaire
							detectes par la filtre 
							Contre +> Reduit la posibilite d obtenir un contour 
							continue sur le profil de la goutelette ( si le bord n'est pas bien definie)
							Pour    <- Ameliore la posibilite d obtenier un contour continue
							Contre <- Augmente le nombre de bord secondaire qui 
							aparetraint dans l image final
						   */
  erAdThrP       param_adaptive_threshold;         /**
						      Seuil adaptative par zones
						      Valeurs possibles [0, 255]
						      
						      Seuil applique par zones:
						      Pour    +> Ameliore la detection de la gouttelette dans
						      le zones de faible contraste (aux extremes et somet de la goutte)
						      Contre +> Peut mixer le profil de la macroi goutte avec les
						      zones a forte contraste dans l espace interelectrode
						      
						      Pour    <- Empeche la confusion du profil de la macro
						      goutte avec des elements externes dans l espace interelectrode
						      Contre <- 
						      
						      Zone d application du seuillage:
						      Pour    +> Ameliore la densite de la macro goutte
						      (reunis le zones non conexes de la macro goutte)
						      Contre +> Reunis toutes le zones de l image dans une seule 
						      niveau de gris (seuil maximal de gris)
						      Pour    <- Permet de ajuster le mieu la taille reel de la macro goutte
						      Contre <- Reunis toutes les zones de l image dans une seul niveau (blanche)
						   */
  erAlphaP       param_alpha_shape;                /** 
						       Parametre pour travailler avec les alpha shape de CGAL 
						       Valeurs possibles [ 1, ) 
						   */  


};

/** \brief  Detection de contour d une zone en fusion 
    sans arc pour regarder le comportement  de solidification
 */

struct erSolidificationAnalysis:public erAnalysis
{
  /** Constructeur par defaul */
  erSolidificationAnalysis( );
  /** Cosntructeur a partir du nom de l image 
      \param std::string : nom de l image
      \param std::string : nom des fichers sortie
  */
  erSolidificationAnalysis( std::string name, std::string infofile = "info");
    /** Definition des paramettres interactive
      \param std::string : nom de l image
  */     
  
  void defineParameters( CvRect,erSmootP, erCannyP, erThresP, erAlphaP);

  /** Application de l analyse
      \param std::string : nom de l image
   */
  bool doIt( std::string);
  bool doItImage(erImage&);
  /** Enregistrement des parametres
      \param std::string : nom de l image
  */
 

  //void setOutputGeometryFile(std::string);         /** <  Methode pour reinitialiser le nom du fichier de geometrie
  //						          A chaque passage, l ancien fichier est ecrase      */
  CvRect         rectOI;                           /** <  Position de la zone d etude dans l image */
  erSmootP       param_smooth1;                    /**  
							Premier lissage du type BLUR: Augmente ou diminue l homegenite de l image.
							Valeurs possibles numeros impairs: 1, 3, 5, ..., 2n+1 avec n Naturel.						   
							Pour    +> Uniformise les niveaux de gris a l interieur du la goutelette
							Contre +> Rendre difficil la detection du bord entre
							la goutelette et les zones dans l espace a faible contraste
							Pour    <- Plus facil la detection du contour de la goutelette
							dans les zones a faible contraste
							Contre <- Reduit l unfirmite a l interieur de la goutelette, 
							donc plus difficil de determiner quelle est la macro goutte
							
							Deuxieme lissage du type MEDIAN 
							Valeurs possibles numeros impairs: 1, 3, 5, ..., 2n+1 avec n Naturel.
							Pour    +> Unifie les zones a egal niveau de gris,
							en reduisant les espace blanche entre les dites zones,
							si celle-ci sont minoritaires et rares
							
							Contre +> Peut ajouter des elements externes a la goutelette
							et modifier sa forme et taille, notament vers les extremites de l image
							Pour    <- Ameliore la perception de la taille reel de la macro goutte
							Contre <- Peut  modifier la forme de la goutelette
						   */
  erCannyP       param_canny;                      /**  
							Valeurs pour discriminer les bordes principaux 
							selon le filtre de canny (Threshold I et II):
							Valeurs possibles [0, 500]						   
							Pour    +> Reduit le nombre de bords secondaire
							detectes par la filtre 
							Contre +> Reduit la posibilite d obtenir un contour 
							continue sur le profil de la goutelette ( si le bord n'est pas bien definie)
							Pour    <- Ameliore la posibilite d obtenier un contour continue
							Contre <- Augmente le nombre de bord secondaire qui 
							aparetraint dans l image final
						   */
  erThresP                 param_threshold;         /**
						    
						   */
  erAlphaP       param_alpha_shape;                /** 
						       Parametre pour travailler avec les alpha shape de CGAL 
						       Valeurs possibles [ 1, ) 
						   */  
 
};




/** \brief Class pour des analysis des bains de fusion

    Cette classe encapsule les methodes pour obtenir le 
    contour ferme du bain fusion observe par reflexion 
    speculaire. 
*/
struct erWeldPoolAnalysis:public erAnalysis
{
  /** Constructeur par defaul */
  erWeldPoolAnalysis();

  /** Cosntructeur a partir du nom de l image 
      \param std::string : nom de l image
      \param std::string : nom des fichers sortie
  */
  erWeldPoolAnalysis( std::string name, std::string infofile = "info");
 
  void defineParameters( CvRect, erWhitBP, erSmootP, erSmootP, erCannyP, erDilatP, erThresP, erTemplP, erAlphaP); 
 /** Passage des parametres dans le ficher a compiler fusion_bain_python.cpp 
      \param CvRect       : rectangle de la zone d interet 
      \param erWhitBP     : parametres pour l atenuations de taches blanches
      \param erSmootP     : premier parametre de lissage
      \param erSmootP     : seconde parametre de lissage
      \param erCannyP     : parametre du filtre de canny
      \param erDilatP     : parametre reduction des pixles noirs
      \param erThresP     : parametre du seuil
      \param erTemplP     : parametres pour la segmentation
      \param erAlphaP     : parametre pour l alpha shape
   */
  bool doIt( std::string); /** < Analyse sur le ficher */
  bool doItImage(erImage&);
  void saveParameters( std::string);
  void loadParameters( std::string);
  bool whiteBlobDetection();
  void setWhiteBlobDetection(bool);
  //void setOutputGeometryFile(std::string);         /** < Methode pour reinitialiser le nom du fichier de geometrie */
  
  CvRect   rectOI;                                 /** < Position de la zone d etude dans l image */
  erWhitBP param_white_blob;                       /**
						      Recouvrement des taches blanches dans la zone d etude 
						      
						      Seuil Blanc:
						      Valeurs possibles [ 1, 255]
						      Pour    +> Reduit la selection de zones non blanches a couvrir
						      Contre +> Des taches blanches de niveau de gris 
						      inferieur au seuil ne seront pas recouvertes
						      Pour    <- Reduit la posibilitte de ne pas recouvrir 
						      des taches a l interieur du bain de fusion
						      Contre <- Augment la possibilite de couvrir 
						      sections du bord du bain de fusion
						      
						      Seuil Noir:
						      Valeurs possibles [ 1, 255]
						      Pour    +> Permet de detecter des taches blanches 
						      entoures que par de zones d un niveau de gris au desou du seuil choisit
						      Contre +> Augmente la posibilite de couvrir zones
						      dans le bord du bain de fusion
						      Pour    <- Ameliore la possibilite de detecter de 
						      taches blanches a l interieur du bain de fusion (si 
						      le bain de fusion est uniforme)
						      Contre <- Si le bord des taches blanches n'est sont
						      pas uniformes, reduit la possibilite de detection des taches
						      
						      Bord exterieur:
						      Valeur possibles [ 1, taille de l image]
						      Pour    +> Permet de detecter des taches, qui ont 
						      un bord exterieur pas homogene (niveau de gris)
						      Contre +> Si les taches sont proche de bord du bain
						      fusion, reduit les posibilites de les detecter
						      Pour    <- Permet de detecter des taches proche du bord 
						      du bain fusion 
						      Contre <- Reduit la posibilite de detecteur de taches,
						      car generalement leur entourage n'est pas homogene
						      
						      Taille de la tache
						      Valeur possible [ 0, taille image x taille image]
						      Pour    +> Seul les taches les plus importantes seront detectes
						      Contre +> Des taches des taille moyenne , mais
						      importantes peuvent n'est pas etre detectes
						      Pour    <- Permet de detecter un plus grand nombre des taches
						      Contre <- Des zones blaches issue de la texrture 
						      de l image peuvent etre confondues avec des taches 
						   */
  erSmootP param_smooth1, param_smooth2;           /** 
						       Premier lissage du type BLUR: Augmente ou diminue 
						       l homegenite de l image.
						       Valeurs possibles numeros impairs: 1, 3, 5, ..., 
						       2n+1 avec n Naturel.						   
						       Pour    +> Uniformise les niveaux de gris a l
						       interieur du bain de fusion et a l exterieur
						       Contre +> Rendre difficil la detection du bord entre
						       le bain de fusion et le metal solide
						       Pour    <- Plus facil la detection du contour du
						       bain fusion si la difference de texture avec l exterieur est apreciable
						       Contre <- Reduit l unformite a l interieur du bain
						       fusion et a l exterieur, donc plus difficil de determiner le contour
						       
						       Deuxieme lissage du type MEDIAN 
						       Valeurs possibles numeros impairs: 1, 3, 5, ..., 2n+1 avec n Naturel.
						       Pour    +> Unifie les zones a egal niveau de gris,
						       en reduisant les espace blanche entre les dites zones,
						       si celle-ci sont minoritaires et rares
						       Contre +> Peut ajouter des elements externes au bain
						       de fusion et modifie sa forme et taille.
						       Pour    <- Ameliore la perception de la taille reel
						       de la macro goutte
						       Contre <- Augmente la dificulte pour trouver un contour ferme						       
						   */
  erDilatP param_dilate;                           /**
						      Nombre d iterations:
						      Valeurs possibles [ 1, 16]
						      Pour     +> Augmente la densite des pixels blanche,
						      aide a fermer les contours autour du bain fusion
						      Contre  +> Peut deformer ou reduir la taille du bain fusion
						      Pour     <- Augmente la posibilite de garder la forme reel du bain fusion
						      Contre  <- Reduit la posibilite de fermer le contour du bain fusion
						   */
  erCannyP param_canny;                            /** 
						       Valeurs pour discriminer les bordes principaux selon
						       le filtre de canny (Threshold I et II):
						       Valeurs possibles [0, 500]						   
						       Pour    +> Reduit le nombre de bords secondaire detectes
						       par la filtre 
						       Contre +> Reduit la posibilite d obtenir un contour
						       continue sur le profil de la macro goutte ( si
						       le bord n'est pas bien definie)
						       Pour    <- Ameliore la posibilite d obtenier un contour continue
						       Contre <- Augmente le nombre de bord secondaire qui aparetraint dans l image final
						   */
  erThresP param_threshold;                        /**
						      Seuillage de l image
						      Valeurs possibles [ 1, 255]

						      Seuil maximal
						      Pour     +> Augmente le contraste entre les zones 
						      au dessu du seuil et les zones en desous
						      Contre  +> 
						      Pour     <-
						      Contre  <- Reduit le contraste entre les zones au
						      dessus du seuil et les zones en desous
						      
						      Seuil
						      Pour     +> Permet de resortir le bain fusion du reste de l image
						      Contre  +> Peut ajouter des elements externes au bain 
						      Pour     <- Reduit la posibilite d'ajouter des
						      elements externes du bain au bain
						      Contre  <- Peut elever certain section de l
						      image qui apartien au bain de fusion
						   */
  erTemplP param_template;                         /** 
						       Paramettre pour segmenter l image a partir d un echantillon
						       Plus grand est l echantillon moins definies seront
						       les bordes dans l image segmente, plus reduit est 
						       l echantillon mieu sera la resolution de l image.
						       L echantillon doit etre choisit dans une region de
						       texture representative de la zone exterieur au bain fusion.
						       Plus grand est l echantillion, plus facil est pour 
						       l algorithme pour trouver les zones que sont different, 
						       notamment le bain fusion. Plus reduit est l echantillion ,
						       plus dificile est pour l algorithme etablir la difference
						       entre deux zones dans l image.
						       Le rectangle est defini dans le nouveau repere
						       de l image.
						   */
  erAlphaP param_alpha_shape;                      /**
						      Paramettre pour la construction des alpha shape en CGAL 
						   */
  
  bool           output_convex_polygon;            /**
						      Si on veut extraire le domaine convexe initialiser a true au depart 
						   */
  bool           white_blob_detection;
};








/** \brief Class pour des analysis des laser Prototypage

    Cette classe encapsule les methodes pour obtenir le 
    contour ferme du bain fusion dans des procedes laser
*/
struct erLaserPrototypageAnalysis:public erAnalysis
{
  /** Cosntructeur par defaul */
  erLaserPrototypageAnalysis( );
 
  /** Cosntructeur a partir du nom de l image 
      \param std::string : nom de l image
      \param std::string : nom des fichers sortie
  */
  erLaserPrototypageAnalysis( std::string name, std::string infofile = "info");
  
  /** Definition des paramettres interactive
      \param std::string : nom de l image
  */     
  bool defineParametersUI( std::string image); /** < Definitions des parametres interactive */
  
  /** Passage des parametres dans le ficher a compiler fusion_bain_python.cpp 
      \param CvRect       : rectangle de la zone d interet 
      \param erSmootP     : premier parametre de lissage
      \param erSmootP     : seconde parametre de lissage
      \param erCannyP     : parametre du filtre de canny
      \param erDilatP     : parametre reduction des pixles noirs
      \param erThresP     : parametre du seuil
      \param erAdThrP     : parametre du seuil adapte par zones
      \param erTemplP     : parametres pour la segmentation
      \param erAlphaP     : parametre pour l alpha shape
  */
  void defineParameters_diffuse( CvRect, erSmootP, erCannyP, erAdThrP, erAlphaP);

  /** Passage des parametres dans le ficher a compiler fusion_bain_python.cpp 
      \param CvRect       : rectangle de la zone d interet 
      \param erSmootP     : premier parametre de lissage 
      \param erCannyP     : parametre du filtre de canny
      \param erAdThrP     : parametre du seuil adapte par zones
      \param erAlphaP     : parametre pour l alpha shape
  */
  void defineParameters( CvRect, erSmootP, erSmootP, erCannyP, erDilatP, erThresP, erTemplP, erAlphaP);
  
  /** Fonction application de l analyse pour les bain fusion laser diffuse
   */ 
  bool doIt_diffuse( std::string);
  
  /** Fonction application de l analyse
   */ 
  bool doIt( std::string);
  bool doItImage(erImage&);
  /** Enregistrement des parametres
      \param std::string :  nom de l image */
  void saveParameters( std::string);

  void loadParameters( std::string);

  /** Methode pour reinitialiser le nom du ficher de geometrie 
      \param std::string : nom de l image
  */
  //void setOutputGeometryFile(std::string);         

  CvRect   rectOI;
  erSmootP param_smooth1, param_smooth2;
  erDilatP param_dilate;
  erCannyP param_canny;
  erThresP param_threshold;
  erAdThrP param_adaptive_threshold;
  erTemplP param_template;
  erAlphaP param_alpha_shape;
  //bool           output_geometry_characteristics;  /** <  Desactiviation des sorties geometriques  Initialiser a true*/
  //std::string    output_geometry_file;             /** <  Nom du fichier de sortie pour la geometrie */
  bool           output_convex_polygon;           /** < Si on veut extraire le domaine convexe initialiser a true au depart */
};
/**\}*/




#endif
