#include<erCv/erCvAnalysis.hpp>


/* Valeurs des paramettres a introduire, pour chaque fonction:
Smooth           : 7, 1 (0 pour OK)
AdaptiveThreshold: 1, 29, 1, 1 (0 pour OK)
Smooth2          : 7, 3 (0 pour OK)
Canny            : 355, 355 



/* Paramettres a introduir par l'usager dans l'appel du programe: */
/* 1- NOM choisi pour identifier les ficher de sortie,*/
/* 2- Adresse et nom de la premiere image a traiter*/





int main( int hola, char** file_name)
{ 
  CvRect rect;
  //rect.x=100;rect.y=120;rect.width=70;rect.height=70;
  rect.x=0;rect.y=0;rect.width=255;rect.height=255;
  erSmootP p1(BLUR,5),p2(GAUSSIAN,5);
  erCannyP cann(355,355);
  erAdThrP adp(THRESH_BINARY,AM_MEAN,53,19,255); //** <
  erAlphaP alp(1.);
  erMetalTransfertAnalysis emt("peo","peo");
  emt.defineParameters(rect,p1,p2,cann,adp,alp);
  emt.doIt("imageExemple_1.bmp");
  emt.doIt("imageExemple_2.bmp");
  emt.doIt("imageExemple_3.bmp");
  emt.doIt("imageExemple_4.bmp");
  emt.doIt("imageExemple_5.bmp");
  emt.doIt("imageExemple_6.bmp");
  return(0);
}
