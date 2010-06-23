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
  CvRect rect;
  rect.x=20;rect.y=160;rect.width=230;rect.height=75;
  erCerc cerc(20,210,5);
  erSmootP p1(BLUR,7),p2(GAUSSIAN,5);
  erCannyP cann(355,355);
  erAdThrP adp(THRESH_BINARY,AM_MEAN,50,14,255); //** < 
  erMacroDropAnalysis mda("peo_1");
  mda.defineParameters(rect,cerc,p1,p2,cann,adp);
  std::string img_base="../pictures/macro_drop/MCR_hongo_";
  for(int i=1;i<17;i++)
      {
	std::string filename=img_base+boost::lexical_cast<std::string>(i)+".bmp";
	mda.doIt(filename);
      };
  mda.saveParameters("result/test.out");
  return(0);
};
