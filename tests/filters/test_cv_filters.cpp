#include<erCv/erCvBase.hpp>
#include <erCv/erCvFilters.hpp>
#include <erCv/erCvSegmentation.hpp>

//std::string INFOFILE;
int main(int HOLA, char** image_name){
  /* Chargement et visualisation de l image de base */
  INFOFILE = image_name[1];
  erImage todo;
  erImage er;
  erImage bw;
  er  = erLoadImage( image_name[2]);
  bw  = erConvertToBlackAndWhite( &er); /* Conversion en 8 bit single channel */
  todo = (erImage *) cvCloneImage( &bw);
  erCvDifferencing( &bw, &todo);
  erSaveImage( &bw, image_name);
  while(&todo !=NULL)
    {  
      er = erLoadImageSeries( image_name);
      if( &er == NULL) break; 
      bw = erConvertToBlackAndWhite( &er);
      erCvDifferencing( &bw, &todo);
      erSaveImage( &bw, image_name);
    }
  return(0);
};


