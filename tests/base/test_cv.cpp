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
  erSmootP psmo, psmo1;
  erThresP pthr;
  bool loaded;   // loaded permet de savir si le fichier c est charge correctement
  INFOFILE = image_name[1];

  erWriteRecordFile( image_name);
  boost::tie(todo,loaded) = erLoadImage( image_name);

  erCvSmoothUser( &todo, &psmo);
  erCvThresholdUser( &todo, &pthr);

  erSaveImage( &todo, image_name);
}


