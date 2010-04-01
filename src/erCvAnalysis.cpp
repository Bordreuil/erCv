#include <erCv/erCvAnalysis.hpp>
#include <erCv/erCvFilters.hpp>
#include <erCv/utilities/erPredicates.hpp>
#include <erCv/erCvExtract.hpp>
#include <erCv/erCvToCgal.hpp>
#include <erCv/erCvSegmentation.hpp>
#include <erCv/geometry/erCgalAlphaShape2.hpp>
#include <erCv/Gui/erCvUserInteraction.hpp>

#include <erCv/Gui/erCvFiltersUser.hpp>

#include <erCv/Gui/erCvSegmentationUser.hpp>
#include<time.h>
#include<fstream>
#include<boost/filesystem.hpp>

std::string ANALYSIS_EXTENSION="_erCvAnalysis";

erAnalysis::erAnalysis(){};

erAnalysis::erAnalysis(std::string name,std::string infofile): 
  name(name),infoFile(infofile)
{  dir_analysis = name+ANALYSIS_EXTENSION;
  create();
};


void erAnalysis::create()
{ 
    if (boost::filesystem::exists(dir_analysis))
      {
	std::cout << "an analysis with same name :" << name << "  already exist\n";
      }
    else{
         boost::filesystem::create_directory(dir_analysis);
        };
};


erMacroDropAnalysis::erMacroDropAnalysis(){};

erMacroDropAnalysis::erMacroDropAnalysis(std::string name,std::string infofile):
  erAnalysis(name,infofile),rectOI(),cercToStart(),param_smooth1(),param_smooth2(),
  param_canny(),param_adaptive_threshold()
{};

bool erMacroDropAnalysis::defineParametersUI(std::string firstImage)
   {
   std::cout <<"-----------------------------------------------\n\n";
   std::cout <<"\tMagic treatment for metal transfer\n\tBy Edward Romero\n\tNovember 2009\n\tLMGC/UM2/UM5508\n\tANR-TEMMSA\n\n";
   std::cout <<"-----------------------------------------------\n\n";
   
   /* Declaration de variables a utiliser par les fonctions */
   INFOFILE = this->infoFile;

   erImage er, bw, eo, ea;
   CvRect rect;
   erCerc cerc; 
   erSmootP psmo, psmo1;
   erCannyP pcan;
   erAdThrP padt;
   bool loaded; 
   std::list< CvPoint> cvPts;

   char* file_name =const_cast<char*>(firstImage.c_str());
   
   boost::tie(er,loaded) = erLoadImage(file_name);
   if(!loaded) return false;
   bw            = erConvertToBlackAndWhite( &er); /* Conversion en 8 bit single channel */
   eo            = bw; 

   ea            = erDef_ROIuser( &bw, &rect);
   rectOI        = rect;
   erCvSmoothUser( &ea, &psmo);
   param_smooth1 = psmo;
   erCvAdaptiveThresholdUser( &ea, &padt);
   param_adaptive_threshold = padt;
   erCvSmoothUser( &ea, &psmo1);
   param_smooth2 = psmo1;
   erCvCannyUser( &ea, &pcan);
   param_canny   = pcan;

   IsEqualTo is_equal_255( 255);

   erExtractCvPoints( cvPts, &ea, is_equal_255, rect); /* Extraction */
   erExtractCurveMacroDropUser( cvPts, &ea, rect, &cerc, file_name);
   cercToStart = cerc;
   char* nom   = const_cast<char*>(name.c_str());
   erPrintCvPoint( cvPts, file_name, nom); 
   return true;

   };

void erMacroDropAnalysis::defineParameters(CvRect rect,erCerc ecerc,erSmootP smooth1,erSmootP smooth2,erCannyP cann,erAdThrP adthr)
{
  rectOI                   = rect;
  cercToStart              = ecerc;
  param_smooth1            = smooth1;
  param_smooth2            = smooth2;
  param_canny              = cann;
  param_adaptive_threshold = adthr;

};

bool erMacroDropAnalysis::doIt(std::string fich)
{      bool loaded;
       char* file_name = const_cast<char*>(fich.c_str());
       std::string output_name = (dir_analysis+"/"+name);
       char* nom       = const_cast<char*>(output_name.c_str());
       erImage erb, bwb, eab; 
       
       boost::tie(erb,loaded) = erLoadImage( file_name);
       if(!loaded) return false;
       bwb = erConvertToBlackAndWhite( &erb);        
       eab = erDef_ROI( &bwb, &rectOI);    
       erCvSmooth( &eab, &param_smooth1);
       erCvAdaptiveThreshold( &eab, &param_adaptive_threshold);
       erCvSmooth( &eab, &param_smooth2);
       erCvCanny( &eab, &param_canny);
       erSaveImage( &eab, file_name,nom);
       IsEqualTo is_equal_255( 255);
       std::list<CvPoint> cvPts; 
       erExtractCvPoints( cvPts, &eab, is_equal_255, rectOI);
       erExtractCurveMacroDrop( &eab,cvPts, rectOI, &cercToStart, file_name);
       erPrintCvPoint( cvPts, file_name, nom); 

       return true;
};

void erMacroDropAnalysis::saveParameters(std::string file)
{ std::string output_file=dir_analysis+"/"+file;
  std::ofstream out(output_file.c_str());
  out << "* Begin er MacroDrop Analysis" << std::endl;
  out << this->rectOI;
  out << this->cercToStart;
  out << this->param_smooth1;
  out << this->param_adaptive_threshold;
  out << this->param_smooth2;
  out << this->param_canny;
  out << "* End er MacroDrop Analysis" << std::endl;
};

