#include <erCv/erCv.hpp>
/*
  Test des fonctions et des classes de base d erCv:
    - Les fonctions sont definies pour un IplImage*
      comme erImage herite d IplImage, on peut faire passer un pointeur
      de erImage a la place
    - On doit pouvoir combiner des fonctions erCv OpenCv

    18/08/2009: cb 
 */

std::string INFOFILE;

int main( int hola, char** image_name)
{

  erImage todo, todo1;
  erSmoothP psmo, psmo1;
  erThresP pthr;
  INFOFILE = image_name[1];

  erWriteRecordFile( image_name);
  todo = erLoadImage( image_name[2]);

  erCvSmoothUser( &todo, &psmo);
  erCvThresholdUser( &todo, &pthr);

  erSaveImage( &todo, image_name);
}


