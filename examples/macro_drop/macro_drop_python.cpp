#include <erCv/erCv.hpp>
#include <erCv/erCv.hpp>
#include <erCv/erCvFilters.hpp>
#include <erCv/erCvFiltersParams.hpp>
#include <erCv/erCvAnalysis.hpp>
#include <erCv/utilities/erPredicates.hpp>
#include <erCv/erCvExtract.hpp>
#include <erCv/erCvToCgal.hpp>
#include <erCv/geometry/erCgalAlphaShape2.hpp>
#include<time.h>
#include<boost/lexical_cast.hpp>
/* Valeurs des paramettres a introduire, pour chaque fonction:
Smooth           : 7, 1 (0 pour OK)
AdaptiveThreshold: 1, 29, 1, 1 (0 pour OK)
Smooth2          : 7, 3 (0 pour OK)
Canny            : 355, 355 */


int main( int hola, char** file_name)
{

//-------ATTENTION paramettres pour le CVAnalysis de yo no se quien-------------/ 
//   CvRect rect;
//   rect.x=121;rect.y=110;rect.width=814;rect.height=220;
//   erCerc cerc(135,293,25);
//   erEqualP equ(0);
//   erSmootP p1(BLUR,7),p2(GAUSSIAN,5);
//   erCannyP cann(355,355);
//   erAdThrP adp(THRESH_BINARY,AM_MEAN,28,130,255); //** < 
//   erMacroDropAnalysis mda("AN_macro_drop");
//   mda.defineParameters(rect,cerc,p1,p2,cann,adp,equ);
//   std::string img_base="../pictures/macro_drop/MCR_hongo_1.bmp";
//   for(int i = 1; i < 15;i++)
//     {
//       std::string filename = erLoadImageSeriesManipulationWeldPool( img_base, 1);
//       std::cout << "file name: " << filename << std::endl;
//       std::cout << "hola0" << std::endl;
//       mda.doIt(filename);
//       img_base = filename;
//     };
//   mda.saveParameters( "result/test.out");

//-----------ATTENTION paramettres pour CvAnalysis de la macro-goutte-champignon--------/
  CvRect rect;
  rect.x = 160; rect.y = 126; rect.width = 140; rect.height = 89;
  erCerc cerc(160,193,2);
  erEqualP equ(0);
  erSmootP p1(BLUR,7),p2(GAUSSIAN,5);
  erCannyP cann(355,355);
  erAdThrP adp(THRESH_BINARY,AM_MEAN,28,130,255); //** < 
  erMacroDropAnalysis mda("AN_macro_drop");
  mda.defineParameters(rect,cerc,p1,p2,cann,adp,equ);
  std::string img_base="../pictures/macro_drop/MCR_hongo_1.bmp";
  for(int i = 1; i < 15;i++)
    {
      std::string filename = erLoadImageSeriesAnalysis( img_base, 1);
      std::cout << "file name: " << filename << std::endl;
      std::cout << "hola0" << std::endl;
      mda.doIt(filename);
      img_base = filename;
    };
  mda.saveParameters( "result/test.out");




//   for(int i=1;i<17;i++)
//       {
// 	std::string filename=img_base+boost::lexical_cast<std::string>(i)+".bmp";
// 	mda.doIt(filename);
//       };
//   mda.saveParameters("result/test.out");
  return(0);
};
