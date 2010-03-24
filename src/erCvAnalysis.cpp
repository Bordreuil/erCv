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
#include<boost/lexical_cast.hpp>

erAnalysis::erAnalysis(){};

erAnalysis::erAnalysis(std::string name,std::string infofile,std::string firstImage): 
  name(name),infoFile(infofile),firstImage(firstImage),incImage(1,1,10),totalImage(10){};


void erAnalysis::setImageIncrement(erImageIncrement ii){incImage=ii;};
void erAnalysis::setTotalImages(int nImax){totalImage=nImax;};

erMacroDropAnalysis::erMacroDropAnalysis(){};

erMacroDropAnalysis::erMacroDropAnalysis(std::string name,std::string infofile,std::string firstImage):
  erAnalysis(name,infofile,firstImage),rectOI(),cercToStart(),param_smooth1(),param_smooth2(),
  param_canny(),param_adaptive_threshold()
{std::cout << name << std::endl;};

bool erMacroDropAnalysis::defineParameterUI()
   {
  std::cout <<"-----------------------------------------------\n\n";
   std::cout <<"\tMagic treatment for metal transfer\n\tBy Edward Romero\n\tNovember 2009\n\tLMGC/UM2/UM5508\n\tANR-TEMMSA\n\n";
   std::cout <<"-----------------------------------------------\n\n";
   uint ninc,ndelta,every,Nimax;
   std::cout << "Increment de photo:";
   std::cin  >> ninc;
   std::cout << "Toutes les n photos:";
   std::cin >>   every;
   std::cout << " increment de:";
   std::cin >> ndelta;
   std::cout << "Nombre max de photos:";
   std::cin >> Nimax;
  
   /* Declaration de variables a utiliser par les fonctions */
   INFOFILE = this->infoFile;
   erImageIncrement inc(ninc,ndelta,every);
   this->incImage = inc ;
   erImage er, bw, eo, ea;
   CvRect rect;
   erCerc cerc; 
   erSmootP psmo, psmo1;
   erCannyP pcan;
   erAdThrP padt;
   bool loaded; 
   std::list< CvPoint> cvPts;
   std::list< CgPoint> cgPts;
   std::list< CgSegmt> cgSeg;
   char* file_name =const_cast<char*>(firstImage.c_str());
   std::cout << file_name << std::endl;
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

   //IsEqualTo is_equal_255( 255);

   cvPts       = erExtractCvPoints( &ea); /* Extraction */
   erExtractCurveMacroDropUser( &ea, cvPts, rect, &cerc, file_name);
   cercToStart = cerc;
   char* nom   = const_cast<char*>(name.c_str());
   erPrintCvPoint( cvPts, file_name, nom); 
   return true;

   };

void erMacroDropAnalysis::defineParameter(CvRect rect,erCerc ecerc,erSmootP smooth1,erSmootP smooth2,erCannyP cann,erAdThrP adthr)
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
       char* nom       = const_cast<char*>(name.c_str());
       erImage erb, bwb, eab; 
       //std::list< CvPoint> cvPts;
       boost::tie(erb,loaded) = erLoadImage( file_name);
       if(!loaded) return false;
       bwb = erConvertToBlackAndWhite( &erb);        
       eab = erDef_ROI( &bwb, &rectOI);    
       erCvSmooth( &eab, &param_smooth1);
       erCvAdaptiveThreshold( &eab, &param_adaptive_threshold);
       erCvSmooth( &eab, &param_smooth2);
       erCvCanny( &eab, &param_canny);
       //erSaveImage( &eab, file_name);
       //IsEqualTo is_equal_255( 255);
       std::list<CvPoint> cvPts; 
       cvPts = erExtractCvPoints( &eab);
       erExtractCurveMacroDropUser( &eab, cvPts,rectOI,&cercToStart, file_name);
       erPrintCvPoint( cvPts, file_name,nom); 
       return true;
};
