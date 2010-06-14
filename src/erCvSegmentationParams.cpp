#include<erCv/erCvSegmentationParams.hpp>

//erDiffeP::erDiffeP(){};
//erDiffeP::erDiffeP(erAdThrP ead,erThresP eth,std::string file,int num):
  //{};


erPyramP::erPyramP():trh1(50),trh2(25),levl(10){};
erPyramP::erPyramP(int thr1,int thr2,int levl):trh1(thr1),trh2(thr2),levl(levl){};

erTemplP::erTemplP():type(SQDIFF_NORMED), rectan(cvRect(0,0,0,0)), drawing(false), image(NULL){};
erTemplP::erTemplP( MatchTemplateType tt, CvRect rect, bool draw, IplImage* img):
  type(tt), rectan(rect), drawing(draw), image(img){};
// Ajout Cyril a verifier Edward
// C'est plus facile a cabler en python
erTemplP::erTemplP( MatchTemplateType tt, CvRect rect, bool draw,std::string nameImage):
  type(tt), rectan(rect), drawing(draw) {image=cvLoadImage(nameImage.c_str());};

erFindcP::erFindcP(): level(7), mode(erCV_RETR_LIST), meth(erCV_CHAIN_APPROX_SIMPLE){};
erFindcP::erFindcP( FindContoursMode co, FindContoursMeth ce, int le): level(le), mode(co), meth(ce){};



std::ostream& operator << (std::ostream& o,const erFindcP ef)
{
  o << "** Begin FindContour Parameter : \n";
  o << "\tLevel\t:\t" << ef.level << std::endl;
  o << "\tMode\t:\t" << ef.mode << std::endl;
  o << "\tMeth\t:\t" << ef.meth << std::endl;
  o << "** End FindContour Parameter------\n";
  return o;
};


std::ostream& operator << (std::ostream& o, const erTemplP et)
{
  o << "**Begin Match Template Parameter : \n";
  o << "\tTemplate Type\t:\t" << et.type << std::endl;
  o << "\tRectangle (width)\t:\t" << et.rectan.width << std::endl;
  o << "\tRectangle (height)\t:\t" << et.rectan.height << std::endl;
  o << "\tRectangle (posX)\t:\t" << et.rectan.x << std::endl;
  o << "\tRectangle (posY)\t:\t" << et.rectan.y << std::endl;
};
