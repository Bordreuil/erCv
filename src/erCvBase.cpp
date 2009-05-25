#include "erCvBase.hpp" 

// Programmation de la classeImage
Image::Image(){_im=NULL;};
Image::Image(char* name){_im=cvLoadImage(name);}; // TODO: test si l image existe
Image::Image(IplImage* im){_im=cvCloneImage(im);};
Image::~Image(){};
IplImage* Image::getCvImage(){return _im;};
//void Image::loadImage(char * name){_im=cvLoadImage(name);};

// Interface pour des fonctions d open cv
void erShowImage(char* name,Image im)
{
  cvNamedWindow(name);
  cvShowImage(name,im.getCvImage());
  cvWaitKey();
};
Image erLoadImage(char* name)
{
  return Image(name);
};

void erSaveImage(char* name,Image im)
{
  cvSaveImage(name,im.getCvImage());
}
