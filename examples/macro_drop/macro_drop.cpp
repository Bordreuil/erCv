#include <erCv/erCv.hpp>
#include <erCv/erCv.hpp>
#include <erCv/erCvFilters.hpp>
#include <erCv/utilities/erPredicates.hpp>
#include <erCv/erCvExtract.hpp>
#include <erCv/erCvToCgal.hpp>
#include <erCv/geometry/erCgalAlphaShape2.hpp>
#include <time.h>

/* Valeurs des paramettres a introduire, pour chaque fonction:
Smooth           : 7, 1 (0 pour OK)
AdaptiveThreshold: 1, 29, 1, 1 (0 pour OK)
Smooth2          : 7, 3 (0 pour OK)
Canny            : 355, 355 





/* Paramettres a introduir par l'usager dans l'appel du programe: */
/* 1- NOM choisi pour identifier les ficher de sortie,*/
/* 2- Adresse et nom de la premiere image a traiter*/
/* Pour gerer les increments des photos */
/* rien de tel qu une petite classe */

int main( int hola, char** file_name)
{

  std::cout <<"-----------------------------------------------\n\n";
  std::cout <<"\tMagic treatment for metal transfer\n\tBy Edward Romero\n\tNovember 2009\n\tLMGC/UM2/UM5508\n\tANR-TEMMSA\n\n";
  std::cout <<"-----------------------------------------------\n\n";
  uint ninc,ndelta,every,Nimax;
  std::cout << "Increment de photo:";
  //std::cin  >> ninc;
  ninc = 1;
  std::cout << "Toutes les n photos:";
  //std::cin >>   every;
  every = 1;
  std::cout << " increment de:";
  //std::cin >> ndelta;
  ndelta = 1;
  std::cout << "Nombre max de photos:";
  //std::cin >> Nimax;
  Nimax = 1;
  
  /* Declaration de variables a utiliser par les fonctions */
  char* exit = file_name[1];
  char* name = file_name[2];
  erImageIncrement inc(ninc,ndelta,every);
  std::cout << INFOFILE << std::endl;
  erImage ea, eb, ec, ed, ee;
  CvRect rect;
  erCerc cerc; 
  erSmootP psmo, psmo1;
  erCannyP pcan;
  erAdThrP padt;
  erThresP pthr, pthr1;
  erEqualP pequ;
  bool loaded;

  std::list< CvPoint> cvPts;
  std::list< CgalPoint> cgalPts;
  std::list< CgalSegmt> cgalSeg;
  
  /* Construction matrix de calibracion de l'image et regle de conversion pixel->mm */
  /* Premiere Image a charger: Patron construite sur l'ordinateur */
  /* Seconde Image a charger: Temoin mesure dans l'experience*/
  //erCalibration ca( "cuadro6.jpg", "diferent4.jpg", 3, 3); /* Calibration des images */
  
  /* Chargement de la premiere image a travailler et conversion a 8bit*/

  boost::tie( ea, loaded) = erLoadImage( name);
  if(!loaded) return 0;
  erSaveImage( &ea, name, exit);
  eb = erConvertToBlackAndWhite( &ea); /* Conversion en 8 bit single channel */

  /* Conversion de l'image du RGB->GRIS */
  //ca.transform_image( bw);

  /* Definision de la zone d'interet ou on souhaite travvailler */
  ec = erDef_ROIuser( &eb, &rect);


  //erCvEqualizeHistUser( &ec, &pequ);

  /* Debut du trataiment de l'image par methodes de filtrage optiques */
  /* Pour reduire la granulosite issue du bruit dans les pixels et la non homogenite de l'eclairage sur l'image;*/
  /* l'image est lisse avec un filtre Smooth du type BLUR (moyennage standart)*/
  //std::cout << "Before Smooth User\n";
  erCvSmoothUser( &ec, &psmo);
  
  /* Dans les zones affectes par la procedure d'ombroscopie, des inegalites dans l'intensite de niveaux de gris sont observes. */
  /* Pour faire resortir les bordes principaux (par contraste) entres les zones zommbres et eclaires, */
  /* un methode de filtrage par seuil, adapte par zone, est utilise */
  erCvAdaptiveThresholdUser( &ec, &padt, true);
  //erCvThresholdUser( &ec, &pthr, true);

  /* Le Sueillage par zones fait aussi resortir les bordes a l'interior des zones zombres */ 
  /* (ou affectes par la procedure d'ombroscopie). Neanmoins ses deffauts resten minoritaires dans cette region, */ 
  /* ainsi,  un filtre smooth du type MEDIAN, permet de les reduires considerablement*/
  erCvSmoothUser( &ec, &psmo1);
  //erCvThresholdUser( &ec, &pthr1, true); 
  /* Une fois etablie les bordes pricipaux dans l'image, un filtre derivatif permet de marquer les contours dans l'image.*/ 
  /* Le filtre choisi est le filtre a repose impulsionelle de Canny*/
  erCvCannyUser( &ec, &pcan);

  /* L'image final post-traitement est saufgarde dans un ficher qui a pour nom: */
  /* le nom definie par l'usager + le No Serial de l'image traite */
  //erSaveImage( &ec, name, exit);  

  /* Extraction */
  /* Definition d un foncteur comme critere pour extraire des pixels suivant leur niveau de gris. cf->utilities/erPredicates.hpp */     
  IsEqualTo is_equal_255( 255);



  /* Le contours obtenues avec le filtre Canny, sont definies par des pixels ayant une intensite maximal de 255 en 8 bit. */
  /* cette fonction ecrit un vecteur avec les coordonnes en pixels de le dites pixels*/
  erExtractCvPoints( cvPts, &ec, is_equal_255, rect); /* Extraction */
  std::cout << "cvPts.size(): " << cvPts.size() << std::endl;

  /* L'usager doit selectionner le contour ou courbe d'interet dans l'image resultant du Canny. */
  /* Cette fonction extrait (depuis le vecteur construit auparavant) les coordones des pixels de le dit curbe */
  erExtractCurveMacroDropUser( cvPts, &ec, rect, &cerc, name);
  std::cout << "cvPts.size(): " << cvPts.size() << std::endl;

  /*Cette fonction ecrit la curbe d'interet, dans un ficher qui a pour nom, */ 
  /* le nom definie par l'usager + le No serial de l'image depuis laquelle etait extrait */
  erPrintCvPoint( cvPts, name, exit); 
  
    /* Boucle de lecteure des images  */
  clock_t tbeg = clock();
  uint nIm(0);
//   while(true)
//     { 
//       erImage eab, ebb, ecb;
//       std::list< CvPoint> cvPtsb;
//       //std::cout << "HOLA_1" << std::endl;
//       boost::tie( eab, loaded) = erLoadImageSeries( name, inc.inc());
//       if(!loaded) break;
//       ebb = erConvertToBlackAndWhite( &eab);        
//       //eo = ca.transform_image( bw);
//       ecb = erDef_ROI( &ebb, &rect);  
//       erCvEqualizeHist( &ecb, &pequ);  
//       erCvSmooth( &ecb, &psmo);
//       erCvAdaptiveThreshold( &ecb, &padt);
//       erCvSmooth( &ecb, &psmo1);
//       erCvCanny( &ecb, &pcan);
//       //        erSaveImage( &eab, file_name);
//       IsEqualTo is_equal_255( 255);
//       //        std::vector<CvPoint> cvPts; 
//       //std::cout << "HOLA_2" << std::endl;
//       erExtractCvPoints( cvPtsb, &ecb, is_equal_255, rect);
//       erExtractCurveMacroDrop( cvPtsb, &ecb, rect,  &cerc, name);
//       erPrintCvPoint( cvPtsb, name, exit); 
      
//       nIm++;
//       std::cout << "Image number :" << nIm << " passed: " << name << "\n";
//       if (nIm>Nimax) break;
//     }
  //     clock_t tfin = clock();
  //     std::cout << "Temps en ms pour " << nIm << " images :" << (tfin-tbeg)  << std::endl;
  return(0);
}
