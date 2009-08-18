#include <erCv/erCvFilters.hpp>


int main(){
  /* Chargement et visualisation de l image de base */
  erImage er    = erLoadImage("../pictures/ed20090619_3_02176.bmp");
  erShowImage("base Image",&er);
  erImage bw    = erConvertToBlackAndWhite(&er); /* Conversion en 8 bit single channel */
  erImage ercan = erSmoothAndCanny(bw,200,1);    /* Smooth and Canny sur l image convertie */
  erShowImage("after Canny",&ercan);    
  cvWaitKey();
 

  return 0;
};
