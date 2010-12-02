/*
  Test pour un objet de calibration de calibration




  18/08/2009 : cb
  02/12/2010 : maj cb
 */


#include <erCv/erCv.hpp>

//std::string INFOFILE;

int main( int hola, char** file_name)
{ 
  /* Defintion de la calibration et visualisation des images 
     patrons et mesures 
  */
  erCalibration ca( "calibration_source.jpg", "calibration_target.bmp", 3, 3);
  erImage pat = ca.get_patron();
  //erShowImage("patron", &pat);
  erImage mes = ca.get_mesure();
  //erShowImage("mesure",&mes);
  
  return(0);
}
