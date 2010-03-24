#ifndef _erCv_ANALYSIS_HPP_
#define  _erCv_ANALYSIS_HPP_

#include "erCvFiltersParams.hpp"
#include "erCvTools.hpp"
#include "erCvBase.hpp"

#include<string>

struct erAnalysis
{
  erAnalysis();
  erAnalysis(std::string name,std::string infofile,std::string firstImage); 
  void setImageIncrement(erImageIncrement ii);
  void setTotalImages(int);
  std::string          infoFile;
  std::string          name;
  std::string          firstImage;
  erImageIncrement     incImage;
  int                  totalImage;
};




struct erMacroDropAnalysis:public erAnalysis
{ erMacroDropAnalysis();
  erMacroDropAnalysis(std::string name,std::string infofile,std::string firstImage);
  bool defineParameterUI();
  void defineParameter(CvRect,erCerc,erSmootP,erSmootP,erCannyP,erAdThrP);
  bool doIt(std::string);
  void saveParameter();
  void loadParameter();
  CvRect         rectOI;
  erCerc         cercToStart;
  erSmootP       param_smooth1,param_smooth2;
  erCannyP       param_canny;
  erAdThrP       param_adaptive_threshold;
 };





#endif
