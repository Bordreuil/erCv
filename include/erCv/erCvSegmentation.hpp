#ifndef _ER_CV_SEGMENTATION_HPP_
#define _ER_CV_SEGMENTATION_HPP_
#include "erCvBase.hpp"
#include "erCvFilters.hpp"
#include "cv.h"


struct erDiffeP
{
  erAdThrP *adapthold;
  erThresP *threshold;
  IplImage *image;
  int type;
};


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
  int typeH;
  bool drawing;
  IplImage *image;
};





void erCvTemplate( IplImage*, erTemplP*);



#endif
