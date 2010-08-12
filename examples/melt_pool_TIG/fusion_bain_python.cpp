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
{
  CvRect rect;
  rect.x=117;rect.y=102;rect.width=301;rect.height=273;
  erSmootP p1(BLUR,7), p2(GAUSSIAN,5);
  erCannyP cann(355,355);
  erEqualP app(0); 
  erAdThrP adp(THRESH_BINARY,AM_MEAN,50,14,255); //** <
  CvRect rec_tem;
  rec_tem.x = 142; rec_tem.y = 175; rec_tem.width = 7; rec_tem.height = 6;
  erTemplP templ(CCORR_NORMED, rec_tem, true); 
  erAlphaP alp(1.);
  erWeldPoolAnalysis wpa("peo_1");

  //wpa.define_calibration("calibration_source.jpg","calibration_target.bmp");

  wpa.defineParameters( rect, p1, p2, app, cann, adp, templ, alp);
  std::string filename = "imageExemple_1.bmp";  
  std::cout << "Param defined" << std::endl;
  wpa.doIt(filename);
  //wpa.saveParameters("result/test.out");
  return(0);
};
