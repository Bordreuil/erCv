#ifndef _ER_CV_SEGMENTATION_HPP_
#define _ER_CV_SEGMENTATION_HPP_
#include "erCvBase.hpp"
#include "cv.h"


struct erTemplP
{
  CvRect rectan;
  int type;
  bool drawing;
  IplImage *image;
};



struct erCallBP
{
  CvRect rectan;
  int type;
};



//void erCvDifferencing( IplImage*, IplImage*);

void erCvTemplate( IplImage*, erTemplP*);

//IplImage* erCvCallBackPatchProject( IplImage*);


#endif
