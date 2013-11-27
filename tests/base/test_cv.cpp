#include <erCv/erCv.hpp>

/*
  Test des fonctions et des classes de base d erCv:
    - Les fonctions sont definies pour un IplImage*
      comme erImage herite d IplImage, on peut faire passer un pointeur
      de erImage a la place
    - On doit pouvoir combiner des fonctions erCv OpenCv

    18/08/2009: cb 
    18/02/2010: cb modifier pour etre utiliser avec ctest 
 */

std::string INFOFILE;

int main( int hola, char** image_name)
{
  char* name = image_name[2];
  char* exit = image_name[1];
  erImage todo, todo1;
  erSmootP psmo, psmo1;
  erThresP pthr;
  bool loaded;   // loaded permet de savir si le fichier c est charge correctement
  
  erWriteRecordFile( exit);
  boost::tie(todo,loaded) = erLoadImage( name);

  erCvSmooth( &todo, &psmo);
  erCvThreshold( &todo, &pthr);

  erSaveImage( &todo, name, exit);
};


