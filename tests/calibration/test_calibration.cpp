/*
  Test pour une fonction de calibration




  18/08/2009 : cb
 */


#include <erCv/erCv.hpp>

int main()
{ /* Chargement et visualisation de l image */
  erImage im = erLoadImage("../pictures/ed20090619_3_00568.bmp");
  erShowImage("toto",&im);

  /* Defintion de la calibration et visualisation des images 
     patrons et mesures 
  */
  erCalibration ca("../pictures/cuadro5.jpg","../pictures/etalon_512.bmp",3,3);
  erImage pat = ca.get_patron();
  erShowImage("patron", &pat);
  erImage mes = ca.get_mesure();
  erShowImage("mesure",&mes);

  /* Creation de l image et modification a l aide de la transformation 
     de la calibration */
  erImage ir;
  ir=ca.transform_image(im);
  cvNamedWindow("Turn");
  cvShowImage("Turn",&ir);
  cvWaitKey();
  return 0;
};
