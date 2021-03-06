#include <erCv/erCv.hpp>
#include <erCv/erCv.hpp>
#include <erCv/erCvFilters.hpp>
#include <erCv/utilities/erPredicates.hpp>
#include <erCv/erCvExtract.hpp>
#include <erCv/erCvToCgal.hpp>
#include <erCv/geometry/erCgalAlphaShape2.hpp>
#include<erCv/graph/erConnectedSegments.hpp>
#include<ctime>

/* Valeurs des paramettres a introduire, pour chaque fonction:
Smooth           : 7, 1 (0 pour OK)
AdaptiveThreshold: 1, 29, 1, 1 (0 pour OK)
Smooth2          : 7, 3 (0 pour OK)
Canny            : 355, 355 


// Attention ENCORE EN DEVELOPPEMENT
// Attention ENCORE EN DEVELOPPEMENT


/* Paramettres a introduir par l'usager dans l'appel du programe: */
/* 1- NOM choisi pour identifier les ficher de sortie,*/
/* 2- Adresse et nom de la premiere image a traiter*/





int main( int hola, char** file_name)
{
  std::cout <<"-----------------------------------------------\n\n";
  std::cout <<"\tMagic treatment for metal transfer\n\tBy Edward Romero\n\tNovember 2009\n\tLMGC/UM2/UM5508\n\tANR-TEMMSA\n\n";
  std::cout <<"-----------------------------------------------\n\n";
  uint ninc,ndelta,every,Nimax;
  std::cout << "Increment de photo:\n";
  std::cin  >> ninc;
  std::cout << "Toutes les n photos:\n";
  std::cin >>   every;
  std::cout << " increment de:\n";
  std::cin >> ndelta;
  std::cout << "Nombre max de photos a traiter:\n";
  std::cin >> Nimax;
  /* Objet permettant de modifier l increment entre deux photos */
  erImageIncrement inc(ninc,ndelta,every);

  /* Declaration de variables a utiliser par les fonctions */
  char* exit = file_name[1];
  char* name = file_name[2];
  std::cout << exit << std::endl;
  erImage er, bw, eo, ea;
  CvRect rect;
  erCerc cerc; 
  erSmootP psmo, psmo1;
  erCannyP pcan;
  erAdThrP padt;
  erAlphaP palp;
  std::list< CvPoint> cvPts;
  std::list< CgalPoint> cgalPts;
  std::list< CgalSegmt> cgalSeg, bgraphSeg;
  bool loaded;

  
  /* Construction matrix de calibracion de l'image et regle de conversion pixel->mm */
  /* Premiere Image a charger: Patron construite sur l'ordinateur */
  /* Seconde Image a charger: Temoin messure dans l'xperience*/
  //erCalibration ca( "cuadro6.jpg", "diferent4.jpg", 3, 3); /* Calibration des images */
  
  /* Chargement de la premiere image a travailler et conversion a 8bit*/

  boost::tie(er,loaded) = erLoadImage( name);
  if(!loaded) return 0;
  std::cout << "Image :" << name << " chargee\n";
  bw = erConvertToBlackAndWhite( &er); /* Conversion en 8 bit single channel */

  /* Conversion de l'image du RGB->GRIS */
  //eo = bw; //ca.transform_image( bw);

  /* Definision de la zone d'interet ou on souhaite travvailler */
  ea = erDef_ROIuser( &bw, &rect);

  /* Debut du trataiment de l'image par methodes de filtrage optiques */
  /* Pour reduire la granulosite issue du bruit dans les pixels et la non homogenite de l'eclairage sur l'image;*/
  /* l'image est lisse avec un filtre Smooth du type BLUR (moyennage standart)*/
  std::cout << "Before Smooth User\n";
  erCvSmoothUser( &ea, &psmo);
  
  /* Dans les zones affectes par la procedure d'ombroscopie, des inegalites dans l'intensite de niveaux de gris sont observes. */
  /* Pour faire resortir les bordes principaux (par contraste) entres les zones zommbres et eclaires, */
  /* un methode de filtrage par seuil, adapte par zone, est utilise */
  erCvAdaptiveThresholdUser( &ea, &padt);

  /* Le Sueillage par zones fait aussi resortir les bordes a l'interior des zones zombres */ 
  /* (ou affectes par la procedure d'ombroscopie). Neanmoins ses deffauts resten minoritaires dans cette region, */ 
  /* ainsi,  un filtre smooth du type MEDIAN, permet de les reduires considerablement*/
  erCvSmoothUser( &ea, &psmo1);
 
  /* Une fois etablie les bordes pricipaux dans l'image, un filtre derivatif permet de marquer les contours dans l'image.*/ 
  /* Le filtre choisi est le filtre a repose impulsionelle de Canny*/
  erCvCannyUser( &ea, &pcan);

  /* L'image final post-traitement est saufgarde dans un ficher qui a pour nom: */
  /* le nom definie par l'usager + le No Serial de l'image traite */
  erSaveImage( &ea, name, exit);  

  //   /* Extraction */
  //   /* Definition d un foncteur comme critere pour extraire des pixels suivant leur niveau de gris. cf->utilities/erPredicates.hpp */     
  IsEqualTo is_equal_255( 255);
  
//   /* Definition du conteneur pour points au moment de l extraction */
//   std::vector< CvPoint> cvPts;

//   /* Le contours obtenues avec le filtre Canny, sont definies par des pixels ayant une intensite maximal de 255 en 8 bit. */
//   /* cette fonction ecrit un vecteur avec les coordonnes en pixels de le dites pixels*/
  erExtractCvPoints( cvPts, &ea, is_equal_255, rect); /* Extraction */
//   std::list<Point_2> cgalPts;
  
//   /* Conversion des points OpenCv en point CGAL */
  convertCvToCgalpoints( cvPts, cgalPts);
  alpha_edges_user( cgalPts, cgalSeg, &palp);
//   Alpha_shape_2 as2(cgalPts.begin(),cgalPts.end(),FT(2));
//   cgalPts.clear();

//   /* Aplication de l'algorithme de boost::graph */
//   std::list<Segment_2> segments;
//   alpha_edges( as2, std::back_inserter(segments));
  
//   /* Ecriture des cotes dans le fichier "edges_cv_filters.dat" */
//   std::string fileN="test";
//   std::string base_edges="results/";
//   std::string file = base_edges+fileN+".dat";
//   std::cout << file << std::endl;
//   std::ofstream ot(file.c_str());
//   std::list<Segment_2>::iterator  is;
//   for(is=segments.begin();is!=segments.end();is++)
//     {
//       ot << *is << std::endl;
//     };
//   segments.clear();
//   /* L'usager doit selectionner le contour ou courbe d'interet dans l'image resultant du Canny. */
//   /* Cette fonction extrait (depuis le vecteur construit auparavant) les coordones des pixels de le dit curbe */
//   //erExtractionCurveUser( &ea, &cerc, file_name, cvPts, rect);

//   /*Cette fonction ecrit la curbe d'interet, dans un ficher qui a pour nom, */ 
//   /* le nom definie par l'usager + le No serial de l'image depuis laquelle etait extrait */
//   //erEcriturePointPixel( cvPts, file_name);
  erLargestClosedPolygon( cgalSeg, bgraphSeg); 
  erPrintCgalPoint( bgraphSeg, name, exit);
//   /* Boucle de lecteure des images  */
//   time_t tbeg = time(NULL);
//   uint nIm(0);
//   while(true)
//     {  
//       boost::tie(er,loaded) = erLoadImageSeries( file_name,inc.inc());
//       if(!loaded) break;
//       bw = erConvertToBlackAndWhite( &er);        
//       //eo = ca.transform_image( bw);
//       ea = erDef_ROI( &bw, &rect);    
//       erCvSmooth( &ea, &psmo);
//       erCvAdaptiveThreshold( &ea, &padt);
//       erCvSmooth( &ea, &psmo1);
//       erCvCanny( &ea, &pcan);
//       erSaveImage( &ea, file_name);
//       IsEqualTo is_equal_255( 255);
//       std::vector<CvPoint> cvPts; 
//       erExtractPoints( &ea, cvPts, is_equal_255,rect,1);
//       // Attention ENCORE EN DEVELOPPEMENT
//       cvPointsToCgal(cvPts.begin(),cvPts.end(),std::back_inserter(cgalPts));
//       // Attention ENCORE EN DEVELOPPEMENT
//       Alpha_shape_2 as2(cgalPts.begin(),cgalPts.end(),FT(2));
      
//       cgalPts.clear();
//       // Attention ENCORE EN DEVELOPPEMENT
//       alpha_edges( as2, std::back_inserter(segments));
//       /* Ecriture des cotes dans le fichier "edges_cv_filters.dat" */
      
//       std::string fifi(file_name[1]);
//       std::string num=boost::lexical_cast<std::string>(nIm);
//       if(num.size() < 2) num.insert(0,"0");
//       std::string file = "results/"+fifi+"_"+num+".seg";
//       std::cout << file << " ecrit\n";
      
//       std::ofstream ot(file.c_str());
//       MapOfSegments  segis = get_connected_segments(segments.begin(),segments.end());
//       Segments_set_is_closed criteria;
//       ConnectedSegments out=filterMapOfSegments(segis,criteria);
//       std::cout << "Taille de out:" << out.size() << std::endl;
//       for(is=out.begin();is!=out.end();is++)
//         { 
// 	  ot << *is << std::endl;
//         };
//       segments.clear();
//       //erExtractionCurve( &ea, &cerc, file_name, cvPts, rect);
//       //erEcriturePointPixel( cvPts, file_name); 
//       nIm++;
//       if(nIm > Nimax) break;
//     }
//   std::cout << "Temps pour " << nIm << " images :" << time(NULL)-tbeg << std::endl;
  return(0);
}
