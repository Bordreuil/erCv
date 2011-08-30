#include <erCv/erCv.hpp>
#include <erCv/erCvFilters.hpp>
#include <erCv/utilities/erPredicates.hpp>
#include <erCv/erCvExtract.hpp>
#include <erCv/erCvToCgal.hpp>
#include <erCv/geometry/erCgalAlphaShape2.hpp>
#include <erCv/geometry/erCgalPolygon2.hpp>
#include<list>
#include<vector>
#include<fstream>
#include<iterator>
#include<boost/utility.hpp>
#include<erCv/graph/erConnectedSegments.hpp>
#include <erCv/geometry/erGeometricalCharacteristics.hpp>
#include<ctime>
#include<time.h>
//std::string INFOFILE;

int main(int HOLA, char** file_name)
{
  std::cout <<"-----------------------------------------------\n\n";
  std::cout <<"\tMagic treatment for weld pool \n\tBy Edward Romero\n\tNovember 2009\n\tLMGC/UM2/UM5508\n\tANR-TEMMSA\n\n";
  std::cout <<"-----------------------------------------------\n\n";
  uint ninc,ndelta,every,Nimax;
  std::cout << "Increment de photo:\n";
  //std::cin  >> ninc;
  ninc = 1;
  std::cout << "Toutes les n photos:\n";
  //std::cin >>   every;
  every = 1;
  std::cout << " increment de:\n";
  //std::cin >> ndelta;
  ndelta = 1;
  std::cout << "Nombre max de photos a traiter:\n";
  //std::cin >> Nimax;
  Nimax = 1;
  /* Objet permettant de modifier l increment entre deux photos */
  erImageIncrement inc(ninc,ndelta,every);

  /* Chargement et visualisation de l image de base */
  char* exit = file_name[1];
  char* name = file_name[2];
  erImage bw, ea, eb, ec, ed, ee, ef;
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
  erEqualP pequ;
  erAlphaP palp;
  erFindcP pfin;
  //erWaterP pwat;
  erWhitBP pwhi;
  bool loaded;

  std::list< CvPoint> cvPts;
  std::list< CgalPoint> cgalPts, cgalPts2;
  std::list< CgalSegmt> cgalSeg, bgraphSeg;
  //std::list<bgraphSegmen> bgraphSeg;
  
  erCalibration ca( "cuadro5-rescale-511.jpg", "rec_droite_256_2.bmp", 3, 3); /* Calibration des images */
  
  boost::tie(ea,loaded) = erLoadImage(name);

  eb = erConvertToBlackAndWhite( &ea); /* Conversion en 8 bit single channel */ 
  
  //erCvSmoothUser( &eb, &psmo);
  erWhiteBlobCorrectionUser( &eb, &pwhi);

  std::cout << "que peo" << std::endl;

  ec = ca.transform_image(eb);
  erSaveImage2( &eb, name, exit, "tra");
  std::cout << "que peo es" << std::endl;
  /* Definision de la zone d'interet ou on souhaite travailler */
  ed = erDef_ROIuser( &ec, &rect, true);
  erSaveImage2( &ec, name, exit, "roi"); 
  //erCvEqualizeHistUser( &ed, &pequ);
  erCvCannyUser( &ed, &pcan);
  //erCvSmoothUser( &ed, &psmo);
  //erCvPyramidUser( &ec, &pyra, true);
  erCvDilateUser( &ed, &pdil);
  //erCvEqualizeHistUser( &ed, &pequ);
  erCvSmoothUser( &ed, &psmo1);
  //ee = erCvTemplateUser( &ed, &ptem, true);
  //erSaveImage2( &ec, file_name, "tem");
  //erCvEqualizeHistUser( &ee, &pequ);
  //ef = erCvTemplateUser( &ee, &ptem, true);
  erCvSmoothUser( &ed, &psmo1);
  ee = erCvTemplateUser( &ed, &ptem, true);
  //ee = ed;
  //ee = erCvCallBackPatchProjectUser( &ed, &pcal, true);
  erCvThresholdUser( &ee, &pthr, true);
  //erSaveImage2( &ec, file_name, "thr");
  
  erCvCannyUser( &ee, &pcan);
  //erSaveImage2( &ee, name, exit, "can");
 
  //erCvFindContours( &ee, &pfin, true);
  //_________________________________________________________________________________________________
  IsEqualTo is_equal_255(255);
  erExtractCvPoints( cvPts, &ee, is_equal_255, rect); /* Extraction */
  erPrintCvPoint( cvPts, name, exit);
  std::cout << "cvPts.size: " << cvPts.size() << std::endl;

  convertCvToCgalpoints( cvPts, cgalPts);
 
  alpha_edges_user( cgalPts, cgalSeg,  &palp);
  //erPrintCgalPoint( cgalSeg, name, exit);
  std::cout << "cgalSeg.size: " << cgalSeg.size() << std::endl;

  largestClosedPolygon( cgalSeg, bgraphSeg);
  erPrintCgalPoint( bgraphSeg, name, exit);
  std::cout << "bgraphSeg.size: " << bgraphSeg.size() << std::endl;

  polygon_creation_user( bgraphSeg, cgalPts2);
  //erPrintCgalPoint( cgalPts2, name, exit);
  std::cout << "cgPts2.size: " << cgalPts2.size() << std::endl;
  //_________________________________________________________________________________________________
//   if(output_geometry_characteristics && bgraphSeg.size() > 6)
//     {
//       std::list<CgalTrian> triangs=erGeometryExtractTriangles(bgraphSeg.begin(),bgraphSeg.end());
//       double area   = getArea(triangs.begin(),triangs.end());
//       CgalLine  line;
//       CgalPoint pt;
//       CgalFTrai fit = linear_least_squares_fitting_2(triangs.begin(),triangs.end(),line,pt,CGAL::Dimension_tag<2>());	
//       std::ofstream ot(output_geometry_file.c_str(),std::ios_base::app);
//       CgalVect vect=line.to_vector();
//       ot << std::setprecision(10) << fich << "\t" << pt.x() << "\t" << pt.y() << "\t" << area << "\t" << vect.x() << "\t" << vect.y() <<"\t" << fit << std::endl;    
//     };
  //std::cout << "cgalSeg.size: " << cgalSeg.size() << std::endl;
  
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
  //erExtractCurveMacroDropUser( &ea, &cerc, file_name, cvPts, rect);
  //erPrintCgalPoint( cgalSeg, name, exit); 
  //erConvertPixelToMks( ca.mm_per_pixels(), cvPts, file_name); /*Ecriture des donnes dans un ficher .txt */
  
//   cvPts.clear();
//   time_t tbeg = time(NULL);
//   uint nIm(0);
//   while(true) /* Boucle de lecteure des images  */
//     {  
//       boost::tie(ea,loaded) = erLoadImageSeries( file_name);
//       if(!loaded) break;
      
//       //eb = ca.transform_image( ea);
//       //ec = erConvertToBlackAndWhite( &eb);
//       erCvPyramid( &ec, &pyra);
      
//       ed = erDef_ROI( &ec, &rect);
//       erCvEqualizeHist( &ed, &pequ);
//       //erCvSmooth( &ec, &psmo);
//       //       //std::cout << "psmo.type= " << psmo.type << std::endl;
//       //       //std::cout << "psmo.size= " << psmo.size << std::endl;
//       ee = erCvTemplate( &ed, &ptem);
//       //erSaveImage2( &ec, file_name, "tem");
//       //       erCvThreshold( &ec, &pthr);
      
//       erCvAdaptiveThreshold( &ee, &padt);
//       //erSaveImage2( &ec, file_name, "ada");
//       //       //       erCvSmooth( &ea, &psmo1);
//       erCvCanny( &ee, &pcan);
//       erSaveImage2( &ee, file_name, "can");
      
//       erExtractPoints( &ee, cvPts, rect);
//       //             std::list<Point_2> cgalPts;
//       //             cvPointsToCgal( cvPts.begin(), cvPts.end(), std::back_inserter(cgalPts));
//       //             Alpha_shape_2 as2( cgalPts.begin(), cgalPts.end(), FT(2));
//       //             cgalPts.clear();
//       //             std::list<Segment_2> segments;
//       //             alpha_edges( as2, std::back_inserter(segments));
//       //             std::string fifi(file_name[1]);
//       //             std::string num=boost::lexical_cast<std::string>(nIm);
//       //             if(num.size() < 2) num.insert(0,"0");
//       //             std::string file = fifi+"_"+num+".seg";
//       //             std::cout << file << " ecrit\n";
//       //             std::ofstream ot(file.c_str());
//       //             std::list<Segment_2>  out = get_connected_segments(segments.begin(),segments.end());
//       //             std::cout << "Taille de out:" << out.size() << std::endl;
//       //             for(is=out.begin();is!=out.end();is++)
//       //       	{ 
//       //       	  ot << *is << std::endl;
//       //       	};
//       //             segments.clear();
//       //	    ;
//       erEcriturePointPixel( cvPts, file_name); 
//       nIm++;
//       if(nIm > Nimax) break;
//     }
//   std::cout << "Temps pour " << nIm << " images :" << time(NULL)-tbeg << std::endl;
  return(0);
}


