#ifndef _ER_CV_SEGMENTATION_HPP_
#define _ER_CV_SEGMENTATION_HPP_
#include "erCvBase.hpp"
#include "erCvSegmentationParams.hpp"
#include "erCvFilters.hpp"
#include "cv.h"
#include<string>

// struct erDiffeP
// {
//   erAdThrP *adapthold;
//   erThresP *threshold;
//   IplImage *image;
//   int type;
// };


// struct erTemplP
// {
//   CvRect rectan;
//   int type;
//   bool drawing;
//   IplImage *image;
// };

// struct erCallBP
// {
//   CvRect rectan;
//   int type;
//   int typeH;
//   bool drawing;
//   IplImage *image;
// };


// struct erEqualP
// {
//   int applic;
// };


// /**
//    \brief

//  */
// struct erPyramP
// {
//   int trh1; /** < Threshold value to link in pyramid fonction */
//   int trh2; /** < Threshold value to clustering in pyramid fonction */
//   int levl; /** < Number of level to pyramid be applied */
// };



IplImage* erCvTemplate( IplImage*, erTemplP*);

void erCvEqualizeHist( IplImage*, erEqualP*);


/** \bried
    Permet d effectuer un filtrage de l image en reagroupant les pixels dans clusters 
    d interet et en effectuant des liaisons entre eux
 */
void erCvPyramid( IplImage*, erPyramP*);



void erWhiteBlobCorrection( IplImage*, erWhitBP*);

void erWhiteBlobDelete(std::string,erWhitBP);

#endif
