#include "erCvBase.hpp" 
#include "erFileUtilities.hpp"

// Programmation de la classeImage
erImage::erImage():IplImage(){};
erImage::erImage(char* name):IplImage(*cvLoadImage(name))
{
}; 

erImage::erImage(IplImage* im):IplImage(*im){};
erImage::~erImage(){};

// Interface pour des fonctions d open cv
void erShowImage(char* name,IplImage* im)
{
  cvNamedWindow(name);
  cvShowImage(name,im);
  cvWaitKey();
  cvDestroyWindow(name);
};

erImage erLoadImage(char* name)
{ if(erFileExists(name))
  {
      return  erImage(name);
  }
  else
    { std::cout << "...Impossible d instancier un objet de type erImage a partir du fichier:" << name << std::endl;
      IplImage * im = NULL;
      return erImage(im);
  };
};

void erSaveImage(char* name,IplImage* im)
{
  cvSaveImage(name,im);
};

erImage erConvertToBlackAndWhite(IplImage* im)
{
   IplImage * ipbw = cvCreateImage( cvGetSize(im), im->depth, 1);
   cvCvtColor(im, ipbw, CV_RGB2GRAY);
   erImage bw(ipbw);
   return bw;
};
