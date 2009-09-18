#include <erCv/erCv.hpp>
/*
  Test des fonctions et des classes de base d erCv:
    - Les fonctions sont definies pour un IplImage*
      comme erImage herite d IplImage, on peut faire passer un pointeur
      de erImage a la place
    - On doit pouvoir combiner des fonctions erCv OpenCv

    18/08/2009: cb 
 */

int main()
{ /* Chargement d une image */
  erImage*   it  ;
  IplImage * ii  = cvLoadImage("../pictures/ed20090619_3_00568.bmp");

  it             = (erImage*)  ii; // Conversion d une IplImage en erImage (les pointeurs)
  //it = ii;
  erImage im     = erLoadImage("../pictures/ed20090619_3_00568.bmp");
  /* Visualisation d une image */
  erShowImage("toto",it);
  /* On attend que la touche Esc soit tapee */
  cvWaitKey();
  return 0;
};
