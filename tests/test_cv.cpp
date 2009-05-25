#include "erCalibration.hpp"

int main()
{
  //IplImage* im = cvLoadImage("pos3_euro_1.bmp");
  //erShowImage("toto",im);
  erCalibration ca("pos1_cuadro.bmp","../datas/pos3_cuadro.bmp",3,3);
  //IplImage * ir;
  //ir=ca.transformImage(im);
  //cvNamedWindow("Turn");
  //cvShowImage("Turn",ir);
  //cvWaitKey();
  // std::cout << "on est sorti" << std::endl;
  return 0;
};
