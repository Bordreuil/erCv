#include <erCv/erCvFilters.hpp>


std::string INFOFILE;
int main(int HOLA, char** image_name){
  /* Chargement et visualisation de l image de base */
  INFOFILE = image_name[1];
  todo = erImage();
  er = erImage();
  bw = erImage();
  er  = erLoadImage( image_name[2]);
  bw  = erConvertToBlackAndWhite( &er); /* Conversion en 8 bit single channel */
  todo.image = cvCloneImage( bw.image);
  erCvDifferencingUser( &bw, &todo);
  erSave_picture( &bw, image_name);
  while(todo.image !=NULL)
    {  
      er = erLoadImages_series( image_name);
      if( er.image == NULL) break; 
      bw = erConvertBlackAndWhite( &erI);
      erCvDifferencingUser( &bw, &todo);
      erSave_picture( &bw, image_name);
    }
  return(0);
}

   
  cvWaitKey();
 

  return 0;
};
