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
enum MatchTemplateType {
  SQDIFF=1,
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




/*@}*/
#endif
