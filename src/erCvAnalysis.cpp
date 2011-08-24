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

#include <erCv/erCvAnalysis.hpp>
#include <erCv/erCvFilters.hpp>
#include <erCv/erCvSegmentation.hpp>
#include <erCv/utilities/erPredicates.hpp>
#include <erCv/erCvExtract.hpp>
#include <erCv/erCvToCgal.hpp>

#include <erCv/geometry/erGeometricalCharacteristics.hpp>
#include <erCv/geometry/erCgalPolygon2.hpp>
#include <erCv/geometry/erCgalConvexPolygone.hpp>
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

/********************************************************************

                      ERANALYSIS

*********************************************************************/


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


//ATTENTION erCalibration doit inclure un ficher avec les facteurs de conversion
void erAnalysis::defineCalibration(std::string source,std::string target)
{  char* source_c    =  const_cast<char*>(source.c_str());
   char*  target_c   =   const_cast<char*>(target.c_str());
   _calibration      = erCalibration(source_c,target_c,3,3);
   _with_calibration = true;
};
void erAnalysis::setCurrentFileName(char* file)
{
  file_name = file;
}

char* erAnalysis::currentFileName()
{
  return file_name;
}

/********************************************************************

                      ER_MACRODROP_ANALYSIS

*********************************************************************/

erMacroDropAnalysis::erMacroDropAnalysis() { };

erMacroDropAnalysis::erMacroDropAnalysis( std::string name, std::string infofile):
  erAnalysis( name, infofile), rectOI( ), cercToStart( ), param_smooth1( ), param_smooth2( ),
  param_canny( ), param_adaptive_threshold( ), param_equalizer_histogram( )
{ };

bool erMacroDropAnalysis::defineParametersUI( std::string firstImage)
{
  std::cout <<"-----------------------------------------------\n\n";
  std::cout <<"\tMagic treatment for macroDrop\n\tBy Edward Romero\n\tNovember 2009\n\tLMGC/UM2/UM5508\n\tANR-TEMMSA\n\n";
  std::cout <<"-----------------------------------------------\n\n";
  
  /* Declaration de variables a utiliser par les fonctions */
  INFOFILE = this->infoFile;
  
  erImage ea, eb, ec, ed;
  CvRect rect;
  erCerc cerc; 
  erSmootP psmo, psmo1;
  erCannyP pcan;
  erAdThrP padt;
  erEqualP pequ;
  bool loaded; 
  std::list< CvPoint> cvPts;
  
  char* file_name =const_cast<char*>(firstImage.c_str());
  
  boost::tie(ea,loaded) = erLoadImage(file_name);
  if(!loaded) return false;
  eb            = erConvertToBlackAndWhite( &ea); /* Conversion en 8 bit single channel */
  //ed            = eb; 
  
  ec            = erDef_ROIuser( &eb, &rect);
  rectOI        = rect;
  erCvEqualizeHist( &ec, &pequ);
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



void erMacroDropAnalysis::defineParameters( CvRect rect, erCerc cerc, erSmootP smooth1, erSmootP smooth2, erCannyP cann, erAdThrP adthr, erEqualP equal)
{
  rectOI                   = rect;
  cercToStart              = cerc;
  param_smooth1            = smooth1;
  param_smooth2            = smooth2;
  param_canny              = cann;
  param_adaptive_threshold = adthr;
  param_equalizer_histogram = equal;
};

bool erMacroDropAnalysis::doIt(std::string fich)
{      bool loaded;
       char* file_name         = const_cast<char*>(fich.c_str());
       setCurrentFileName(file_name);
       erImage ea;
       boost::tie( ea, loaded) = erLoadImage( file_name);
       if( !loaded) return false;
       doItImage(ea);
};
bool erMacroDropAnalysis::doItImage(erImage& ea)
{      
       erImage  eb, ec, ed; 
       std::list<CvPoint> cvPts;
       std::string output_name = (dir_analysis+"/"+name+"_mcr");
       char* nom               = const_cast<char*>(output_name.c_str());

       std::cout << std::endl;
       eb = erConvertToBlackAndWhite( &ea);        
       ec = erDef_ROI( &eb, &rectOI); 
       //erShowImage("essai",&eb);
       erCvEqualizeHist( &ec, &param_equalizer_histogram);
       erCvSmooth( &ec, &param_smooth1);
       erCvAdaptiveThreshold( &ec, &param_adaptive_threshold);
       erCvSmooth( &ec, &param_smooth2);
       erCvCanny( &ec, &param_canny);
       erSaveImage( &ec, currentFileName(), nom);
       IsEqualTo is_equal_255( 255); 
       erExtractCvPoints( cvPts, &ec, is_equal_255, rectOI);
       erExtractCurveMacroDrop( cvPts, &ec, rectOI, &cercToStart,currentFileName());
       erPrintCvPoint( cvPts,currentFileName(), nom); 
       
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

/********************************************************************

                      ER_WIRE_ANALYSIS

*********************************************************************/



erWireAnalysis::erWireAnalysis(std::string name, std::string infofile):erMacroDropAnalysis(name,infofile){};

bool erWireAnalysis::doItImage(erImage& ea)
{      
       erImage  eb, ec, ed; 
       std::list<CvPoint> cvPts;
       std::string output_name = (dir_analysis+"/"+name+"_wire");
       char* nom               = const_cast<char*>(output_name.c_str());

       std::cout << std::endl;
       eb = erConvertToBlackAndWhite( &ea);        
       ec = erDef_ROI( &eb, &rectOI); 
 
       erCvEqualizeHist( &ec, &param_equalizer_histogram);
       erCvSmooth( &ec, &param_smooth1);

       erCvAdaptiveThreshold( &ec, &param_adaptive_threshold);
       erCvSmooth( &ec, &param_smooth2);
       erCvCanny( &ec, &param_canny);
 
       erSaveImage( &ec, currentFileName(), nom);
       IsEqualTo is_equal_255( 255); 
       erExtractCvPoints( cvPts, &ec, is_equal_255, rectOI);
       erExtractCurveWire( cvPts, &ec, rectOI, &cercToStart,currentFileName());

       erPrintCvPoint( cvPts,currentFileName(), nom); 
       
       return true;
};



/* Analysis pour la goutelette de metal de tranfer*/
/********************************************************************

                      METAL_TRANSFERT_ANALYSIS

*********************************************************************/
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
  ec = erDef_ROIuser( &eb, &rect,true);
  rectOI = rect;
  erCvSmoothUser( &ec, &psmo);
  param_smooth1 = psmo;
  erCvAdaptiveThresholdUser( &ec, &padt,true);
  param_adaptive_threshold = padt;
  erCvSmoothUser( &ec, &psmo1);
  param_smooth2 = psmo1;
  erCvCannyUser( &ec, &pcan,true);
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
               param_canny = cann;
  param_adaptive_threshold = adthr;
         param_alpha_shape = alphas;
};

void erMetalTransfertAnalysis::setOutputGeometryFile(std::string file) //** Le fichier existant est ecrase!!
{
  output_geometry_file = dir_analysis+"/"+file+"_mtl"+".geo";
  std::ofstream out(output_geometry_file.c_str());
  out << "Nom_du_fichier\t\tCentroid_x\tCentroid_y\tAire\tAxe_Princ_x\tAxe_Princ_y\tFit(0-1)\n";

};

bool erMetalTransfertAnalysis::doIt( std::string fich)
{
  erImage ea;
  bool loaded;
  char* file_name         = const_cast< char*>( fich.c_str());
  setCurrentFileName(file_name);
  boost::tie(ea, loaded) = erLoadImage( file_name);
  if( !loaded) return false;
  doItImage(ea);
};
bool erMetalTransfertAnalysis::doItImage(erImage& ea)
{
  erImage eb, ec;
  std::list< CvPoint>   cvPts;
  std::list< CgalPoint> cgalPts;
  std::list< CgalSegmt> cgalSeg, bgraphSeg;
  erEqualP pequ;

  std::string output_name = (dir_analysis+"/"+name+"_mtl");
  char* nom = const_cast< char*>( output_name.c_str());
  
  erSaveImage( &ea,currentFileName(), nom);
 
  eb = erConvertToBlackAndWhite( &ea);
 
  ec = erDef_ROI( &eb, &rectOI);

  erCvSmooth( &ec, &param_smooth1);
 
  erCvAdaptiveThreshold( &ec, &param_adaptive_threshold);
  //erSaveImage2( &ec, file_name, nom, "adp");
  erCvSmooth( &ec, &param_smooth2);
  //erSaveImage2( &ec, file_name, nom, "sm2");

  erCvCanny( &ec, &param_canny);
 
  IsEqualTo is_equal_255( 255);
  erExtractCvPoints( cvPts, &ec, is_equal_255, rectOI);
  
  convertCvToCgalpoints( cvPts, cgalPts);

  alpha_edges( cgalPts, cgalSeg, &param_alpha_shape);
  //std::list< CgalSegmt>::iterator dede=cgalSeg.begin();
  //erPrintCgalPoint( cgalSeg, file_name, nom);
    
  largest_closed_segment( cgalSeg, bgraphSeg);
  
  erPrintCgalPoint( bgraphSeg,currentFileName(), nom);

  if(output_geometry_characteristics && bgraphSeg.size() > 6)
    {
      std::list<CgalTrian> triangs=erGeometryExtractTriangles(bgraphSeg.begin(),bgraphSeg.end());
      double area   = getArea(triangs.begin(),triangs.end());
      CgalLine  line;
      CgalPoint pt;
      CgalFTrai fit = linear_least_squares_fitting_2(triangs.begin(),triangs.end(),line,pt,CGAL::Dimension_tag<2>());	
      std::ofstream ot(output_geometry_file.c_str(),std::ios_base::app);
      CgalVect vect=line.to_vector();
      ot << std::setprecision(10) << currentFileName() << "\t" << pt.x() << "\t" << pt.y() << "\t" << area << "\t" << vect.x() << "\t" << vect.y() <<"\t" << fit << std::endl;    
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


/********************************************************************

                      WELD_POOL_ANALYSIS

*********************************************************************/
/* Constructeur par defaut */
erWeldPoolAnalysis::erWeldPoolAnalysis(){};

//** Constructeur avec des paramettres determines ailleurs */
erWeldPoolAnalysis::erWeldPoolAnalysis( std::string name, std::string infofile): 
  erAnalysis( name, infofile), rectOI( ), param_white_blob( ), param_smooth1( ), param_smooth2( ), param_dilate( ), param_canny( ), param_threshold( ), param_template( ), param_alpha_shape( ), output_geometry_characteristics(true),output_convex_polygon(true){setOutputGeometryFile(name); }; 

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
  erSmootP psmo1, psmo2;
  erCannyP pcan;
  erThresP pthr;
  erTemplP ptem;
  erWhitBP pwhi;
  erDilatP pdil;
  std::list< CvPoint> cvPts;
  std::list< CgalPoint> cgalPts;
  std::list< CgalSegmt> cgalSeg, bgraphSeg;
  erAlphaP palp;
  bool loaded;
  
  char* file_name = const_cast< char*>(firstImage.c_str());
  
  boost::tie( ea, loaded) = erLoadImage( file_name);
  if(!loaded) return false;
  
  eb = erConvertToBlackAndWhite( &ea);
  
  erWhiteBlobCorrectionUser( &eb, &pwhi);
  //erWhiteBloborCorrection( &eb);
  param_white_blob = pwhi;

  if( _with_calibration)
    {
      ec = _calibration.transform_image(eb);
      //erSaveImage(&ec,file_name, nom+'calib');
      //erShowImage( "calib", &ec);
    }
  else
    {
      ec = eb;
    };
  
  
  ed = erDef_ROIuser( &ec, &rect,true);
  rectOI = rect;
  erCvSmoothUser( &ed, &psmo1);
  param_smooth1 = psmo1;
 

  ed = erCvTemplateUser( &ed, &ptem,true);
  param_template = ptem;


  erCvCannyUser( &ed, &pcan,true);
  param_canny = pcan;
  
  erCvDilateUser( &ed, &pdil,true);
  param_dilate = pdil;
  erCvSmoothUser( &ed, &psmo2);
  param_smooth2 = psmo2;
  /** erCvSmoothUser( &ed, &psmo1);
      param_smooth1 = psmo1; */

  //ee = erCvTemplateUser( &ed, &ptem,true);
  //param_template = ptem;
  
  erCvThresholdUser( &ed, &pthr,true);
  param_threshold = pthr;
  
  erCvCannyUser( &ee, &pcan,true);
  param_canny = pcan;
  
  IsEqualTo is_equal_255(255);
  char* nom   = const_cast<char*>(name.c_str());
  
  erExtractCvPoints( cvPts, &ee, is_equal_255, rect);
  convertCvToCgalpoints( cvPts, cgalPts);
  
  alpha_edges( cgalPts, cgalSeg, &palp);
  
  largest_closed_segment( cgalSeg, bgraphSeg);

  erPrintCgalPoint( bgraphSeg, file_name, nom);
  
  return true;
};


void erWeldPoolAnalysis::defineParameters( CvRect rect, erWhitBP whiteb, erSmootP smooth1, erSmootP smooth2, erCannyP canny, erDilatP dilate, erThresP thres, erTemplP templ, erAlphaP alphas)
{
  rectOI = rect;
  param_white_blob = whiteb;
  param_smooth1 = smooth1;
  param_smooth2 = smooth2;
  param_dilate = dilate;
  param_canny = canny;
  param_threshold = thres;
  param_template = templ;
  //param_find_contours = findc;
  param_alpha_shape = alphas;
};


void erWeldPoolAnalysis::setOutputGeometryFile(std::string file) //** Le fichier existant est ecrase!!
{
  output_geometry_file = dir_analysis+"/"+file+"_wep"+".geo";
  std::ofstream out(output_geometry_file.c_str());
  out << "Nom_du_fichier\t\t\t\tCentroid_x\tCentroid_y\tAire\tAxe_Princ_x\tAxe_Princ_y\tFit(0-1)\n";

};

bool erWeldPoolAnalysis::doIt(std::string fich)
{ 
  bool loaded;
  char* file_name         = const_cast< char*>( fich.c_str());
  setCurrentFileName(file_name);
  erImage ea;
  
  boost::tie(ea, loaded) = erLoadImage( file_name);
  if( !loaded)return false;
  doItImage(ea);
};
bool erWeldPoolAnalysis::doItImage(erImage& ea)
{
  erImage  eb, ec, ed, ee;
  std::list< CvPoint>   cvPts;
  std::list< CgalPoint> cgalPts, cgalPts2;
  std::list< CgalSegmt> cgalSeg, bgraphSeg;
  std::string output_name = (dir_analysis+"/"+name+"_wep");
  char* nom = const_cast< char*>( output_name.c_str());
  eb = erConvertToBlackAndWhite( &ea); 
  
 
  erWhiteBlobCorrection( &eb, &param_white_blob);
  
  
  /** Modif temp */
  erCvSmooth( &eb, &param_smooth1);
 
  /** Jusque la */
  if( _with_calibration)
    {
      ec = _calibration.transform_image(eb);
      //erSaveImage(&ec,file_name, nom+'calib');
      //erShowImage( "calib", &ec);
    }
  else
    {
      ec = eb;
    };

  ed = erDef_ROI( &ec, &rectOI);
  
  erCvCanny( &ed, &param_canny);
 
  
  erCvDilate( &ed, &param_dilate);
 

  /**
  erCvSmooth( &ed, &param_smooth1);
  nomc= const_cast< char*>( (output_name+"blur").c_str());
  erSaveImage( &ed, file_name, nomc);
  erShowImage( "blur", &ed);
  */
  erCvSmooth( &ed, &param_smooth2);
 

  ee = erCvTemplate( &ed, &param_template);
  erCvThreshold( &ee, &param_threshold);
  erCvCanny( &ee, &param_canny);


  IsEqualTo is_equal_255(255);
  erExtractCvPoints( cvPts, &ee, is_equal_255, rectOI);

  convertCvToCgalpoints( cvPts, cgalPts);
  

  alpha_edges( cgalPts, cgalSeg, &param_alpha_shape);
 
  largest_closed_segment( cgalSeg, bgraphSeg);
 

  convex_hull( bgraphSeg, cgalPts2);
 

  double area;

  if(output_convex_polygon)
  {
    std::list<CgalPoint> polygon = erGeometryExtractConvexPolygon(bgraphSeg.begin(),bgraphSeg.end());

      std::string output_nam = (dir_analysis+"/"+name+"_wep_poly");
      char* name = const_cast< char*>( output_nam.c_str());
      erPrintCgalPoint(polygon,currentFileName(),name);
      Polygon_2 poly(polygon.begin(),polygon.end());
      area = poly.area();
    };
  if(output_geometry_characteristics && bgraphSeg.size() > 6)
    {
      std::list<CgalTrian> triangs=erGeometryExtractTriangles(bgraphSeg.begin(),bgraphSeg.end());
      if(!not output_convex_polygon)
	{
	 area   = getArea(triangs.begin(),triangs.end());
	};
      CgalLine  line;
      CgalPoint pt;
      CgalFTrai fit = linear_least_squares_fitting_2(triangs.begin(),triangs.end(),line,pt,CGAL::Dimension_tag<2>());	
      std::ofstream ot(output_geometry_file.c_str(),std::ios_base::app);
      CgalVect vect=line.to_vector();
      ot << std::setprecision(10) << currentFileName() << "\t" << pt.x() << "\t" << pt.y() << "\t" << area << "\t" << vect.x() << "\t" << vect.y() <<"\t" << fit << std::endl;    
    };
  return true;
 
};

/* On sauve garde les parammettres utilisé dans un ficher de backup */
void erWeldPoolAnalysis::saveParameters( std::string file)
{
  std::string output_file = dir_analysis+"/"+file;
  std::ofstream out( output_file.c_str());
  out << "* Begin er WeldPool Analysis" << std::endl;
  out << this->rectOI;
  //out << this->param_white_blob;
  out << this->param_canny;
  //out << this->param_dilate;
  out << this->param_smooth1;
  out << this->param_smooth2;
  //out << this->param_template;
  //out << this->param_threshold;
  out << this->param_canny;
  //out << this->param_alpha_shape;
  out << "* End er WeldPool Analysis" << std::endl;
};


/********************************************************************

                      LASER_ANALYSIS

*********************************************************************/


/* Constructeur par defaut */
erLaserPrototypageAnalysis::erLaserPrototypageAnalysis(){};

//** Constructeur avec des paramettres determines ailleurs */
erLaserPrototypageAnalysis::erLaserPrototypageAnalysis( std::string name, std::string infofile): 
  erAnalysis( name, infofile), rectOI( ), param_smooth1( ), param_smooth2( ), param_canny( ),  param_dilate( ), param_threshold( ), param_adaptive_threshold( ), param_template( ), param_alpha_shape( ), output_geometry_characteristics(true),output_convex_polygon(true){setOutputGeometryFile(name); }; 

//** Boucle de execution du programe en utilisant le la user interface de openCv */
bool erLaserPrototypageAnalysis::defineParametersUI( std::string firstImage) 
{
  std::cout <<"--------------------------------------------------\n\n";
  std::cout <<"\tMagic treatment for metal transfert\ntBy Edward Romero\n\tMay 2010\n\tLMGC/UM2/UM5508\n\tANR-TEMMSA\n\n";
  std::cout <<"-------------------------------------------------\n\n";
  
  /*Declaration de variables a utiliser par les fonctions */
  INFOFILE = this->infoFile;
  erImage ea, eb, ec, ed, ee;
  CvRect rect;
  erSmootP psmo1, psmo2;
  erCannyP pcan;
  erThresP pthr;
  erTemplP ptem;
  erDilatP pdil;
  std::list< CvPoint> cvPts;
  std::list< CgalPoint> cgalPts;
  std::list< CgalSegmt> cgalSeg, bgraphSeg;
  erAlphaP palp;
  bool loaded;
  
  char* file_name = const_cast< char*>(firstImage.c_str());
  
  boost::tie( ea, loaded) = erLoadImage( file_name);
  if(!loaded) return false;
  
  ed = erDef_ROIuser( &eb, &rect);
  rectOI = rect;

  erCvCannyUser( &ed, &pcan);
  param_canny = pcan;
  
  erCvDilateUser( &ed, &pdil);
  param_dilate = pdil;
  
  erCvSmoothUser( &ed, &psmo1);
  param_smooth1 = psmo1;

  erCvSmoothUser( &ed, &psmo2);
  param_smooth2 = psmo2;

  ee = erCvTemplateUser( &ed, &ptem);
  param_template = ptem;
  
  erCvThresholdUser( &ee, &pthr);
  param_threshold = pthr;
  
  erCvCannyUser( &ee, &pcan);
  param_canny = pcan;
  
  IsEqualTo is_equal_255(255);
  char* nom   = const_cast<char*>(name.c_str());
  
  erExtractCvPoints( cvPts, &ee, is_equal_255, rect);
  convertCvToCgalpoints( cvPts, cgalPts);
  
  alpha_edges( cgalPts, cgalSeg, &palp);
  
  largest_closed_segment( cgalSeg, bgraphSeg);

  erPrintCgalPoint( bgraphSeg, file_name, nom);
  
  return true;
};

//void erWeldPoolAnalysis::defineParameters( CvRect rect, erSmootP smooth1, erSmootP smooth2, erEqualP equal, erCannyP canny, erAdThrP adthr, erTemplP templ, erAlphaP alphas, erFindcP findc)
void erLaserPrototypageAnalysis::defineParameters_diffuse( CvRect rect, erSmootP smooth, erCannyP canny, erAdThrP adthr, erAlphaP alphas)
{
  rectOI = rect;
  param_smooth1 = smooth;
  param_canny = canny;
  param_adaptive_threshold = adthr;
  param_alpha_shape = alphas;
};


//void erWeldPoolAnalysis::defineParameters( CvRect rect, erSmootP smooth1, erSmootP smooth2, erEqualP equal, erCannyP canny, erAdThrP adthr, erTemplP templ, erAlphaP alphas, erFindcP findc)
void erLaserPrototypageAnalysis::defineParameters( CvRect rect, erSmootP smooth1, erSmootP smooth2, erCannyP canny, erDilatP dilate, erThresP thres, erTemplP templ, erAlphaP alphas)
{
  rectOI = rect;
  param_smooth1 = smooth1;
  param_smooth2 = smooth2;
  param_dilate = dilate;
  param_canny = canny;
  param_threshold = thres;
  param_template = templ;
  //param_find_contours = findc;
  param_alpha_shape = alphas;
};



void erLaserPrototypageAnalysis::setOutputGeometryFile(std::string file) //** Le fichier existant est ecrase!!
{
  output_geometry_file = dir_analysis+"/"+file+"_wep"+".geo";
  std::ofstream out(output_geometry_file.c_str());
  out << "Nom_du_fichier\t\tCentroid_x\tCentroid_y\tAire\tAxe_Princ_x\tAxe_Princ_y\tFit(0-1)\n";
};


bool erLaserPrototypageAnalysis::doIt_diffuse(std::string fich)
{ 
  bool loaded;
  char* file_name         = const_cast< char*>( fich.c_str());
  std::string output_name = (dir_analysis+"/"+name+"_wep");
  char* nom = const_cast< char*>( output_name.c_str());
  erImage ea, eb, ec, ed, ee;
  std::list< CvPoint>   cvPts;
  std::list< CgalPoint> cgalPts;
  std::list< CgalSegmt> cgalSeg, bgraphSeg;
  
  boost::tie(ea, loaded) = erLoadImage( file_name);
  if( !loaded) return false;

  eb = erConvertToBlackAndWhite( &ea);
  erSaveImage( &eb, file_name, nom);

  ec = erDef_ROI( &eb, &rectOI);

  erCvAdaptiveThreshold( &ec, &param_adaptive_threshold);

  erCvSmooth( &ec, &param_smooth1);

  erCvCanny( &ec, &param_canny);

  //erShowImage( "result canny", &ec);
  //erSaveImage2Analysis( &ee, file_name, fich, "can");

  IsEqualTo is_equal_255(255);
  erExtractCvPoints( cvPts, &ec, is_equal_255, rectOI);
 
  convertCvToCgalpoints( cvPts, cgalPts);

  alpha_edges( cgalPts, cgalSeg, &param_alpha_shape);

  largest_closed_segment( cgalSeg, bgraphSeg);

  erPrintCgalPoint( bgraphSeg, file_name, nom);
  if(output_convex_polygon)
  {
      std::list<CgalPoint> polygon = erGeometryExtractConvexPolygon(bgraphSeg.begin(),bgraphSeg.end());
      std::string output_nam = (dir_analysis+"/"+name+"_wep_poly");
      char* name = const_cast< char*>( output_nam.c_str());
      erPrintCgalPoint(polygon,file_name,name);
    };
  if(output_geometry_characteristics && bgraphSeg.size() > 6)
    {
      std::list<CgalTrian> triangs=erGeometryExtractTriangles(bgraphSeg.begin(),bgraphSeg.end());
      double area   = getArea(triangs.begin(),triangs.end());
      CgalLine  line;
      CgalPoint pt;
      CgalFTrai fit = linear_least_squares_fitting_2(triangs.begin(),triangs.end(),line,pt,CGAL::Dimension_tag<2>());	
      std::ofstream ot(output_geometry_file.c_str(),std::ios_base::app);
      CgalVect vect=line.to_vector();
      ot << std::setprecision(10) << currentFileName() << "\t" << pt.x() << "\t" << pt.y() << "\t" << area << "\t" << vect.x() << "\t" << vect.y() <<"\t" << fit << std::endl;    
    };
  return true;
};




bool erLaserPrototypageAnalysis::doIt(std::string fich)
{ 
  bool loaded;
  char* file_name         = const_cast< char*>( fich.c_str());
  setCurrentFileName(file_name);
  erImage ea;
  boost::tie(ea, loaded) = erLoadImage( file_name);
  if( !loaded) return false;
  doItImage(ea);
};
bool erLaserPrototypageAnalysis::doItImage(erImage& ea)
{

  std::string output_name = (dir_analysis+"/"+name+"_wep");
  char* nom = const_cast< char*>( output_name.c_str());
  erImage eb, ec, ed, ee;
  std::list< CvPoint>   cvPts;
  std::list< CgalPoint> cgalPts;
  std::list< CgalSegmt> cgalSeg, bgraphSeg;
  
  ec = erConvertToBlackAndWhite( &ea);
  erSaveImage( &ec,currentFileName(), nom);

  ed = erDef_ROI( &ec, &rectOI);
  
  erCvCanny( &ed, &param_canny);
 
  erCvDilate( &ed, &param_dilate);

  erCvSmooth( &ed, &param_smooth1);

  erCvSmooth( &ed, &param_smooth2);

  ee = erCvTemplate( &ed, &param_template);

  erCvThreshold( &ee, &param_threshold);

  erCvCanny( &ee, &param_canny);
  //erShowImage( "result canny 2", &ee);
  //erSaveImage2Analysis( &ee, file_name, fich, "can");

  IsEqualTo is_equal_255(255);
  erExtractCvPoints( cvPts, &ee, is_equal_255, rectOI);
 
  convertCvToCgalpoints( cvPts, cgalPts);

  alpha_edges( cgalPts, cgalSeg, &param_alpha_shape);

  largest_closed_segment( cgalSeg, bgraphSeg);

  erPrintCgalPoint( bgraphSeg,currentFileName(), nom);
 
  if(output_convex_polygon)
  {
      std::list<CgalPoint> polygon = erGeometryExtractConvexPolygon(bgraphSeg.begin(),bgraphSeg.end());
      std::string output_nam = (dir_analysis+"/"+name+"_wep_poly");
      char* name = const_cast< char*>( output_nam.c_str());
      erPrintCgalPoint(polygon,currentFileName(),name);
    };

  if(output_geometry_characteristics && bgraphSeg.size() > 6)
    {
      std::list<CgalTrian> triangs=erGeometryExtractTriangles(bgraphSeg.begin(),bgraphSeg.end());
      double area   = getArea(triangs.begin(),triangs.end());
      CgalLine  line;
      CgalPoint pt;
      CgalFTrai fit = linear_least_squares_fitting_2(triangs.begin(),triangs.end(),line,pt,CGAL::Dimension_tag<2>());	
      std::ofstream ot(output_geometry_file.c_str(),std::ios_base::app);
      CgalVect vect=line.to_vector();
      ot << std::setprecision(10) << currentFileName() << "\t" << pt.x() << "\t" << pt.y() << "\t" << area << "\t" << vect.x() << "\t" << vect.y() <<"\t" << fit << std::endl;    
    };
  return true;
};

/* On sauve garde les parammettres utilisé dans un ficher de backup */
void erLaserPrototypageAnalysis::saveParameters( std::string file)
{
  std::string output_file = dir_analysis+"/"+file;
  std::ofstream out( output_file.c_str());
  out << "* Begin er LaserPrototypage Analysis" << std::endl;
  out << this->rectOI;
  //out << this->param_white_blob;
  out << this->param_canny;
  //out << this->param_dilate;
  out << this->param_smooth1;
  out << this->param_smooth2;
  //out << this->param_template;
  //out << this->param_threshold;
  out << this->param_canny;
  //out << this->param_alpha_shape;
  out << "* End er WeldPool Analysis" << std::endl;
};
