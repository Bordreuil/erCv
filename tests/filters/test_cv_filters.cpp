#include <erCv/erCv.hpp>
#include "cv.h"




int main(int HOLA, char** image_name)
{
  bool loaded;
  /* Chargement et visualisation de l image de base */
  INFOFILE = image_name[1];
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
  
  boost::tie(er,loaded)  = erLoadImage( image_name[2]);
  bw = erConvertToBlackAndWhite( &er);
  erWriteRecordFile( image_name);  //todo = cvCloneImage( &bw);
  erCvTemplateUser( &bw, &ptem); 
  //erCvPyramidUser( &bw, &pyra);
 
  erCvSmoothUser( &bw, &psmo);
 
  erCvThresholdUser( &bw, &pthr);

  erCvCannyUser( &bw, &pcan);
  erCvSobelUser( &bw, &psob);
  erSaveImage( &bw, image_name);
  
  while(true)
    {  
      boost::tie(er,loaded) = erLoadImageSeries( image_name);
      if(!loaded) break;    
      bw = erConvertToBlackAndWhite( &er);
      erCvTemplate( &bw, &ptem);
      //erCvPyramid( &bw, &pyra);
      erCvSmooth( &bw, &psmo);
      //erCvAdaptiveThreshold( &tm, &padt);
      erCvThreshold( &bw, &pthr);
      //erCvSmooth( &bw, &psmo);
      //erCvErode( &bw, &pero);
      erCvCanny( &bw, &pcan);
      erCvSobel( &bw, &psob);
      erSaveImage( &bw, image_name);
    }
  return(0);
};


