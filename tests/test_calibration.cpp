#include <erCv/erCv.hpp>

int main()
{
  erImage im = erLoadImage("ed20090619_3_00568.bmp");
  erShowImage("toto",&im);
  erCalibration ca("cuadro5.jpg","etalon_512.bmp",3,3);
  erImage pat = ca.get_patron();
  erShowImage("patron", &pat);
  erImage mes = ca.get_mesure();
  erShowImage("mesure",&mes);
  erImage ir;
  ir=ca.transform_image(im);
  cvNamedWindow("Turn");
  cvShowImage("Turn",&ir);
  cvWaitKey();
  // std::cout << "on est sorti" << std::endl;
  return 0;
};
