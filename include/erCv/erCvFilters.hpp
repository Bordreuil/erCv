#ifndef _ER_CV_FILTERS_HPP_
#define _ER_CV_FILTERS_HPP_

#include "erCvBase.hpp"





struct Drawrec
{
  CvRect rectan;
  IplImage *image;
  bool drawing;
};



struct p_smooth
{
  int size; //Beside size (in pixels) of soomthness region 
  int type; //Type the smooth to be aplied
};


struct p_sobel
{
  int trhX; //Order X derivated in sobel fonction
  int trhY; //Order Y derivated in sobel fonction
};


struct p_canny
{
  int trh1; //Threshold 1 to canny fonction
  int trh2; //Threshold 2 to canny fonction
};




struct p_threshold
{
  int trh1; //Threshold principal value in Threshold fonction
  int trh2; //Threshold secondary value in Threshold fonction
  int type; //Type of Threshold to be applied
};


struct p_adaptivethreshold
{
  int trhP;
  int neig;
  int trh0;
  int type;
  int adpt;
};


struct p_pyramid
{
  int trh1; //Threshold value to link in pyramid fonction
  int trh2; //Threshold value to clustering in pyramid fonction
  int levl; //Number of level to pyramid be applied
};


struct p_dilate
{
  int iter; //Iteration number to be applied dilate fonction
};


struct p_erode
{
  int iter; //Iteration number to be applied erode fonction
};







/** Permet d effectuer un lissage et un filtrage sur l image 
*/
erImage erSmoothAndCanny( IplImage*, int , int );



/** Permet d effectuer un filtrage par bordes en binaire sur l image 
*/
void erCvCanny( IplImage*, p_canny*);




/** Permet d effectuer une lissage sur l image 
*/
void erCvSmooth( IplImage*, p_smooth*);





/** Permet d effectuer une lissage sur l image (peramettres definies par l usager)
*/
void erCvSobelUser( IplImage*, p_sobel*);



/** Permet de filtrer l image par seuils d intensite
 */
void erCvThreshold( IplImage*, p_threshold*);


/** Permet d filtrer l image par seuils d intensites adaptes par zones 
 */
void erCvAdaptiveThreshold( IplImage* simg, p_adaptivethreshold* parm);



/** Permet d effectuer un filtrage de l image en reagroupant les pixels dans cluosters d interet et en effectuant des liesons entre eux
 */
void erCvPyramid( IplImage*, p_pyramid*);



/** Permet d effectuer un filtrage de l image en reduissant le nombre de pixels avec noir
 */
void erCvDilate( IplImage*, p_dilate*);



/** Permet d effectuer un filtrage de l image en augmentant le nombre de pixels avec noir
 */
void erCvErode( IplImage*, p_erode*);


#endif
