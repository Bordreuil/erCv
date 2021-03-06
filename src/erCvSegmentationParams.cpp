// Copyright Universite Montpellier 2/CNRS 
// Contributor(s) : 
//         Edward Romero 
//         Cyril Bordreuil
// Contact: cyril.bordreuil@univ-montp2.fr
// 
// This software is a computer program whose purpose is to [describe
//  functionalities and technical features of your software].
//
// This software is governed by the CeCILL license under French law and
// abiding by the rules of distribution of free software.  You can  use, 
// modify and/ or redistribute the software under the terms of the CeCILL
// license as circulated by CEA, CNRS and INRIA at the following URL
// "http://www.cecill.info". 
//
// As a counterpart to the access to the source code and  rights to copy,
// modify and redistribute granted by the license, users are provided only
// with a limited warranty  and the software's author,  the holder of the
// economic rights,  and the successive licensors  have only  limited
// liability. 
//
// In this respect, the user's attention is drawn to the risks associated
// with loading,  using,  modifying and/or developing or reproducing the
// software by the user in light of its specific status of free software,
// that may mean  that it is complicated to manipulate,  and  that  also
// therefore means  that it is reserved for developers  and  experienced
// professionals having in-depth computer knowledge. Users are therefore
// encouraged to load and test the software's suitability as regards their
// requirements in conditions enabling the security of their systems and/or 
// data to be ensured and,  more generally, to use and operate it in the 
// same conditions as regards security. 
// 
// The fact that you are presently reading this means that you have had
// knowledge of the CeCILL license and that you accept its terms.
#include <erCv/erCvSegmentationParams.hpp>
#include <erCv/erCvBase.hpp>
#include <iostream>
#include <fstream>
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
erWhitBP::erWhitBP( int tw, int tb, int bb, int sb):trh_w(tw),trh_b(tb),blob_b(bb),size_b(sb){};

erRegGrP::erRegGrP(): int_maxdis(0.2), ini_point( std::make_pair( cvPoint(0,0), 0)){};
erRegGrP::erRegGrP( int dm, std::pair< CvPoint, int> ip): int_maxdis(dm), ini_point(ip){};

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
