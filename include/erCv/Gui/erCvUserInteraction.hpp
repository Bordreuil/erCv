#ifndef _ERCV_USER_INTERACTION_HPP_
#define _ERCV_USER_INTERACTION_HPP_
#include <erCv/erCvBase.hpp>


/**
   \brief
 */
IplImage* erDef_ROIuser( erImage*, CvRect*, bool with_trackbar = false);



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
