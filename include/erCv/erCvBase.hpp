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

/** 
    Encapsulation de la structure IplImage d openCv
    erImage derive de la classe IplImage, on peut utiliser l ensemble des fonctions
    d opencv directement avec un pointeur sur cette classe.
 */
class erImage : public IplImage
{
public:
  /** \brief Constructeur par defaul  */
  erImage();
  /** \brief Constructeur a partir du nom de l'image */
  erImage(char* );
  /** \brief Constructeur a partir du pointeur de l image */
  erImage(IplImage* );
  /** \brief Constructeur a partir de l image */
  erImage(IplImage);
  /** \brief Destructeur */ 
  //~erImage();
  CvRect  rectan; /** < Rectangle: CvRect,  demarquant une zone d interet dans l image */
  bool    drawing; /** < Si drawing = false =>  , si drawing = true => */
private:
  /**
     Methodes d acces
  **/ 
};



/** 
    Structure contenant le point de debut d une curve definie par le cercle du type CvCerc
 */
struct erCerc
{ 
  /** \brief Constructeur par defaul */
  erCerc();
  /** \brief Constructeur avec les paramettres du cercle */
  erCerc(int,int,int);
  CvPoint centro; /** < Coordones du centrer du cercle (x,y) */
  int radio; /** < Radio du cercle */
};


/** 
 */
struct erCercleImg
{
  IplImage* image;
  CvPoint centeri;
  int radiusi;
  bool drawing;
};


/**
   Structure contenant la zone d interet definie par un rectangle du type CvRect
*/
struct erRect:public CvRect
{
  /** \brief Constructeur avec les paramettres du rectangle */
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
    \param char*      : nom de l ecran ou apparaitra l image
    \param IplImage*  : Pointer vers l image
 */
void erShowImage(char* ,IplImage*);




// Quelques fonctions utiles d' OpenCv

/** \brief Fonction permettant de visualiser deux Images a l aide
    d openCv


    \param char*      : nom de l ecran ou apparaitra l image 1
    \param IplImage*  : Pointer vers l image 1
    \param char*      : nom de l ecran ou apparaitra l image 2
    \param IplImage*  : Pointer vers l image 2
 */
void erShow2Image(char* ,IplImage*, char*, IplImage*);




/** \brief Fonction permettant de charge une  Image a l aide
    d openCv
    \param char* : nom de l image
 */
std::pair<erImage,bool> erLoadImage( char*);
//std::pair<erImage,bool> erLoadImage( char**);



/** \brief Fonction permettant de charger une serie d Image a l aide
    d openCv ayant comme extentions une succesion ordonne et continue de intieres
    \param char*    : nom de l image
    \param unit     : Intiere donnant le pass dans la succesion 
 */
std::pair<erImage,bool> erLoadImageSeries( char*, uint inc=1);


/** \brief Fonction permettant de chercher une serie d Images a l aide
 d openCv ayant comme extention une succesion ordonne et continue de intieres
 La function reenvoi le nom de l image a charger. Cette image est donne par la succesion
 ATTENTION CET MODULE EST a utiliser sur erCvAnalysis  
    \param std::string    : nom de l image
    \param unit           : Intiere donnant le pass dans la succesion 
*/
std::string erLoadImageSeriesAnalysis( std::string, uint inc=1);



/** \brief Fonction permettant de sauvegarder une image a l aide
    d openCv
    \param IplImage*     : pointer vers l image
    \param char*         : nom de l image charge
    \param char*         : nom du ficher ou l image sera sauvegarde
 */
void erSaveImage( IplImage*, char*, char*);





/** \brief Fonction permettant de sauvegarder une image a l aide
    d openCv avec une nom-sufixe choisi par l utilisateur
    \param IplImage*     : pointer vers l image
    \param char*         : nom de l image charge
    \param char*         : nom du ficher ou l image sera sauvegarde
    \param char*         : extension sur le nom du ficher (example: nom_extension.png)
*/
void erSaveImage2( IplImage*,char*, char*, char*);



/** \brief Fonction permettant de sauvegarder une image a l aide
    d openCv a utiliser sur le module erCvAnalysis
    \param char*         : nom de l image charge
    \param std::string   : nom du ficher ou l image sera sauvegarde
    \param char*         : extension sur le nom du ficher (example: nom_extension.png)
 */
void erSaveImage2Analysis( IplImage*,char*, std::string, char*);



/**
   Focntion permettant de copier une image du type erImage dans une autre image de la meme clase erImage
   \param erImage  : struc de l image a copier
*/
erImage erCopyImage(erImage);





/** 
    Fonction permettant de convertir une image couleur (3 channal) en image des niveaux de gris (1 channal)
    \param IplImage*   : pointer vers l image a convertir
*/
IplImage*  erConvertToBlackAndWhite( IplImage*);





/** 
    Fonction permettant d ecrire un ficher de sauvegarde des paramettres utilises pour chaque fonction
    \param char* : nom du ficher
 */
void erWriteRecordFile( char*);





/** Fonction permettant d convertir une image 32bit en 8bit
    \param IplImage*  : pointer vers l image en 32bit
    \param IplImage*  : pointer vers l image en 8 bit
 */
void erCvConvert32to8( IplImage*, IplImage*);





/** 
    Fonction permettant d ecrir le nom d un ficher de sortie avec l extension correspondante
    \param char*       : nom du ficher de l image en tratement
    \param char*       : nom de base du ficher de l image de sorti
    \param std::string : nom de l extension 
*/
char* erEcrireNomFichier( char*, char*, std::string);


/*@}*/
#endif
