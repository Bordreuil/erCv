#include <erCv/erCvFilters.hpp>
#include <erCv/utilities/erPredicates.hpp>
#include <erCv/erCvExtract.hpp>
#include <erCv/erCvToCgal.hpp>
#include <erCv/geometry/erCgalAlphaShape2.hpp>
#include<list>
#include<fstream>
#include<iterator>

std::string INFOFILE;

int main(int HOLA, char** file_name){
  /* Chargement et visualisation de l image de base */
  INFOFILE = file_name[1];
  erImage er    = erLoadImage(file_name[2]);
  //erShowImage( "base Image", &er);
  erImage bw    = erConvertToBlackAndWhite( &er); /* Conversion en 8 bit single channel */
  erImage ercan = erSmoothAndCanny( &bw, 200, 1);    /* Smooth and Canny sur l image convertie */
  erShowImage("after Canny",&ercan);    
  cvWaitKey();
  /* 
     Definition d un foncteur comme critere pour extraire 
     des pixels suivant leur niveau de gris.

     cf -> utilities/erPredicates.hpp
     
   */
  IsEqualTo is_equal_255(255);      
  /* Definition du conteneur pour points au moment de l extraction */
  std::list<CvPoint2D32f> cvPts;
  /* Extraction */
  erExtractPoints(&ercan,cvPts,is_equal_255);
  /* Ecriture des points extraits dans le fichier 'points_cv_filters_cv.dat' */
  std::ofstream ocv("results/points_cv_filters_cv.dat");
  std::list<CvPoint2D32f>::iterator cvi;
  for(cvi=cvPts.begin();cvi!=cvPts.end();cvi++)
    {
      ocv << cvi->x << " "<< cvi->y  << std::endl;
    }
  /* Definition du conteneur de points CGAL */
  std::list<Point_2> cgalPts;
  /* Conversion des points OpenCv en point CGAL */
  cvPointsToCgal(cvPts.begin(),cvPts.end(),std::back_inserter(cgalPts));
  /* Ecriture des points CGAL dans le fichier 'points_cv_filters_cgal.dat' */
  std::ofstream op("results/points_cv_filters_cgal.dat");
  std::list<Point_2>::iterator ci;
  for(ci=cgalPts.begin();ci!=cgalPts.end();ci++)
    {
      op << *ci << std::endl;
    }
  /* Construction de l alpha shape a partir des points CGAL */
  Alpha_shape_2 as2(cgalPts.begin(),cgalPts.end(),FT(50.));
  std::list<Segment_2> segments;
  alpha_edges( as2, std::back_inserter(segments));
  /* Ecriture des cotes dans le fichier "edges_cv_filters.dat" */
  std::ofstream ot("results/edges_cv_filters.dat");
  std::list<Segment_2>::iterator  is;
  for(is=segments.begin();is!=segments.end();is++)
    {
      ot << *is << std::endl;
    };

  return 0;
};
