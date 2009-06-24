#include "erCv.hpp"

int main()
{
  erImage im = erLoadImage("ed20090619_3_00568.bmp");
  erShowImage("toto",&im);
  erCalibration ca("etalon_512.bmp", "cuadro5.jpg",3,3);
  erShowImage("patron", &(ca.get_patron()));
  erImage ir;
  ir=ca.transform_image(im);
  cvNamedWindow("Turn");
  cvShowImage("Turn",&ir);
  cvWaitKey();
  // std::cout << "on est sorti" << std::endl;
  return 0;
};
