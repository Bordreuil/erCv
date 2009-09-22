#ifndef _ER_CV_FILTERSUSERS_HPP_
#define _ER_CV_FILTERSUSERS_HPP_
#include <erCv/erCvFilters.hpp>
#include <erCv/erCvBase.hpp>






/** Permet d effectuer un filtrage par bordes en binaire sur l image (peramettres definies par l usager)
*/
void erCvCannyUser( IplImage*, p_canny*);



/** Permet de deriver l intensite de l image independament sur les axes X et Y (paramettres definies par l usager)
*/
void erCvSobelUser( IplImage*, p_sobel*);



/** Permet d effectuer une lissage sur l image (peramettres definies par l usager)
*/
void erCvSmoothUser( IplImage*, p_smooth*);



/** Permet de filtrer l image par seuils d intensite (peramettres definies par l usager)
 */
void erCvThresholdUser( IplImage*, p_threshold*);




/** Permet d filtrer l image par seuils d intensites adaptes par zones (peramettres definies par l usager)
 */
void erCvAdaptiveThresholdUser( Drawrec*, p_adaptivethreshold*);



/** Permet d effectuer un filtrage de l image en reagroupant les pixels dans cluosters d interet et en effectuant des liesons entre eux (peramettres definies par l usager)
 */
void erCvPyramidUser( IplImage*, p_pyramid*);



/** Permet d effectuer un filtrage de l image en reduissant le nombre de pixels avec noir (peramettres definies par l usager)
 */
void erCvDilateUser( IplImage*, p_dilate*);



/** Permet d effectuer un filtrage de l image en augmentant le nombre de pixels avec noir (peramettres definies par l usager)
 */
void erCvErodeUser( IplImage*, p_erode*);


#endif
