#ifndef _ER_CV_FILTERS_HPP_
#define _ER_CV_FILTERS_HPP_

#include "erCvBase.hpp"


/** \defgroup filters erCvFilters */
/** \brief interface de filtres opencv dans erCv */




//** \addtogroup filters */
/*@{*/
/**
   \brief Structure contenant les parametre utiles pour 
   un lissage
 */

enum SmoothType {BLUR_NO_SCALE,
		BLUR,
		GAUSSIAN,
		MEDIAN, 
		BILATERAL
                 };

extern const int nbSmoothType;
extern char* smoothtype []; ;


struct erSmootP
{
  int        size; //** < Beside size (in pixels) of soomthness region 
  SmoothType type; //** < Type of the smooth to be aplied
};

/**
   \brief 
 */
struct erSobelP
{
  int trhX; //** < Order X derivated in sobel fonction */
  int trhY; //** < Order Y derivated in sobel fonction */
};

/**
   \brief
 */
struct erCannyP
{
  int trh1; //** < Threshold 1 to canny fonction */
  int trh2; //** < Threshold 2 to canny fonction */
};

/**
   \brief

 */
struct erThresP
{
  int trh1; //** < Threshold principal value in Threshold fonction */
  int trh2; //** < Threshold secondary value in Threshold fonction */
  int type; //** < Type of Threshold to be applied */
};

/**
   \brief

 */
struct erAdThrP
{
  int trhP;  //** <                           */
  int neig;  //** <                           */
  int trh0;  //** <                           */
  int type;  //** <                           */
  int adpt;  //** <                           */
};
/**
   \brief

 */

struct erPyramP
{
  int trh1; //** < Threshold value to link in pyramid fonction */
  int trh2; //** < Threshold value to clustering in pyramid fonction */
  int levl; //** < Number of level to pyramid be applied */
};


/**
   \brief

 */
struct erDilatP
{
  int iter; //** < Iteration number to be applied dilate fonction */
};

/**
   \brief

 */
struct erErodeP
{
  int iter; //** < Iteration number to be applied erode fonction */
};


/** \brief 
    Permet d effectuer un lissage et un filtrage sur l image 
*/
erImage erSmoothAndCanny( IplImage*, int , int );



/** \brief 
    Permet d effectuer un filtrage par bordes en binaire sur l image 
*/
void erCvCanny( IplImage*, erCannyP*);




/** 
    \brief Permet d effectuer une lissage sur l image 
*/
void erCvSmooth( IplImage*, erSmootP*);





/** \brief
    Permet d effectuer une lissage sur l image (parametres definies par l utilisateur)
*/
void erCvSobel( IplImage*, erSobelP*);



/** \brief
    Permet de filtrer l image par seuils d intensite
 */
void erCvThreshold( IplImage*, erThresP*);


/** \brief
    Permet d filtrer l image par seuils d intensites adaptes par zones 
 */
void erCvAdaptiveThreshold( IplImage* simg, erAdThrP* parm);



/** \bried
    Permet d effectuer un filtrage de l image en reagroupant les pixels dans clusters 
    d interet et en effectuant des liaisons entre eux
 */
void erCvPyramid( IplImage*, erPyramP*);



/** \brief
    Permet d effectuer un filtrage de l image en reduissant le nombre de pixels avec noir
 */
void erCvDilate( IplImage*,erDilatP*);



/** \brief
    Permet d effectuer un filtrage de l image en augmentant le nombre de pixels avec noir
 */
void erCvErode( IplImage*, erErodeP*);
/*@}*/

#endif
