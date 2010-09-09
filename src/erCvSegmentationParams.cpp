#include<erCv/erCvSegmentationParams.hpp>

//erDiffeP::erDiffeP(){};
//erDiffeP::erDiffeP(erAdThrP ead,erThresP eth,std::string file,int num):
  //{};


erPyramP::erPyramP():trh1(50),trh2(25),levl(10){};
erPyramP::erPyramP(int thr1,int thr2,int levl):trh1(thr1),trh2(thr2),levl(levl){};

//erTemplP::erTemplP():type(SQDIFF_NORMED), rectan(cvRect(0,0,0,0)), drawing(false), image(NULL){};
//erTemplP::erTemplP( MatchTemplateType tt, CvRect rect, bool draw, IplImage* img):
//  type(tt), rectan(rect), drawing(draw), image(img){};

erTemplP::erTemplP():type(SQDIFF_NORMED), rectan(cvRect(0,0,0,0)), drawing(false){};
erTemplP::erTemplP( MatchTemplateType tt, CvRect rect, bool draw): type(tt), rectan(rect), drawing(draw){};

// Ajout Cyril a verifier Edward
// C'est plus facile a cabler en python
//erTemplP::erTemplP( MatchTemplateType tt, CvRect rect, bool draw,std::string nameImage):  
//type(tt), rectan(rect), drawing(draw) {image=cvLoadImage(nameImage.c_str());}; /*REVISAR cet declaratyion avec Cyril, problem: n'est pas necessaire l'inclusion soit de l'image ou de le string */
//erTemplP::erTemplP( MatchTemplateType tt, CvRect rect, bool draw):
//  type(tt), rectan(rect), drawing(draw){};

erEqualP::erEqualP(): applic(0){};
erEqualP::erEqualP( int ap): applic(ap){};

erFindcP::erFindcP(): level(7), mode(erCV_RETR_LIST), meth(erCV_CHAIN_APPROX_SIMPLE){};
erFindcP::erFindcP( FindContoursMode co, FindContoursMeth ce, int le): level(le), mode(co), meth(ce){};

erWhitBP::erWhitBP():trh_w(185),trh_b(120),blob_b(5),size_b(10){};
erWhitBP::erWhitBP( unsigned char tw, unsigned char tb, int bb, int sb):trh_w(tw),trh_b(tb),blob_b(bb),size_b(sb){};

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
