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
  p_smooth psmo, psmo1;
  p_threshold pthr;
  INFOFILE = image_name[1];

  erWrite_Record_File( image_name);
  todo = erLoadImage( image_name[2]);

  erCvSmoothUser( &todo, &psmo);
  erCvThresholdUser( &todo, &pthr);

  erSave_picture( &todo, image_name);
}


// int main()
// { /* Chargement d une image */
//   erImage im = erLoadImage("../pictures/ed20090619_3_00568.bmp");
//   /* Visualisation d une image */
//   erShowImage("toto",&im);
//   /* On attend que la touche Esc soit tapee */
//   cvWaitKey();
//   return 0;
// };
