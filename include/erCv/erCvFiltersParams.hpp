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

   Ajouter explication Edward!!!


 */
extern const int nbSmoothType;
extern char* smoothtype[]; 
enum SmoothType {BLUR_NO_SCALE, /** < 0 :   */
		 BLUR,          /** < 1 :   */
		 GAUSSIAN,      /** < 2 :   */
		 MEDIAN,        /** < 3 :   */
		 BILATERAL      /** < 4 :   */
};
struct erSmootP
{ 
  erSmootP();
  erSmootP(SmoothType,int);
  int        size; /** < Beside size (in pixels) of smoothness region */
  SmoothType type; /** < Type of the smooth to be aplied */
};
std::ostream& operator << (std::ostream&, const erSmootP);



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
{ erCannyP(int,int);
  erCannyP();
  int trh1; /** < Threshold 1 to canny fonction */
  int trh2; /** < Threshold 2 to canny fonction */
};
std::ostream& operator << (std::ostream&,const erCannyP);



/**
   \brief
   
*/
//enum Thres{}
enum ThresholdType{ _THRESH_BINARY=1,     /** < 1:   */
		    _THRESH_BINARY_INV=2, /** < 2:   */
		    _THRESH_TRUNC=3,      /** < 3:   */
		    _THRESH_TOZERO=4,     /** < 4:   */
		    _THRESH_TOZERO_INV=5  /** < 5:   */
};
extern char* thresholdtype[ ];
// ATTENTION : Finir les commentaires
struct erThresP
{
  erThresP(ThresholdType,int,int);
  erThresP();
  int trh1; /** < Threshold principal value in Threshold fonction */
  int trh2; /** < Threshold secondary value in Threshold fonction */
  ThresholdType type; /** < Type of Threshold to be applied */
};
//std::ostream& operator << (std::ostream&,const erThresP);



/**
   \brief

*/
//enum Adapt{};
enum AdaptiveThresholdType{THRESH_BINARY=1,     /** < 1:    */
			   THRESH_BINARY_INV=2  /** < 2:   */
};
enum AdaptiveMethodType{AM_MEAN=1,              /** < 1:   */
			AM_GAUSSIAN=2           /** < 2:   */
};
extern char* adaptivethresholdtype[];
extern char* adaptivemethodtype[];
// ATTENTION : Finir les commentaires
struct erAdThrP
{ 
  erAdThrP(AdaptiveThresholdType,AdaptiveMethodType,int,int,int);
  erAdThrP();
  int trhP;  //** <                           */
  int neig;  //** <                           */
  int trh0;  //** <                           */
  AdaptiveThresholdType type;  //** <                           */
  AdaptiveMethodType    adpt;  //** <                           */
};
std::ostream& operator << (std::ostream&,const erAdThrP);


/**
   \brief

 */
struct erDilatP
{
  erDilatP( int);
  erDilatP();
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

