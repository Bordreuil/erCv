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
  rect.x = 143; rect.y = 29; rect.width = 270; rect.height = 173;
  erSmootP p1(BLUR,7), p2(MEDIAN,7);
  erCannyP cann(500,500);
  erDilatP dil(1); 
  erThresP thr( THRESH_BINARY_, 82, 255); //** <
  CvRect rec_tem;
  rec_tem.x = 171; rec_tem.y = 124; rec_tem.width = 5; rec_tem.height = 5;
  erTemplP templ(SQDIFF_NORMED, rec_tem, true); 
  erAlphaP alp(1);
  erLaserPrototypageAnalysis lpa("laser_prototypage");
  lpa.defineParameters( rect, p1, p2, cann, dil, thr, templ, alp);
  lpa.doIt( "example_laser_prototypage_1.jpg");

  CvRect rect2;
  rect2.x = 168; rect2.y = 11; rect2.width = 222; rect2.height = 133;
  CvRect rec_tem2;
  rec_tem2.x = 144; rec_tem2.y = 89; rec_tem2.width = 3; rec_tem2.height = 3;
  erTemplP templ2(SQDIFF_NORMED, rec_tem2, true); 
  erThresP thr2( THRESH_BINARY_, 11, 255); //** <
  lpa.defineParameters( rect2, p1, p2, cann, dil, thr2, templ2, alp);
  lpa.doIt( "example_laser_prototypage_2.jpg");

  rect.x = 354; rect.y = 191; rect.width = 340; rect.height = 178;
  rec_tem.x = 200; rec_tem.y = 111; rec_tem.width = 3; rec_tem.height = 3;
  erTemplP templ3(SQDIFF_NORMED, rec_tem, true); 
  erThresP thr3( THRESH_BINARY_, 125, 255); //** <
  lpa.defineParameters( rect, p1, p2, cann, dil, thr3, templ3, alp);
  lpa.doIt( "example_laser_prototypage_3.jpg");

  rect.x = 89; rect.y = 591; rect.width = 342; rect.height = 222;
  rec_tem.x = 235; rec_tem.y = 125; rec_tem.width = 3; rec_tem.height = 3;
  erTemplP templ4(SQDIFF_NORMED, rec_tem, true); 
  erThresP thr4( THRESH_BINARY_, 87, 255); //** <
  lpa.defineParameters( rect, p1, p2, cann, dil, thr4, templ4, alp);
  lpa.doIt( "example_laser_prototypage_4.jpg");

  rect.x = 382; rect.y = 336; rect.width = 299; rect.height = 219;
  rec_tem.x = 229; rec_tem.y = 167; rec_tem.width = 3; rec_tem.height = 3;
  erTemplP templ5(SQDIFF_NORMED, rec_tem, true); 
  erThresP thr5( THRESH_BINARY_, 80, 255); //** <
  lpa.defineParameters( rect, p1, p2, cann, dil, thr5, templ5, alp);
  lpa.doIt( "example_laser_prototypage_5.jpg");

  
  return(0);
};
