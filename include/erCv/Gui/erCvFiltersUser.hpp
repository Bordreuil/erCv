#ifndef _ER_CV_FILTERSUSERS_HPP_
#define _ER_CV_FILTERSUSERS_HPP_
#include <erCv/erCvFilters.hpp>
#include <erCv/erCvBase.hpp>






/** \brief Permet d effectuer un filtrage par bordes en binaire sur l image (peramettres definies par l usager)
*/
void erCvCannyUser( IplImage*, erCannyP*, bool with_trackbar = false);



/** \brief Permet de deriver l intensite de l image independament sur les axes X et Y (paramettres definies par l usager)
*/
void erCvSobelUser( IplImage*, erSobelP*);



/** \brief Permet d effectuer une lissage sur l image (peramettres definies par l usager)
*/
void erCvSmoothUser( IplImage*, erSmootP*);



/** \brief
    Permet de filtrer l image par seuils d intensite (peramettres definies par l usager)
 */
void erCvThresholdUser( IplImage*, erThresP*, bool with_trackbar = false);




/** \brief Permet d filtrer l image par seuils d intensites adaptes par zones (peramettres definies par l usager)
 */
void erCvAdaptiveThresholdUser( IplImage*, erAdThrP*, bool with_trackbar = false);




/**  \brief  Permet d effectuer un filtrage de l image en reduissant le nombre de pixels avec noir (peramettres definies par l usager)
 */
void erCvDilateUser( IplImage*, erDilatP*);



/**  \brief Permet d effectuer un filtrage de l image en augmentant le nombre de pixels avec noir (peramettres definies par l usager)
 */
void erCvErodeUser( IplImage*, erErodeP*);


#endif
