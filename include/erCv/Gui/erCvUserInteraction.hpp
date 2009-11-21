#ifndef _ERCV_USER_INTERACTION_HPP_
#define _ERCV_USER_INTERACTION_HPP_
#include <erCv/erCvBase.hpp>


struct erCerc
{
  CvPoint centro;
  int radio;
};

struct erCercleImg
{
  IplImage* image;
  CvPoint centeri;
  int radiusi;
  bool drawing;
};

/**
   \brief
 */
IplImage* erDef_ROIuser( erImage*, CvRect*);

/**
   \brief
 */
IplImage* erDef_ROI( erImage*, CvRect*);

/**
   \brief
 */
void erRes_ROI_recons( IplImage*);

/**
   \brief
*/
std::pair< CvPoint, int> erCvDebutCurve( IplImage*);

#endif
