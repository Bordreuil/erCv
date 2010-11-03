#ifndef _ER_CV_SEGMENTATION_USER_HPP_
#define _ER_CV_SEGMENTATION_USER_HPP_
#include "erCv/erCvSegmentationParams.hpp"
#include "erCv/erCvBase.hpp"
#include "cv.h"



/** \brief
    Permmet de segmenter une image a partir d un echantillon ou zone template dans l image, en utilisant une criter de comparaison avec le reste de l image
    La dite zone est choisit par l usager
*/
IplImage* erCvTemplateUser( IplImage*, erTemplP*, bool with_trackbar = false);


/** \brief
    Une fois determine un type d histograme base sur le format coulor de l image. La fonction permmet de segmenter l image a partir d un echantillon choisit par l usager
    Le type d histograme ainsi comment l echantillon est choisit par l usager
*/
IplImage* erCvCallBackPatchProjectUser( IplImage*, erCallBP*, bool with_trackbar = false );



/** \brief
    Permmet de normalizer l intensite et incremente le contraste en equalisant l histograme d une image des niveaux de gris
*/
void erCvEqualizeHistUser( IplImage*, erEqualP*);


/** \brief
    Permet d effectuer un filtrage de l image en reagroupant les pixels dans clusters 
    d interet et en effectuant des liaisons entre eux
*/
void erCvPyramidUser( IplImage*, erPyramP*, bool with_trackbar = false);

/** \brief
    Permmet d identifier les contours dans une image en binaire
 */
void erCvFindContours( IplImage*, erFindcP*, bool with_trackbar = false);

// void erCvWatershed( IplImage*, erWaterP*);

/** \brief
    Permet de couvrir taches blanches (au desous du seuil) dans l image qui se trouvent entoure par des zones noir (au dessu du seuil)
*/
void erWhiteBlobCorrectionUser( IplImage*, erWhitBP*);

#endif
