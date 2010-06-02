#ifndef _erCV_SEGMENTATION_PARAMS_HPP_
#define _erCV_SEGMENTATION_PARAMS_HPP_
#include "erCvFiltersParams.hpp"
#include "erCvBase.hpp"
#include<iostream>
/** \defgroup filters_params FiltersParams */
/** \ingroup filters  */

/** \addtogroup filters_params */
/*@{*/





struct erDiffeP
{
  erAdThrP *adapthold;
  erThresP *threshold;
  IplImage *image;
  int type;
};



/**
   \brief

 */
enum Templ{};
enum MatchTemplateType {SQDIFF=1,
			SQDIFF_NORMED=2,
			CCORR=3,
			CCORR_NORMED=4,
			CCOEFF=5,
			CCOEFF_NORMED=6
};
extern char* matchtemplatetype[];
struct erTemplP
{
  erTemplP(MatchTemplateType,CvRect,bool,IplImage*);
  erTemplP();
  CvRect rectan;
  bool drawing;
  IplImage *image;
  MatchTemplateType type;
};


/**
   \brief

 */
// enum CallBP{};
// enum CallBPColorConversion {CV_RGB2XYZ=1,
// 			    CV_RGB2HSV=2,
// 			    CV_RGB2HLS=3,
// 			    CV_RGB2Lab=4,
// 			    CV_RGB2YCrCb=5,
// 			    CCOEFF_NORMED=6
// };
// extern char* matchtemplatetype[];
// struct erTemplP
// {
//   erTemplP(MatchTemplateType,CvRect,bool,IplImage*);
//   erTemplP();
//   CvRect rectan;
//   bool drawing;
//   IplImage *image;
//   MatchTemplateType type;
// };
struct erCallBP
{
  CvRect rectan;
  int type;
  int typeH;
  bool drawing;
  IplImage *image;
};




struct erEqualP
{
  int applic;
};





/**
   \brief

 */
struct erPyramP
{
  int trh1; /** < Threshold value to link in pyramid fonction */
  int trh2; /** < Threshold value to clustering in pyramid fonction */
  int levl; /** < Number of level to pyramid be applied */
};




/**
   \brief Structure contenant les parametre utiles pour 
   un lissage
 */
extern const int nbFindContoursMode;
extern char* findcontoursmode[]; 
enum FindContoursMode {erCV_RETR_EXTERNAL, 
		       erCV_RETR_LIST,
		       erCV_RETR_CCOM,
		       erCV_RETR_TREE
};
extern const int nbFindContoursMeth;
extern char* findcontoursmeth[]; 
enum FindContoursMeth {erCV_CHAIN_CODE,
		       erCV_CHAIN_APPROX_NONE,
		       erCV_CHAIN_APPROX_SIMPLE,
		       erCV_CHAIN_APPROX_TC89_L1
};
struct erFindcP
{ 
  erFindcP();
  erFindcP(FindContoursMode,FindContoursMeth,int);
  int        level; /** <  */
  FindContoursMode  mode; /** < Mode to organise the countour finding process */
  FindContoursMeth  meth; /** < Methode to find contours */
};
std::ostream& operator << (std::ostream&, const erFindcP);




/*@}*/
#endif
