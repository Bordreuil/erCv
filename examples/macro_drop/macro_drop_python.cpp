#include <erCv/erCv.hpp>
#include <erCv/erCv.hpp>
#include <erCv/erCvFilters.hpp>
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


/* Paramettres a introduir par l'usager dans l'appel du programe: */
/* 1- NOM choisi pour identifier les ficher de sortie,*/
/* 2- Adresse et nom de la premiere image a traiter*/
/* Pour gerer les increments des photos */
/* rien de tel qu une petite classe */

int main( int hola, char** file_name)
{
  //MacroDropAnalysis mda("peo","peo","../pictures/mcr_07032009_01593.bmp");
  //mda.defineParameterUI();
  
  /* Boucle de lecteure des images  */
//   clock_t tbeg = clock();
//   uint nIm(0);
//   while(true)
//     { 
//       erImage erb, bwb, eab; 
//       boost::tie(erb,loaded) = erLoadImageSeries( file_name,inc.inc());
//       if(!loaded) break;
//       bwb = erConvertToBlackAndWhite( &erb);        
//       //eo = ca.transform_image( bw);
//       eab = erDef_ROI( &bwb, &rect);    
//       erCvSmooth( &eab, &psmo);
//       erCvAdaptiveThreshold( &eab, &padt);
//       erCvSmooth( &eab, &psmo1);
//       erCvCanny( &eab, &pcan);
//       erSaveImage( &eab, file_name);
//       IsEqualTo is_equal_255( 255);
//       std::vector<CvPoint> cvPts; 
//       erExtractPoints( &eab, cvPts, is_equal_255);
//       erExtractionCurve( &eab, &cerc, file_name, cvPts, rect);
//       erEcriturePointPixel( cvPts, file_name); 
      
//       nIm++;
//       std::cout << "Image number :" << nIm << " passed: " << file_name[2] << "\n";
//       if (nIm>Nimax) break;
//     }
//     clock_t tfin = clock();
//     std::cout << "Temps en ms pour " << nIm << " images :" << (tfin-tbeg)  << std::endl;
  return(0);
};
