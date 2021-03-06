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
  rect.x = 154; rect.y = 61; rect.width = 273; rect.height = 159;
  erAdThrP adt( THRESH_BINARY, AM_MEAN, 42, 130, 255); 
  erSmootP p1(MEDIAN,9);
  erCannyP cann(500,500);
  erAlphaP alp(3);
  erLaserPrototypageAnalysis lpa("laser_prototypage");
 
  lpa.defineParameters_diffuse( rect, p1, cann, adt, alp);
 
  lpa.doIt_diffuse( "example_laser_prototypage_1.jpg");
 
  CvRect rect2;
  rect2.x = 177; rect2.y = 23; rect2.width = 194; rect2.height = 112;
  erAdThrP adt2( THRESH_BINARY, AM_MEAN, 19, 74, 255); 
  lpa.defineParameters_diffuse( rect2, p1, cann, adt2, alp);
  lpa.doIt_diffuse( "example_laser_prototypage_2.jpg");

  CvRect rect3;
  rect3.x = 347; rect3.y = 197; rect3.width = 348; rect3.height = 172;
  erAdThrP adt3( THRESH_BINARY, AM_MEAN, 0, 63, 255); 
  erAlphaP alp3(25);
  lpa.defineParameters_diffuse( rect3, p1, cann, adt3, alp3);
  lpa.doIt_diffuse( "example_laser_prototypage_3.jpg");

  CvRect rec_tem;
  rect.x = 89; rect.y = 591; rect.width = 342; rect.height = 222;
  rec_tem.x = 235; rec_tem.y = 125; rec_tem.width = 3; rec_tem.height = 3;
  erSmootP p451(BLUR,7), p452(MEDIAN,7);
  erDilatP dil(1); 
  erTemplP templ4(SQDIFF_NORMED, rec_tem, true); 
  erThresP thr4( THRESH_BINARY_, 87, 255); //** <
  lpa.defineParameters( rect, p451, p452, cann, dil, thr4,  templ4, alp);
  lpa.doIt( "example_laser_prototypage_4.jpg");

  rect.x = 388; rect.y = 365; rect.width = 278; rect.height = 182;
  rec_tem.x = 221; rec_tem.y = 144; rec_tem.width = 7; rec_tem.height = 5;
  erTemplP templ5(SQDIFF_NORMED, rec_tem, true); 
  //<<<<<<< .mine
  erThresP thr5( THRESH_BINARY_, 142, 255); //** <
  lpa.defineParameters( rect, p451, p452, cann, dil, thr5, templ5, alp);
  //=======
  //erThresP thr5( THRESH_BINARY_, 81, 255); //** <
  //erAlphaP alp2(2);
  //erCannyP cann2(500,500);
  //erSmootP p12(BLUR,5);
  //lpa.defineParameters( rect, p12, p2, cann2, dil, thr5, templ5, alp2);
  //>>>>>>> .r130
  lpa.doIt( "example_laser_prototypage_5.jpg");

  
  return(0);
};
