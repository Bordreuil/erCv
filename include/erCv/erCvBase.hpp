/** \mainpage
    Le projet erCv est un module developpe au cours du projet ANR Jeunes Chercheurs
    TEMMSA 2007 effectue au sein du Laboratoire de Mecanique et Genie Civil/UMR5508 de l' Universite de Montpellier 2. Le module developpe par Edward Romero edward.romero@lmgc.univ-montp2.fr
    est essentiellement un couplage entre plusieurs bibliotheques OpenSource:
    - OpenCv : permet de realiser le traitement d image (segmentation, seuillage,calibration,..)
    -  CGAL 3.4 : permet de quantifier tous les aspects geometriques
    .
    
    L'installation necessite un compilateur C++.
    L'installation d erCv necessite le logiciel OpenSource CMake http://www.cmake.org
    Une extension du module est prevu en python et necessite la bibliotheque Boost.python
    http://www.boost.org 

    Les fichiers interfaces (.hpp) sont accessibles dans un programme en specifiant le repertoire include ou include/erCv suivant l utilisation qu'on veut en faire.
 */

/** @file erCvBase.hpp 
  \brief Fichier contenant l encapsulation par une classe de la structure 
   IplImage d openCv ainsi que la redefinition de quelques fonctions d openCv
  @package erCv
  \defgroup cv_group erCvBase
  Decrit l encapsulation de base d opencv pour les developpements d edward
*/
#ifndef _erCvBase_hpp
#define _erCvBase_hpp

#include <cv.h>
#include <highgui.h>
#include <boost/lexical_cast.hpp>
#include <vector>
#include <string>
#include <utility>
#include <iostream>
#include <fstream>

extern std::string INFOFILE;
const char* nameInfoFile(std::string);
// Une classe pour interfacer l image IplImage d OpenCv
/** \addtogroup cv_group */
/*@{*/

class erImage : public IplImage
/** 
    Encapsulation de la structure IplImage d openCv
    erImage derive de la classe IplImage, on peut utiliser l ensemble des fonctions
    d opencv directement avec un pointeur sur cette classe.
 */
{
public:
  /** 
      Constructeur destructeur
  **/
  erImage();
  erImage(char* );
  erImage(IplImage* );
  erImage(IplImage);
 
  ~erImage();
  CvRect  rectan;
  bool    drawing;
private:
  /**
     Methodes d acces
  **/ 
};


// Quelques fonctions utiles d' OpenCv
/** \brief Fonction permettant de visualiser une Image a l aide
 d openCv
 */
void erShowImage(char* ,IplImage*);


/** \brief Fonction permettant de charge une  Image a l aide
 d openCv
 */
std::pair<erImage,bool> erLoadImage( char**);


/** \brief Fonction permettant de charger une serie d Image a l aide
 d openCv ayant comme extentions une succesion ordonne et continue de intieres
 */
std::pair<erImage,bool> erLoadImageSeries( char**);



/** \brief Fonction permettant de sauvegarder une image a l aide
 d openCv
 */
void erSaveImage( IplImage*, char**);

erImage erCopyImage(erImage);


/** Fonction permettant de convertir une image en noir et blanc 
*/
//erImage    erConvertToBlackAndWhite( IplImage*);
IplImage*  erConvertToBlackAndWhite( IplImage*);


/** Fonction permettant d ecrire un ficher de sauvegarde des paramettres utilises pour chaque fonction
 */
void erWriteRecordFile( char**);


/** Fonction permettant d convertir une image 32bit en 8bit
 */
void erCvConvert32to8( IplImage*, IplImage*);


/*@}*/
#endif
