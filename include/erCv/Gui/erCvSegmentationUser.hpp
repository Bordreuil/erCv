#ifndef _ER_CV_SEGMENTATION_USER_HPP_
#define _ER_CV_SEGMENTATION_USER_HPP_
#include "erCv/erCvSegmentationParams.hpp"
#include "erCv/erCvBase.hpp"
#include "cv.h"


void erCvDifferencing( IplImage*, IplImage*);

IplImage* erCvTemplateUser( IplImage*, erTemplP*, bool with_trackbar = false);

IplImage* erCvCallBackPatchProjectUser( IplImage*, erCallBP*, bool with_trackbar = false );

void erCvEqualizeHistUser( IplImage*, erEqualP*);

void erCvPyramidUser( IplImage*, erPyramP*, bool with_trackbar = false);

void erCvFindContours( IplImage*, erFindcP*, bool with_trackbar = false);

void erCvWatershed( IplImage*, erWaterP*);

void erWhiteBlobCorrectionUser( IplImage*, erWhitBP*);

#endif
