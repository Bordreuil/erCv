#include <erCv/erCv.hpp>
#include "cv.h"




int main(int HOLA, char** image_name)
{
  bool loaded;
  /* Chargement et visualisation de l image de base */
  char* exit = image_name[1];
  char* name = image_name[2];
  erImage todo, er, bw, tm;
  erTemplP ptem;
  erSmootP psmo;
  erCannyP pcan;
  erPyramP pyra ,pyra1;
  erThresP pthr;
  erAdThrP padt;
  erDilatP pdil;
  erErodeP pero;
  erSobelP psob;
  
  boost::tie(er,loaded)  = erLoadImage( name);
  bw = erConvertToBlackAndWhite( &er);
  erWriteRecordFile( exit);  //todo = cvCloneImage( &bw);
  erCvTemplate( &bw, &ptem); 
  //erCvPyramidUser( &bw, &pyra);
 
  erCvSmoothUser( &bw, &psmo);
 
  erCvThreshold( &bw, &pthr);

  erCvCanny( &bw, &pcan);
  erCvSobel( &bw, &psob);
  erSaveImage( &bw, name, exit);
  
  return(0);
};


