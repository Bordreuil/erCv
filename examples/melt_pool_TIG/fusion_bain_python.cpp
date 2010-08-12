#include <erCv/erCv.hpp>
#include <erCv/erCv.hpp>
#include <erCv/erCvFilters.hpp>
#include <erCv/erCvFiltersParams.hpp>
#include <erCv/erCvSegmentationParams.hpp>
#include <erCv/erCvAnalysis.hpp>
#include <erCv/utilities/erPredicates.hpp>
//#include <erCv/erCvExtract.hpp>
#include <erCv/erCvToCgal.hpp>
#include <erCv/geometry/erCgalAlphaShape2.hpp>
#include <erCv/geometry/erCgalPolygon2.hpp>
#include<time.h>
#include<boost/lexical_cast.hpp>
/* Valeurs des paramettres a introduire, pour chaque fonction:
Smooth           : 7, 1 (0 pour OK)
AdaptiveThreshold: 1, 29, 1, 1 (0 pour OK)
Smooth2          : 7, 3 (0 pour OK)
Canny            : 355, 355 */


int main( int hola, char** file_name)
{ // Zone d interet dans l image retournee
  CvRect rect;
  rect.x=127;rect.y=82;rect.width=272;rect.height=296;
  //rect.x=50;rect.y=50;rect.width=150;rect.height=190;
  erSmootP p1(BLUR,5), p2(MEDIAN,13);
  erCannyP cann(355,355);
  erEqualP app(0); 
  erAdThrP adp(THRESH_BINARY,AM_MEAN,123,130,255); //** <
  CvRect rec_tem;
  rec_tem.x = 245; rec_tem.y = 279; rec_tem.width = 8; rec_tem.height = 7;
  //rec_tem.x = 14; rec_tem.y = 20; rec_tem.width = 5; rec_tem.height = 5;
  erTemplP templ(CCORR_NORMED, rec_tem, true); 
  erAlphaP alp(75);
  erWeldPoolAnalysis wpa("peo_1");

  wpa.defineCalibration("calibration_source.jpg","calibration_target.bmp");

  wpa.defineParameters( rect, p1, p2, app, cann, adp, templ, alp);

  wpa.doIt("imageExemple_3.bmp");
  wpa.doIt("imageExemple_2.bmp");
  wpa.doIt("imageExemple_1.bmp");
  //wpa.saveParameters("result/test.out");
  return(0);
};
