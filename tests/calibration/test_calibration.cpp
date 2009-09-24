/*
  Test pour une fonction de calibration




  18/08/2009 : cb
 */


#include <erCv/erCv.hpp>

std::string INFOFILE;

int main( int hola, char** file_name)
{ /* Chargement et visualisation de l image */
  erImage im ;bool loaded;
  boost::tie(im,loaded)= erLoadImage(file_name[2]);
  INFOFILE = file_name[1];
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
  //erImage ir;
  erImage ir=ca.transform_image(im);
  cvNamedWindow("Turn");
  cvShowImage("Turn",&ir);
  cvWaitKey();
  return 0;
};
