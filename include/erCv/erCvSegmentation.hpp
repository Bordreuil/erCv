#ifndef _ER_CV_SEGMENTATION_HPP_
#define _ER_CV_SEGMENTATION_HPP_
#include "erCvBase.hpp"
#include "erCvSegmentationParams.hpp"
#include "erCvFilters.hpp"
#include "cv.h"
#include<string>

/** \defgroup segmentation erCvSegmentation */
/** \brief interface d'algorithmes de segmentation openCV dans erCv */



/** \addtogroup segmentation
    /*@{*/

/** \brief
    Permmet de substraire une image A sur autre B d equal type et dimension (A-B=C)
*/
void erCvDifferencing( IplImage*, IplImage*);


/** \brief
    Permet de segmenter une image a partir d un echantillon ou zone template dans l image (voir erCvTemplateUser)
*/
IplImage* erCvTemplate( IplImage*, erTemplP*);


/** \brief
    Permet d'incrementer le contraste dans l image, en effectuant une normalizacion de l histograme
*/
void erCvEqualizeHist( IplImage*, erEqualP*);


/** \brief
    Permet d effectuer un filtrage de l image en reagroupant les pixels dans clusters 
    d interet et en effectuant des liaisons entre eux
 */
void erCvPyramid( IplImage*, erPyramP*);


/** \brief
    Permet de couvir les zones blanches (au desous du seuil) entoure par une zone noir (au dessu du seuil)
*/
void erWhiteBlobCorrection( IplImage*, erWhitBP*);


//void erWhiteBlobDelete(std::string,erWhitBP);

#endif
