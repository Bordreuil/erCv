#include <erCv/erCvBase.hpp>
#include <erCv/erCvFilters.hpp>
#include <erCv/erCvSegmentation.hpp>
#include <cstdio>
#include <iostream>
#include <fstream>

//std::string INFOFILE;
int main(int HOLA, char** image_name){
  /* Chargement et visualisation de l image de base */
  INFOFILE = image_name[1];
  erImage* todo;
  erImage er;
  //erImage bw;
  er  = erLoadImage( image_name[2]);
  erShowImage("toti",&er);
  erImage bw  = erConvertToBlackAndWhite( &er); /* Conversion en 8 bit single channel */
  // <<<<<<< .mine
  //   todo.image = cvCloneImage( bw.image);
  //   erCvDifferencing( &bw, &todo);
  //   erSave_picture( &bw, image_name);
  //   while(todo.image !=NULL)
  // =======
  std::cout << "P1" << std::endl;
  erShowImage("toto",&bw);
  IplImage* in = cvCloneImage( &bw);
  todo = (erImage *) in;
  //todo = (erImage *) cvCloneImage( &bw);
  std::cout << "P11" << std::endl;
  erCvDifferencing( &bw, todo);
  erSaveImage( &bw, image_name);
  while(todo !=NULL)
    {  
      std::cout << "H1" << std::endl;
      er = erLoadImageSeries( image_name);
      std::cout << "H111" << std::endl;
      if( &er == NULL)
	{

	  break; 
	}
      bw = erConvertToBlackAndWhite( &er);
      erCvDifferencing( &bw, todo);
      erSaveImage( &bw, image_name);
      std::cout << "H1111" << std::endl;

    }
  return(0);
};


