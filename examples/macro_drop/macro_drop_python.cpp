#include <erCv/erCv.hpp>
#include <erCv/erCv.hpp>
#include <erCv/erCvFilters.hpp>
#include <erCv/erCvAnalysis.hpp>
#include <erCv/utilities/erPredicates.hpp>
#include <erCv/erCvExtract.hpp>
#include <erCv/erCvToCgal.hpp>
#include <erCv/geometry/erCgalAlphaShape2.hpp>
#include<time.h>

/* Valeurs des paramettres a introduire, pour chaque fonction:
Smooth           : 7, 1 (0 pour OK)
AdaptiveThreshold: 1, 29, 1, 1 (0 pour OK)
Smooth2          : 7, 3 (0 pour OK)
Canny            : 355, 355 */


// <<<<<<< .mine



// struct MacroDropAnalysis:public Analysis
// {
//   MacroDropAnalysis( char* name, char* infofile, char* firstImage):Analysis( name, infofile, firstImage){};
//   bool defineParameterUI()
//   {
//  std::cout <<"-----------------------------------------------\n\n";
//   std::cout <<"\tMagic treatment for metal transfer\n\tBy Edward Romero\n\tNovember 2009\n\tLMGC/UM2/UM5508\n\tANR-TEMMSA\n\n";
//   std::cout <<"-----------------------------------------------\n\n";
//   uint ninc,ndelta,every,Nimax;
//   std::cout << "Increment de photo:";
//   std::cin  >> ninc;
//   std::cout << "Toutes les n photos:";
//   std::cin >>   every;
//   std::cout << " increment de:";
//   std::cin >> ndelta;
//   std::cout << "Nombre max de photos:";
//   std::cin >> Nimax;
  
//   /* Declaration de variables a utiliser par les fonctions */
//   INFOFILE = this->infoFile;
//   ImageIncrement inc(ninc,ndelta,every);
//   this->incImage = inc ;
//   erImage er, bw, eo, ea;
//   CvRect rect;
//   erCerc cerc; 
//   erSmootP psmo, psmo1;
//   erCannyP pcan;
//   erAdThrP padt;
//   bool loaded; 
//   std::list< CvPoint> cvPts;
//   std::list< CgPoint> cgPts;
//   std::list< CgSegmt> cgSeg;
//   char* file_name = firstImage;

//   boost::tie(er,loaded) = erLoadImage(file_name);
//   if(!loaded) return false;
//   bw = erConvertToBlackAndWhite( &er); /* Conversion en 8 bit single channel */
//   eo = bw; 

//   ea = erDef_ROIuser( &bw, &rect);
//   rectOI = rect;
//   erCvSmoothUser( &ea, &psmo);
//   param_smooth1 = psmo;
//   erCvAdaptiveThresholdUser( &ea, &padt);
//   param_adaptive_thershold = padt;
//   erCvSmoothUser( &ea, &psmo1);
//   param_smooth2 = psmo1;
//   erCvCannyUser( &ea, &pcan);
//   param_canny = pcan;

//   IsEqualTo is_equal_255( 255);
//   //std::vector< CvPoint> cvPts;

//   erExtractCvPoints( cvPts, &ea, is_equal_255, rect); /* Extraction */
//   erExtractCurveMacroDropUser( cvPts, &ea, rect, &cerc, file_name);
//   cercToStart = cerc;
//   char* nom = name;
//   erPrintCvPoint( cvPts, file_name, nom); 
//   return true;

//   };
 
//   CvRect         rectOI;
//   erCerc         cercToStart;
//   erSmootP       param_smooth1,param_smooth2;
//   erCannyP       param_canny;
//   erAdThrP       param_adaptive_thershold;
// };


// =======
// >>>>>>> .r61
/* Paramettres a introduir par l'usager dans l'appel du programe: */
/* 1- NOM choisi pour identifier les ficher de sortie,*/
/* 2- Adresse et nom de la premiere image a traiter*/
/* Pour gerer les increments des photos */
/* rien de tel qu une petite classe */

int main( int hola, char** file_name)
{
  CvRect rect;
  rect.x=20;rect.y=160;rect.width=230;rect.height=75;
  erCerc cerc(20,210,5);
  erSmootP p1(BLUR,7),p2(GAUSSIAN,5);
  erCannyP cann(355,355);
  erAdThrP adp(THRESH_BINARY,AM_MEAN,50,14,255); //** < 
  erMacroDropAnalysis mda("peo","peo","test_000.bmp");
  mda.defineParameter(rect,cerc,p1,p2,cann,adp);
  mda.doIt("test_000.bmp");

  return(0);
};
