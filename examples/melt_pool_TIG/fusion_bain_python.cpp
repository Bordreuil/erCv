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
  rect.x=158;rect.y=121;rect.width=225;rect.height=225;
  //rect.x=50;rect.y=50;rect.width=150;rect.height=190;
  erWhitBP whi( 150, 150, 5, 100);
  erSmootP p1(BLUR,5), p2(MEDIAN,5);
  erCannyP cann(500,500);
  erDilatP dil(1); 
  erThresP thr(_THRESH_BINARY,200,255); //** <
  CvRect rec_tem;
  rec_tem.x = 9; rec_tem.y = 208; rec_tem.width = 8; rec_tem.height = 8;
  //rec_tem.x = 14; rec_tem.y = 20; rec_tem.width = 5; rec_tem.height = 5;
  erTemplP templ(SQDIFF_NORMED, rec_tem, true); 
  erAlphaP alp(1);
  erWeldPoolAnalysis wpa("full_bain_1");

  wpa.defineCalibration("calibration_source.jpg","calibration_target.bmp");
  wpa.defineParameters( rect, whi, p1, p2, cann, dil, thr, templ, alp);

  wpa.doIt( "example_full_bain_1.bmp");
  wpa.doIt( "example_full_bain_2.bmp");
  wpa.doIt( "example_full_bain_3.bmp");
  erSmootP p12(BLUR,7), p22(MEDIAN,7);
  erThresP thr2(_THRESH_BINARY,215,255); 
  wpa.defineParameters( rect, whi, p12, p22, cann, dil, thr2, templ, alp);
  wpa.doIt( "example_full_bain_4.bmp");
  
  return(0);
};
