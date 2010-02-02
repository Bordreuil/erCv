#ifndef _ER_CV_SEGMENTATION_USER_HPP_
#define _ER_CV_SEGMENTATION_USER_HPP_
#include "erCv/erCvSegmentation.hpp"
#include "erCv/erCvBase.hpp"
#include "cv.h"


void erCvDifferencing( IplImage*, IplImage*);

IplImage* erCvTemplateUser( IplImage*, erTemplP*);

IplImage* erCvCallBackPatchProjectUser( IplImage*, erCallBP* );


#endif
