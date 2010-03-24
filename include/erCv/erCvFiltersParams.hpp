#ifndef _erCV_FILTERS_PARAMS_HPP_
#define _erCV_FILTERS_PARAMS_HPP_
#include<iostream>
/** \defgroup filters_params FiltersParams */
/** \ingroup filters  */

/** \addtogroup filters_params */
/*@{*/



/**
   \brief Structure contenant les parametre utiles pour 
   un lissage
 */


extern const int nbSmoothType;
extern char* smoothtype []; 

enum SmoothType {BLUR_NO_SCALE,
		BLUR,
		GAUSSIAN,
		MEDIAN, 
		BILATERAL
                 };

struct erSmootP
{
  int        size; /** < Beside size (in pixels) of smoothness region */
  SmoothType type; /** < Type of the smooth to be aplied */
};

//std::ostream& operator << (std::ostream&, erSmootP*);

/**
   \brief 
 */
struct erSobelP
{
  int trhX; /** < Order X derivated in sobel fonction */
  int trhY; /** < Order Y derivated in sobel fonction */
};



/**
   \brief
 */
struct erCannyP
{
  int trh1; /** < Threshold 1 to canny fonction */
  int trh2; /** < Threshold 2 to canny fonction */
};



/**
   \brief

 */
struct erThresP
{
  int trh1; /** < Threshold principal value in Threshold fonction */
  int trh2; /** < Threshold secondary value in Threshold fonction */
  int type; /** < Type of Threshold to be applied */
};



/**
   \brief

 */
// ATTENTION : Finir les commentaires
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
struct erDilatP
{
  int iter; /** < Iteration number to be applied dilate fonction */
};


/**
   \brief

 */
struct erErodeP
{
  int iter; /** < Iteration number to be applied erode fonction */
};




/*@}*/
#endif

