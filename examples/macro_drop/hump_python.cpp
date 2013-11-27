#include <erCv/erCv.hpp>

int main( int hola, char** file_name)
{
  CvRect rect;
  rect.x=121;rect.y=110;rect.width=814;rect.height=223;
  erCerc cerc(135,293,25);
  erEqualP equ(0);
  erSmootP p1(BLUR,7),p2(MEDIAN,5);
  erCannyP cann(355,355);
  erAdThrP adp(THRESH_BINARY,AM_MEAN,49,119,255); //** < */
  erMacroDropAnalysis mda("hump");
  mda.defineParameters(rect,cerc,p1,p2,cann,adp,equ);
  mda.doIt("hump_1.bmp");
  return(0);
};
