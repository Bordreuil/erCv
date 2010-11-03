#ifndef _ERCV_USER_INTERACTION_HPP_
#define _ERCV_USER_INTERACTION_HPP_
#include <erCv/erCvBase.hpp>


/**
   \brief 
   Function qui permet a l usager de demarquer la zone d intreret a travers d un rectangle
   Si with_trackbar est true; la demarcation de la zone d interet s effectue a travers la souris en appuyant sur l image
   si non, il faut introduire les dimensions du rectangle 
 */
IplImage* erDef_ROIuser( erImage*, CvRect*, bool with_trackbar = false);



/**
   \brief
   Function qu utilise le rectagle definie en erDef_ROIuser pour demarquer la zone d interet
 */
IplImage* erDef_ROI( erImage*, CvRect*);



/**
   \brief
   Fonction qui permmet de destruir la zone d interet et revenier sur l image d origin
 */
void erRes_ROI_recons( IplImage*);



/**
   \brief
   Fonction qui permmet a l usager de marquer le debut d une corde ou ligne des pixels dans une image en binaire
*/
std::pair< CvPoint, int> erCvDebutCurve( IplImage*);

#endif
