#include <erCv/erCv.hpp>
#include <erCv/erCvFilters.hpp>
#include <erCv/utilities/erPredicates.hpp>
#include <erCv/erCvExtract.hpp>
#include <erCv/erCvToCgal.hpp>
#include <erCv/geometry/erCgalAlphaShape2.hpp>
#include<list>
#include<vector>
#include<fstream>
#include<iterator>
#include<boost/utility.hpp>
#include<erCv/graph/erConnectedSegments.hpp>
#include<ctime>
#include<time.h>
//std::string INFOFILE;

int main(int HOLA, char** file_name)
{
  std::cout <<"-----------------------------------------------\n\n";
  std::cout <<"\tMagic treatment for metal transfer\n\tBy Edward Romero\n\tNovember 2009\n\tLMGC/UM2/UM5508\n\tANR-TEMMSA\n\n";
  std::cout <<"-----------------------------------------------\n\n";
//   uint ninc,ndelta,every,Nimax;
//   std::cout << "Increment de photo:\n";
//   std::cin  >> ninc;
//   std::cout << "Toutes les n photos:\n";
//   std::cin >>   every;
//   std::cout << " increment de:\n";
//   std::cin >> ndelta;
//   std::cout << "Nombre max de photos a traiter:\n";
//   std::cin >> Nimax;
  /* Objet permettant de modifier l increment entre deux photos */
  //ImageIncrement inc(ninc,ndelta,every);

  /* Chargement et visualisation de l image de base */
  //INFOFILE = file_name[1];
   erImage bw, ea, eb, ec, ed;
   erImage pimg, bwpimg;
   CvRect rect;
   erCerc cerc;
   erDiffeP pdif;
   erTemplP ptem;
   erCallBP pcal;
   erSmootP psmo, psmo1;
   erCannyP pcan;
   erPyramP pyra;
   erThresP pthr;
   erAdThrP padt, padt1;
   erDilatP pdil;
   erErodeP pero;
   erSobelP psob;
   bool loaded;
  std::cout << " Avant calibration\n";
  erCalibration ca( "cuadro5.jpg", "cuadro5.jpg", 3, 3); /* Calibration des images */
  erImage pat = ca.get_patron();
  std::cout << "HOLA2" << std::endl;
  erShowImage("patron", &pat);
  erImage mes = ca.get_mesure();
  erShowImage("mesure",&mes);
  //boost::tie(ea,loaded) = erLoadImage(file_name);
  
  //eb = ca.transform_image(ea);
  //erSaveImage2( &eb, file_name, "cal");

  //erCvSmoothUser( &eb, &psmo);
  //erSaveImage2( &eb, file_name, "smo");
  //ec = erConvertToBlackAndWhite( &eb); /* Conversion en 8 bit single channel */ 
  
  //  ec = erCvTemplateUser( &eb, &ptem);
  //   erSaveImage2( &ec, file_name, "tem");
  
  //   erCvThresholdUser( &ec, &pthr);
  //   erSaveImage2( &ec, file_name, "thr");
  
  //   erCvCannyUser( &ec, &pcan);
  //   erSaveImage2( &ec, file_name, "can");
  
  //   IsEqualTo is_equal_255( 255); /* Definition d un foncteur comme critere pour extraire des pixels suivant leur niveau de gris. cf->utilities/erPredicates.hpp */     
  //   std::vector< CvPoint> cvPts; /* Definition du conteneur pour points au moment de l extraction */
  //   erExtractPoints( &ec, cvPts, is_equal_255, rect, 1); /* Extraction */
  //   std::list<Point_2> cgalPts;
  //   cvPointsToCgal( cvPts.begin(), cvPts.end(), std::back_inserter(cgalPts));
  //   Alpha_shape_2 as2( cgalPts.begin(), cgalPts.end(), FT(2));
  //   cgalPts.clear();
  //   std::list<Segment_2> segments;
  //   alpha_edges( as2, std::back_inserter(segments));
  //   std::string fileN = "test";
  //   //std::string base_edges = "results/";
  //   //std::string file = base_edges+fileN+".dat";
  //   std::string file = fileN+".dat";
  //   std::cout << file << std::endl; 
  //   std::ofstream ot( file.c_str());
  //   std::list<Segment_2>::iterator is;
  //   for( is = segments.begin(); is != segments.end(); is++)
  //     {
  //       ot << *is << std::endl;
  //     }
  //   segments.clear();  
  
  //   clock_t tbeg = clock();
  //   std::cout << "Temps image :" << tbeg  << std::endl;
  //erExtractionCurveUser( &ea, &cerc, file_name, cvPts, rect);
  //erEcriturePointPixel( cvPts, file_name); 
  //erConvertPixelToMks( ca.mm_per_pixels(), cvPts, file_name); /*Ecriture des donnes dans un ficher .txt */
  
  //   time_t tbeg = time(NULL);
  //   uint nIm(0);
  //   while(true) /* Boucle de lecteure des images  */
  //     {  
  //       boost::tie(eb,loaded) = erLoadImageSeries( file_name);
  //       if(!loaded) break;
  //       //       bw = erConvertToBlackAndWhite( &er);  
  //       //       eo = ca.transform_image( bw);
  //       //       ea = erDef_ROI( &eo, &rect);
  //       erCvSmooth( &eb, &psmo);
  //       //std::cout << "psmo.type= " << psmo.type << std::endl;
  //       //std::cout << "psmo.size= " << psmo.size << std::endl;
  //       ec = erCvTemplate( &eb, &ptem);
  //       //erShowImage( "prueba", &eb);
  //       erCvThreshold( &ec, &pthr);
  //       //       erCvAdaptiveThreshold( &ea, &padt);
  //       //       erCvSmooth( &ea, &psmo1);
  //       erCvCanny( &ec, &pcan);
  //       erSaveImage( &ec, file_name);
  //       IsEqualTo is_equal_255( 255);
  //       std::vector<CvPoint> cvPts; 
  //       erExtractPoints( &ec, cvPts, is_equal_255);
  //       std::list<Point_2> cgalPts;
  //       cvPointsToCgal( cvPts.begin(), cvPts.end(), std::back_inserter(cgalPts));
  //       Alpha_shape_2 as2( cgalPts.begin(), cgalPts.end(), FT(2));
  //       cgalPts.clear();
  //       std::list<Segment_2> segments;
  //       alpha_edges( as2, std::back_inserter(segments));
  //       std::string fifi(file_name[1]);
  //       std::string num=boost::lexical_cast<std::string>(nIm);
  //       if(num.size() < 2) num.insert(0,"0");
  //       std::string file = fifi+"_"+num+".seg";
  //       std::cout << file << " ecrit\n";
  //       std::ofstream ot(file.c_str());
  //       std::list<Segment_2>  out = get_connected_segments(segments.begin(),segments.end());
  //       std::cout << "Taille de out:" << out.size() << std::endl;
  //       for(is=out.begin();is!=out.end();is++)
  // 	{ 
  // 	  ot << *is << std::endl;
  // 	};
  //       segments.clear();
  //       //erExtractionCurve( &ea, &cerc, file_name, cvPts, rect);
  //       //erEcriturePointPixel( cvPts, file_name); 
  //       nIm++;
  //       if(nIm > Nimax) break;
  //     }
  //   std::cout << "Temps pour " << nIm << " images :" << time(NULL)-tbeg << std::endl;
  return(0);
}


