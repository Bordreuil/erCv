#include <erCv/erCvAnalysis.hpp>
#include <erCv/erCvFilters.hpp>
#include <erCv/erCvSegmentation.hpp>
#include <erCv/utilities/erPredicates.hpp>
#include <erCv/erCvExtract.hpp>
#include <erCv/erCvToCgal.hpp>

#include <erCv/geometry/erGeometricalCharacteristics.hpp>
#include <erCv/Gui/erCvUserInteraction.hpp>
#include <erCv/Gui/erCvFiltersUser.hpp>
#include <erCv/Gui/erCvSegmentationUser.hpp>


#include <erCv/graph/erConnectedSegments.hpp>


#include<time.h>
#include<fstream>
#include<iomanip>
#include<boost/filesystem.hpp>

#include<CGAL/linear_least_squares_fitting_2.h>


std::string ANALYSIS_EXTENSION="_erCvAnalysis";

erAnalysis::erAnalysis( ){ };

erAnalysis::erAnalysis( std::string name, std::string infofile): 
  name( name), infoFile( infofile),_with_calibration(false)
{  
  dir_analysis = name + ANALYSIS_EXTENSION;
  create( );
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


void erAnalysis::define_calibration(std::string source,std::string target)
{  char* source_c =  const_cast<char*>(source.c_str());
   char*  target_c =   const_cast<char*>(target.c_str());
   _calibration      = erCalibration(source_c,target_c,3,3);
   _with_calibration = false;
};



/* Analysis pour le macro drop */

erMacroDropAnalysis::erMacroDropAnalysis() { };

erMacroDropAnalysis::erMacroDropAnalysis( std::string name, std::string infofile):
  erAnalysis( name, infofile), rectOI( ), cercToStart( ), param_smooth1( ), param_smooth2( ),
  param_canny( ), param_adaptive_threshold( )
{};

bool erMacroDropAnalysis::defineParametersUI( std::string firstImage)
{
  std::cout <<"-----------------------------------------------\n\n";
  std::cout <<"\tMagic treatment for metal transfer\n\tBy Edward Romero\n\tNovember 2009\n\tLMGC/UM2/UM5508\n\tANR-TEMMSA\n\n";
  std::cout <<"-----------------------------------------------\n\n";
  
  /* Declaration de variables a utiliser par les fonctions */
  INFOFILE = this->infoFile;
  
  erImage ea, eb, ec, ed;
  CvRect rect;
  erCerc cerc; 
  erSmootP psmo, psmo1;
  erCannyP pcan;
  erAdThrP padt;
  bool loaded; 
  std::list< CvPoint> cvPts;
  
  char* file_name =const_cast<char*>(firstImage.c_str());
  
  boost::tie(ea,loaded) = erLoadImage(file_name);
  if(!loaded) return false;
  eb            = erConvertToBlackAndWhite( &ea); /* Conversion en 8 bit single channel */
  //ed            = eb; 
  
  ec            = erDef_ROIuser( &eb, &rect);
  rectOI        = rect;
  erCvSmoothUser( &ec, &psmo);
  param_smooth1 = psmo;
  erCvAdaptiveThresholdUser( &ec, &padt);
  param_adaptive_threshold = padt;
  erCvSmoothUser( &ec, &psmo1);
  param_smooth2 = psmo1;
  erCvCannyUser( &ec, &pcan);
  param_canny   = pcan;
  
  IsEqualTo is_equal_255( 255);
  
  erExtractCvPoints( cvPts, &ec, is_equal_255, rect); /* Extraction */
  erExtractCurveMacroDropUser( cvPts, &ec, rect, &cerc, file_name);
  cercToStart = cerc;
  char* nom   = const_cast<char*>(name.c_str());
  erPrintCvPoint( cvPts, file_name, nom); 
  return true;
};



void erMacroDropAnalysis::defineParameters( CvRect rect, erCerc cerc, erSmootP smooth1, erSmootP smooth2, erCannyP cann, erAdThrP adthr)
{
  rectOI                   = rect;
  cercToStart              = cerc;
  param_smooth1            = smooth1;
  param_smooth2            = smooth2;
  param_canny              = cann;
  param_adaptive_threshold = adthr;
};

bool erMacroDropAnalysis::doIt(std::string fich)
{      bool loaded;
       char* file_name         = const_cast<char*>(fich.c_str());
       std::string output_name = (dir_analysis+"/"+name+"_mcr");
       char* nom               = const_cast<char*>(output_name.c_str());
       erImage ea, eb, ec, ed; 
       std::list<CvPoint> cvPts;       
       boost::tie( ea, loaded) = erLoadImage( file_name);
       if( !loaded) return false;
       eb = erConvertToBlackAndWhite( &ea);        
       ec = erDef_ROI( &eb, &rectOI);    
       erCvSmooth( &ec, &param_smooth1);
       erCvAdaptiveThreshold( &ec, &param_adaptive_threshold);
       erCvSmooth( &ec, &param_smooth2);
       erCvCanny( &ec, &param_canny);
       erSaveImage( &ec, file_name, nom);
       IsEqualTo is_equal_255( 255); 
       erExtractCvPoints( cvPts, &ec, is_equal_255, rectOI);
       erExtractCurveMacroDrop( cvPts, &ec, rectOI, &cercToStart, file_name);
       erPrintCvPoint( cvPts, file_name, nom); 
       return true;
};

void erMacroDropAnalysis::saveParameters(std::string file)
{ 
  std::string output_file=dir_analysis+"/"+file;
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






/* Analysis pour la goutelette de metal de tranfer*/

erMetalTransfertAnalysis::erMetalTransfertAnalysis(){ };

erMetalTransfertAnalysis::erMetalTransfertAnalysis( std::string name, std::string infofile):
  erAnalysis( name, infofile), rectOI( ), param_smooth1( ), param_smooth2( ), param_canny( ), 
  param_adaptive_threshold( ), param_alpha_shape(), output_geometry_characteristics(true)
{setOutputGeometryFile(name); }; 

bool erMetalTransfertAnalysis::defineParametersUI( std::string firstImage)
{ 
  std::cout <<"--------------------------------------------------\n\n";
  std::cout <<"\tMagic treatment for metal transfert\ntBy Edward Romero\n\tMay 2010\n\tLMGC/UM2/UM5508\n\tANR-TEMMSA\n\n";
  std::cout <<"-------------------------------------------------\n\n";
  
  /*Declaration de variables a utiliser par les fonctions */
  INFOFILE = this->infoFile;

  erImage ea, eb, ec, ed, ee;
  CvRect rect;
  erSmootP psmo, psmo1;
  erCannyP pcan;
  erAdThrP padt;
  std::list< CvPoint> cvPts;
  std::list< CgalPoint> cgalPts;
  std::list< CgalSegmt> cgalSeg, bgraphSeg;
  erAlphaP palp;
  bool loaded;

  char* file_name = const_cast< char*>(firstImage.c_str());

  boost::tie( ea, loaded) = erLoadImage( file_name);
  if(!loaded) return false;
  eb = erConvertToBlackAndWhite( &ea); /* Conversion en 8 bit single channel */
  ec = erDef_ROIuser( &eb, &rect);
  rectOI = rect;
  erCvSmoothUser( &ec, &psmo);
  param_smooth1 = psmo;
  erCvAdaptiveThresholdUser( &ec, &padt);
  param_adaptive_threshold = padt;
  erCvSmoothUser( &ec, &psmo1);
  param_smooth2 = psmo1;
  erCvCannyUser( &ec, &pcan);
  param_canny = pcan;

  IsEqualTo is_equal_255( 255);

  erExtractCvPoints( cvPts, &ec, is_equal_255, rect); /* Extraction */
  convertCvToCgalpoints( cvPts, cgalPts);
  alpha_edges_user( cgalPts, cgalSeg, &palp);
  param_alpha_shape = palp;
  largest_closed_segment( cgalSeg, bgraphSeg);
  char* nom = const_cast< char*>( name.c_str());
  erPrintCgalPoint( bgraphSeg, file_name, nom);
  return true; 
};



void erMetalTransfertAnalysis::defineParameters( CvRect rect, erSmootP smooth1, erSmootP smooth2, erCannyP cann, erAdThrP adthr, erAlphaP alphas)
{
  rectOI = rect;
  param_smooth1 = smooth1;
  param_smooth2 = smooth2;
  param_canny   = cann;
  param_adaptive_threshold = adthr;
  param_alpha_shape = alphas;
};

void erMetalTransfertAnalysis::setOutputGeometryFile(std::string file) //** Le fichier existant est ecrase!!
{
  output_geometry_file = dir_analysis+"/"+file+"_mtl"+".geo";
  std::ofstream out(output_geometry_file.c_str());
  out << "Nom_du_fichier\t\tCentroid_x\tCentroid_y\tAire\tAxe_Princ_x\tAxe_Princ_y\tFit(0-1)\n";

};

bool  erMetalTransfertAnalysis::doIt( std::string fich)
{
  bool loaded;
  char* file_name         = const_cast< char*>( fich.c_str());
  std::string output_name = (dir_analysis+"/"+name+"_mtl");
  char* nom = const_cast< char*>( output_name.c_str());
  erImage ea, eb, ec;
  std::list< CvPoint>   cvPts;
  std::list< CgalPoint> cgalPts;
  std::list< CgalSegmt> cgalSeg, bgraphSeg;

  boost::tie(ea, loaded) = erLoadImage( file_name);
  if( !loaded) return false;
  eb = erConvertToBlackAndWhite( &ea);
  ec = erDef_ROI( &eb, &rectOI);
  erCvSmooth( &ec, &param_smooth1);
  erCvAdaptiveThreshold( &ec, &param_adaptive_threshold);

  erCvSmooth( &ec, &param_smooth2);
  erCvCanny( &ec, &param_canny);

  erSaveImage( &ec, file_name, nom);

  IsEqualTo is_equal_255( 255);
  erExtractCvPoints( cvPts, &ec, is_equal_255, rectOI);
  
  convertCvToCgalpoints( cvPts, cgalPts);

  alpha_edges( cgalPts, cgalSeg, &param_alpha_shape);
  std::list< CgalSegmt>::iterator dede=cgalSeg.begin();
    
  largest_closed_segment( cgalSeg, bgraphSeg);
  erPrintCgalPoint( bgraphSeg, file_name, nom);

  if(output_geometry_characteristics && bgraphSeg.size() > 6)
    {
      std::list<CgalTrian> triangs=erGeometryExtractTriangles(bgraphSeg.begin(),bgraphSeg.end());
      double area   = getArea(triangs.begin(),triangs.end());
      CgalLine  line;
      CgalPoint pt;
      CgalFTrai fit = linear_least_squares_fitting_2(triangs.begin(),triangs.end(),line,pt,CGAL::Dimension_tag<2>());	
      std::ofstream ot(output_geometry_file.c_str(),std::ios_base::app);
      CgalVect vect=line.to_vector();
      ot << std::setprecision(10) << fich << "\t" << pt.x() << "\t" << pt.y() << "\t" << area << "\t" << vect.x() << "\t" << vect.y() <<"\t" << fit << std::endl;    
    };
 

  return true;
};


void erMetalTransfertAnalysis::saveParameters( std::string file)
{
  std::string output_file = dir_analysis+"/"+file;
  std::ofstream out( output_file.c_str());
  out << "* Begin er MetalTransfert Analysis" << std::endl;
  out << this->rectOI;
  out << this->param_smooth1;
  out << this->param_adaptive_threshold;
  out << this->param_smooth2;
  out << this->param_canny;
  //out << this->param_alpha_shape;
  out << "* End er MetalTransfert Analysis" << std::endl;
};









/* Analysis pour le bain de fusion */

/* Constructeur par defaut */
erWeldPoolAnalysis::erWeldPoolAnalysis(){};
//** Constructeur avec des paramettres determines ailleurs */
erWeldPoolAnalysis::erWeldPoolAnalysis( std::string name, std::string infofile): 
  erAnalysis( name, infofile), rectOI( ), param_smooth1( ), param_smooth2( ), 
  param_equalizer_histogram( ), param_canny( ), param_adaptive_threshold( ), 
  param_template( ), param_alpha_shape( ), param_find_contours( ) { };

//** Boucle de execution du programe en utilisant le la user interface de openCv */
bool erWeldPoolAnalysis::defineParametersUI( std::string firstImage) 
{
  std::cout <<"--------------------------------------------------\n\n";
  std::cout <<"\tMagic treatment for metal transfert\ntBy Edward Romero\n\tMay 2010\n\tLMGC/UM2/UM5508\n\tANR-TEMMSA\n\n";
  std::cout <<"-------------------------------------------------\n\n";
  
  /*Declaration de variables a utiliser par les fonctions */
  INFOFILE = this->infoFile;
  erImage ea, eb, ec, ed, ee;
  CvRect rect;
  erSmootP psmo, psmo1;
  erEqualP pequ;
  erCannyP pcan;
  erAdThrP padt;
  erTemplP ptem;
  erFindcP pfin;
  erWaterP pwat;
  std::list< CvPoint> cvPts;
  std::list< CgalPoint> cgalPts;
  std::list< CgalSegmt> cgalSeg, bgraphSeg;
  erAlphaP palp;
  bool loaded;
  
  char* file_name = const_cast< char*>(firstImage.c_str());
  
  boost::tie( ea, loaded) = erLoadImage( file_name);
  if(!loaded) return false;
  
  erCalibration ca( "cuadro5-rescale-511.jpg", "rec_droite_256_2.bmp", 3, 3);
  eb = ca.transform_image(ea);
  //erSaveImage2( &eb, name, exit, "tra");
  
  ec = erDef_ROIuser( &eb, &rect);
  rectOI = rect;
  
  erCvSmoothUser( &ec, &psmo);
  param_smooth1 = psmo;
  
  //erCvEqualizeHistUser( &ec, &pequ);
  //param_equalizer_histogram = pequ;
  
  ed = erCvTemplateUser( &ec, &ptem);
  param_template = ptem;
  
  erCvAdaptiveThresholdUser( &ed, &padt);
  param_adaptive_threshold = padt;
  
  //erCvWatershed( &ed, &pwat);
  
  erCvCannyUser( &ed, &pcan);
  param_canny = pcan;
  
  //erCvFindContours( &ed, &pfin);
  //param_find_contours = pfin;
  
  IsEqualTo is_equal_255(255);
  char* nom   = const_cast<char*>(name.c_str());
  erExtractCvPoints( cvPts, &ed, is_equal_255, rect);
  convertCvToCgalpoints( cvPts, cgalPts);
  
  alpha_edges( cgalPts, cgalSeg, &palp);
  
  erPrintCgalPoint( cgalSeg, file_name, nom);
  
  return true;
};

//void erWeldPoolAnalysis::defineParameters( CvRect rect, erSmootP smooth1, erSmootP smooth2, erEqualP equal, erCannyP canny, erAdThrP adthr, erTemplP templ, erAlphaP alphas, erFindcP findc)
void erWeldPoolAnalysis::defineParameters( CvRect rect, erSmootP smooth1, erSmootP smooth2, erEqualP equal, erCannyP canny, erAdThrP adthr, erTemplP templ, erAlphaP alphas)
{
  rectOI = rect;
  param_smooth1 = smooth1;
  param_smooth2 = smooth2;
  param_equalizer_histogram = equal;
  param_canny = canny;
  param_adaptive_threshold = adthr;
  param_template = templ;
  //param_find_contours = findc;
  param_alpha_shape = alphas;
};


bool erWeldPoolAnalysis::doIt(std::string fich)
{ 
  bool loaded;
  char* file_name         = const_cast< char*>( fich.c_str());
  std::string output_name = (dir_analysis+"/"+name+"_wep");
  char* nom = const_cast< char*>( output_name.c_str());
  erImage ea, eb, ec, ed, ee;
  CvRect rect;
  erSmootP psmo, psmo1;
  erEqualP pequ;
  erCannyP pcan;
  erAdThrP padt;
  erTemplP ptem;
  erFindcP pfin;
  erWaterP pwat;
  erAlphaP palp;
  std::list< CvPoint>   cvPts;
  std::list< CgalPoint> cgalPts;
  std::list< CgalSegmt> cgalSeg, bgraphSeg;
  
  boost::tie(ea, loaded) = erLoadImage( file_name);

  if( !loaded) return false;
 
  if( _with_calibration)
    {
      eb = _calibration.transform_image(ea);
    }
  else
    {
      eb = ea;
    };
  ec = erConvertToBlackAndWhite( &eb);
  
  ed = erDef_ROI( &ec, &rectOI);
 
  erCvSmooth( &ed, &param_smooth1);
  std::cout << "Aprs smooth" << std::endl;
  ee = erCvTemplate( &ed, &param_template);
  std::cout << "Aprs Template" << std::endl;
  erCvEqualizeHist( &ee, &param_equalizer_histogram);
  std::cout << "Aprs Equaliz" << std::endl;
  erCvAdaptiveThreshold( &ee, &param_adaptive_threshold);
  std::cout << "Aprs Adapt Thres" << std::endl;
  erCvCanny( &ee, &param_canny);
  std::cout << "Aprs Canny" << std::endl;
  erShowImage( "image_canny", &ee);
  //erSaveImage2Analysis( &ee, file_name, fich, "can");
  IsEqualTo is_equal_255(255);
  erExtractCvPoints( cvPts, &ee, is_equal_255, rect);
  convertCvToCgalpoints( cvPts, cgalPts);
  alpha_edges( cgalPts, cgalSeg, &param_alpha_shape);
  erPrintCgalPoint( cgalSeg, file_name, nom);
  return true;
  std::cout << "hola_Analysis" << std::endl;
};




/* On sauve garde les parammettres utilisé dans un ficher de backup */
void erWeldPoolAnalysis::saveParameters( std::string file)
{
  std::string output_file = dir_analysis+"/"+file;
  std::ofstream out( output_file.c_str());
  out << "* Begin er WeldPool Analysis" << std::endl;
  out << this->rectOI;
  out << this->param_smooth1;
  // out << this->param_equalizer_histogram;
  //out << this->param_template;
  out << this->param_adaptive_threshold;
  out << this->param_canny;  
  out << this->param_find_contours;
  //out << this->param_alpha_shape;
  out << "* End er WeldPool Analysis" << std::endl;
};


