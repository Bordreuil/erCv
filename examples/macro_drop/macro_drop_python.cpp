#include <erCv/erCv.hpp>


int main( int hola, char** file_name)
{

  CvRect rect;
  rect.x=20;rect.y=160;rect.width=230;rect.height=75;
  erCerc cerc(20,210,5);
  erEqualP equ(0);
  erSmootP p1(BLUR,7),p2(GAUSSIAN,5);
  erCannyP cann(355,355);
  erAdThrP adp(THRESH_BINARY,AM_MEAN,50,14,255); //** < 
  erMacroDropAnalysis mda("macroDrop");
  mda.defineParameters(rect,cerc,p1,p2,cann,adp,equ);

  mda.doIt("imageExemple_1.bmp");

  return(0);
};
