#include <erCv/erCv.hpp>





int main(int HOLA, char** image_name){
  bool loaded;
  /* Chargement et visualisation de l image de base */
  INFOFILE = image_name[1];
  erImage todo;
  erImage  er;

  boost::tie(er,loaded)  = erLoadImage( image_name[2]);
  erShowImage("toti",&er);
  erImage bw  = erConvertToBlackAndWhite( &er);

  erShowImage("toto",&bw);

  todo = cvCloneImage( &bw);

  erCvDifferencing( &bw, &todo);
  erSaveImage( &bw, image_name);

  while(true)
    {  

      boost::tie(er,loaded) = erLoadImageSeries( image_name);

      if(!loaded) break; 
    
      bw = erConvertToBlackAndWhite( &er);
      erCvDifferencing( &bw, &todo);
      erSaveImage( &bw, image_name);


    }
  return(0);
};


