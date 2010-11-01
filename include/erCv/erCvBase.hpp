
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

#include <string>
#include <utility>


#include "erCvTools.hpp"

extern std::string INFOFILE;

const char* nameInfoFile(std::string);
const char* nameGoodImagesFile(std::string);


// Une classe pour interfacer l image IplImage d OpenCv
/** \addtogroup cv_group */
/*@{*/

typedef unsigned  uint;

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
 
  //~erImage();
  CvRect  rectan;
  bool    drawing;
private:
  /**
     Methodes d acces
  **/ 
};


struct erCerc
{ erCerc();
  erCerc(int,int,int);
  CvPoint centro;
  int radio;
};

struct erCercleImg
{
  IplImage* image;
  CvPoint centeri;
  int radiusi;
  bool drawing;
};

struct erRect:public CvRect
{
  erRect(int,int,int,int);
};
// Quelques fonctions pour gerer l impression
/** \brief Impression d objet dans un flux*/
std::ostream& operator << ( std::ostream&, const erCerc&);
std::ostream& operator << ( std::ostream&, const erRect&);
std::ostream& operator << ( std::ostream&, const CvRect&);



// Quelques fonctions utiles d' OpenCv
/** \brief Fonction permettant de visualiser une Image a l aide
 d openCv
 */
void erShowImage(char* ,IplImage*);




// Quelques fonctions utiles d' OpenCv
/** \brief Fonction permettant de visualiser une Image a l aide
 d openCv
 */
void erShow2Image(char* ,IplImage*, char*, IplImage*);




/** \brief Fonction permettant de charge une  Image a l aide
 d openCv
 */
std::pair<erImage,bool> erLoadImage( char*);
//std::pair<erImage,bool> erLoadImage( char**);



/** \brief Fonction permettant de charger une serie d Image a l aide
 d openCv ayant comme extentions une succesion ordonne et continue de intieres
 */
std::pair<erImage,bool> erLoadImageSeries( char*, uint inc=1);


/** \brief Fonction permettant de charger une serie d Image a l aide
 d openCv ayant comme extentions une succesion ordonne et continue de intieres
 ATTENTION CET MODULE EST UNE MANIPULATION POUR TRAVAILLER DANS erCvAnalysis avec la fonction erCvAnalysisWeldPool::doIt */
std::string erLoadImageSeriesManipulationWeldPool( std::string, uint inc=1);



/** \brief Fonction permettant de sauvegarder une image a l aide
 d openCv
 */
void erSaveImage( IplImage*, char*, char*);





/** \brief Fonction permettant de sauvegarder une image a l aide
 d openCv
 */
void erSaveImage2( IplImage*,char*, char*, char*);



/** \brief Fonction permettant de sauvegarder une image a l aide
 d openCv
 */
void erSaveImage2Analysis( IplImage*,char*, std::string, char*);




erImage erCopyImage(erImage);





/** Fonction permettant de convertir une image en noir et blanc 
*/
//erImage    erConvertToBlackAndWhite( IplImage*);
IplImage*  erConvertToBlackAndWhite( IplImage*);





/** Fonction permettant d ecrire un ficher de sauvegarde des paramettres utilises pour chaque fonction
 */
void erWriteRecordFile( char*);





/** Fonction permettant d convertir une image 32bit en 8bit
 */
void erCvConvert32to8( IplImage*, IplImage*);





/** Fonction permettant d ecrir le nom d un ficher de sortie avec l extension correspondante
 */
//char* erEcrireNomFicher( char**, std::string);
char* erEcrireNomFichier( char*, char*, std::string);


/*@}*/
#endif
