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
//std::string INFOFILE;

int main(int HOLA, char** file_name){
  /* Chargement et visualisation de l image de base */
  INFOFILE = file_name[1];
  erImage bw, ea, eb, ec;
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

  //erCalibration ca( "cuadro5.jpg", "rec_droite_256.bmp", 3, 3);
  //erCalibration ca( "../pictures/cuadro_droit_256.jpg", "../pictures/rec_droite_256.bmp", 3, 3); /* Calibration des images */  
  boost::tie(eb,loaded) = erLoadImage(file_name);
  //bw = ca.transform_image( eb);
  //erSaveImage( &bw, file_name);  
   IsEqualTo is_equal_255( 255); 
   /* Definition d un foncteur comme critere pour extraire des pixels suivant leur niveau de gris. cf->utilities/erPredicates.hpp */     
  std::vector< CvPoint> cvPts; 
  /* Definition du conteneur pour points au moment de l extraction */
   //erExtractPoints( &ea, cvPts, is_equal_255); /* Extraction */
   //erExtractionCurveUser( &ea, &cerc, file_name, cvPts, rect);
   //erEcriturePointPixel( cvPts, file_name); 
   //erConvertPixelToMks( ca.mm_per_pixels(), cvPts, file_name); /*Ecriture des donnes dans un ficher .txt */


  
  //   while(true) /* Boucle de lecteure des images  */
  //   {  
  //     boost::tie(er,loaded) = erLoadImageSeries( file_name);
  //     if(!loaded) break;
//       bw = erConvertToBlackAndWhite( &er);  
     
//       eo = ca.transform_image( bw);
//       ea = erDef_ROI( &eo, &rect);
    
//       erCvSmooth( &ea, &psmo);
     
//       erCvAdaptiveThreshold( &ea, &padt);
//       erCvSmooth( &ea, &psmo1);
     
//       erCvCanny( &ea, &pcan);
//       erSaveImage( &ea, file_name);
//       IsEqualTo is_equal_255( 255);
//       std::vector<CvPoint> cvPts; 
//       erExtractPoints( &ea, cvPts, is_equal_255);
//       erExtractionCurve( &ea, &cerc, file_name, cvPts, rect);
//       erEcriturePointPixel( cvPts, file_name); 
       
//     }

//   /* Ecriture des points extraits dans le fichier 'points_cv_filters_cv.dat' */
//   std::ofstream ocv( "results/points_cv_filters_cv.dat");
//   std::list<CvPoint2D32f>::iterator cvi;
//   for( cvi=cvPts.begin(); cvi!=cvPts.end(); cvi++)
//     {
//       ocv << cvi->x << " "<< cvi->y  << std::endl;
//     }
//   /* Definition du conteneur de points CGAL */
//   std::list<Point_2> cgalPts;
//   /* Conversion des points OpenCv en point CGAL */
//   cvPointsToCgal(cvPts.begin(),cvPts.end(),std::back_inserter(cgalPts));
//   /* Ecriture des points CGAL dans le fichier 'points_cv_filters_cgal.dat' */
//   std::ofstream op("results/points_cv_filters_cgal.dat");
//   std::list<Point_2>::iterator ci;
//   for(ci=cgalPts.begin();ci!=cgalPts.end();ci++)
//     {
//       op << *ci << std::endl;
//     }
//   /* Construction de l alpha shape a partir des points CGAL */
//   Alpha_shape_2 as2(cgalPts.begin(),cgalPts.end(),FT(50.));
//   std::list<Segment_2> segments;
//   alpha_edges( as2, std::back_inserter(segments));
//   /* Ecriture des cotes dans le fichier "edges_cv_filters.dat" */
//   std::ofstream ot("results/edges_cv_filters.dat");
//   std::list<Segment_2>::iterator  is;
//   for(is=segments.begin();is!=segments.end();is++)
//     {
//       ot << *is << std::endl;
//     };

  return 0;
};
