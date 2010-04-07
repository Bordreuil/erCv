#include<erCv/erCvSegmentationParams.hpp>




erTemplP::erTemplP():type(SQDIFF_NORMED), rectan(cvRect(0,0,0,0)), drawing(false), image(NULL){};
erTemplP::erTemplP( MatchTemplateType tt, CvRect rect, bool draw, IplImage* img):
  type(tt), rectan(rect), drawing(draw), image(img){};


std::ostream& operator << (std::ostream& o, const erTemplP et)
{
  o << "**Begin Match Template Parameter : \n";
  o << "\tTemplate Type\t:\t" << et.type << std::endl;
  o << "\tRectangle (width)\t:\t" << et.rectan.width << std::endl;
  o << "\tRectangle (height)\t:\t" << et.rectan.height << std::endl;
  o << "\tRectangle (posX)\t:\t" << et.rectan.x << std::endl;
  o << "\tRectangle (posY)\t:\t" << et.rectan.y << std::endl;
};
