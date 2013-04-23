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
#include <erCv/graph/erShortestPaths.hpp>

#include<time.h>
#include<fstream>
#include<iomanip>
#include<boost/filesystem.hpp>
#include<boost/lexical_cast.hpp>
#include<CGAL/linear_least_squares_fitting_2.h>


std::string ANALYSIS_EXTENSION="_erCvAnalysis";

/********************************************************************

                      ER_ANALYSIS

*********************************************************************/


erAnalysis::erAnalysis( ){ };

erAnalysis::erAnalysis( std::string name, std::string infofile): 
  name( name), infoFile( infofile),_with_calibration(false),_output_geometry_characteristics(true),
  _output_axisymmetric(false),_output_convex(false),_output_intermediate_images(false)
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
{  char* source_c    = const_cast<char*>(source.c_str());
   char*  target_c   = const_cast<char*>(target.c_str());
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
bool        erAnalysis::outputGeometry()
{
  return _output_geometry_characteristics;
};
void erAnalysis::writeOutGeometry(SegmentList& bgraphSeg,std::string dataFile)
{ //std::cout << outputGeometryFile().c_str() << std::endl;
  //std::cout << bgraphSeg.size() << std::endl;
  if( outputGeometry() && bgraphSeg.size() > 40)
    {
      std::list<CgalTrian> triangs;
      if(!outputAxisymmetricGeometry())
	{
	  triangs=erGeometryExtractTriangles(bgraphSeg.begin(),bgraphSeg.end());
	}
      else
	{
	  triangs=erGeometryExtractTrianglesWithMesh(bgraphSeg.begin(),bgraphSeg.end());
	};
	  double area; 
	  CgalLine  line;
	  CgalPoint pt;
	  CgalFTrai fit = linear_least_squares_fitting_2(triangs.begin(),triangs.end(),line,pt,CGAL::Dimension_tag<2>());
	  CgalVect vect  = line.to_vector();
      if(!outputAxisymmetricGeometry())
	{	
	  area     = erGetArea(triangs.begin(),triangs.end());
	}
      else
	{
	  area   =erGetAreaAxi(triangs.begin(),triangs.end(),pt,vect);
	}
	  std::ofstream ot(outputGeometryFile().c_str(),std::ios_base::app);

	  ot << std::setprecision(10) << currentFileName() << "\t" << dataFile << "\t" << pt.x() << "\t" << pt.y() << "\t" << area  << "\t" << vect.x() << "\t" << vect.y() <<"\t" << fit << std::endl;        
    }
};

void         erAnalysis::setOutputGeometryFile(std::string outputgeometry)
{ 
  _output_geometry_file = dir_analysis+"/"+outputgeometry+".geo";
  std::ofstream out(_output_geometry_file.c_str());
  std::cout << "-----Fichier de stockage de la geometry:\t\t" << _output_geometry_file << std::endl;
  if(outputAxisymmetricGeometry())
    {
       out << "Nom_du_fichier\tNom_du_contour\tCentroid_x\tCentroid_y\tVolume\tAxe_Princ_x\tAxe_Princ_y\tFit(0-1)\n";
    }
  else
    {
      out << "Nom_du_fichier\tNom_du_contour\tCentroid_x\tCentroid_y\tAire\tAxe_Princ_x\tAxe_Princ_y\tFit(0-1)\n";
    };
};

std::string erAnalysis::outputGeometryFile()
{
  return _output_geometry_file;
};

void        erAnalysis::setOuputGeometry(bool out)
{
  _output_geometry_characteristics = out;
};
bool        erAnalysis::outputAxisymmetricGeometry()
{
  return _output_axisymmetric; 
};
void        erAnalysis::setOutputAxisymmetricGeometry(bool axi)
{  
  _output_axisymmetric = axi;
  
};
bool        erAnalysis::outputIntermediateImages()
{
  return _output_intermediate_images; 
};
void        erAnalysis::setOutputIntermediateImages(bool ii)
{  
  _output_intermediate_images = ii;
  
};
bool    erAnalysis::outputConvex()
{
  return _output_convex;
};
void erAnalysis::setOutputConvex(bool out)
{
  _output_convex=out;
  // setOutputGeometryFile(outputGeometryFile());
};


/********************************************************************

                      ER_MACRODROP_ANALYSIS

*********************************************************************/

erMacroDropAnalysis::erMacroDropAnalysis() { };

erMacroDropAnalysis::erMacroDropAnalysis( std::string name, std::string infofile):
  erAnalysis( name, infofile), rectOI( ), cerc_to_start( ), param_smooth1( ), param_smooth2( ),
  param_canny( ), param_adaptive_threshold( ), param_equalizer_histogram( )
{ };




void erMacroDropAnalysis::defineParameters( CvRect rect, erCerc cerc, erSmootP smooth1, erSmootP smooth2, erCannyP cann, erAdThrP adthr, erEqualP equal)
{
  rectOI                   = rect;
  cerc_to_start            = cerc;
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
       output_name = (dir_analysis+"/"+name+"_mcr");
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
       erExtractCurveMacroDrop( cvPts, &ec, rectOI, &cerc_to_start,currentFileName());
       erPrintCvPoint( cvPts,currentFileName(), nom); 
       
       return true;
};



/********************************************************************

                      ER_WIRE_ANALYSIS

*********************************************************************/



erWireAnalysis::erWireAnalysis(std::string name, std::string infofile):erMacroDropAnalysis(name,infofile),cerc_to_end(),param_alpha_shape(){};
void erWireAnalysis::setEndZone(erCerc cerc)
{
  cerc_to_end = cerc;
};
void erWireAnalysis::setBeginZone(erCerc cerc)
{
  cerc_to_start = cerc;
};
bool erWireAnalysis::doItImage(erImage& ea)
{      
       erImage  eb, ec, ed; 
       
       std::list<CvPoint>    cv_pts;
       std::list< CgalPoint> cgal_pts,cgal_wire_pts;
       std::list< CgalSegmt> cgalSeg, bgraphSeg;
       
       output_name = (dir_analysis+"/"+name+"_wire");
       char* nom               = const_cast<char*>(output_name.c_str());

       eb = erConvertToBlackAndWhite( &ea);        
       ec = erDef_ROI( &eb, &rectOI); 
 
       erCvEqualizeHist( &ec, &param_equalizer_histogram);
       erCvSmooth( &ec, &param_smooth1);
       
       erCvAdaptiveThreshold( &ec, &param_adaptive_threshold);
       
       erCvSmooth( &ec, &param_smooth2);
       
       erCvCanny( &ec, &param_canny);
       
       erSaveImage( &ec, currentFileName(), nom);
       IsEqualTo is_equal_255( 255); 
       erExtractCvPoints( cv_pts, &ec, is_equal_255, rectOI);
       convertCvToCgalpoints( cv_pts, cgal_pts);

       erAlphaEdges( cgal_pts, cgalSeg, &param_alpha_shape);
      
       cgal_wire_pts = erGetShortestPath(cgalSeg.begin(),cgalSeg.end(),cerc_to_start,cerc_to_end);
      
  
       erPrintCgalPoint( cgal_wire_pts,currentFileName(), nom);

             
       return true;
};



/* Analysis pour la goutelette de metal de tranfer*/
/********************************************************************

                      METAL_TRANSFERT_ANALYSIS

*********************************************************************/
erMetalTransfertAnalysis::erMetalTransfertAnalysis(){ };

erMetalTransfertAnalysis::erMetalTransfertAnalysis( std::string name, std::string infofile):
  erAnalysis( name, infofile), rectOI( ), param_smooth1( ), param_smooth2( ), param_canny( ), 
  param_adaptive_threshold( ), param_alpha_shape()
{}; 



void erMetalTransfertAnalysis::defineParameters( CvRect rect, erSmootP smooth1, erSmootP smooth2, erCannyP cann, erAdThrP adthr, erAlphaP alphas)
{
                    rectOI = rect;
             param_smooth1 = smooth1;
             param_smooth2 = smooth2;
               param_canny = cann;
  param_adaptive_threshold = adthr;
         param_alpha_shape = alphas;
};


bool erMetalTransfertAnalysis::doIt( std::string fich)
{
  erImage ea;
  bool loaded;
  char* file_name         = const_cast< char*>( fich.c_str());
  setCurrentFileName(file_name);
  boost::tie(ea, loaded) = erLoadImage( file_name);
  if( !loaded) return false;
  return doItImage(ea);
};
bool erMetalTransfertAnalysis::doItImage(erImage& ea)
{
  erImage eb, ec;
  std::list< CvPoint>   cvPts;
  std::list< CgalPoint> cgalPts;
  std::list< CgalSegmt> cgalSeg, bgraphSeg;
  erEqualP pequ;
 
  output_name = (dir_analysis+"/"+name+"_mtl");
  char* nom = const_cast< char*>( output_name.c_str());
  
  erSaveImage( &ea,currentFileName(), nom);
 
  eb = erConvertToBlackAndWhite( &ea);
 
  ec = erDef_ROI( &eb, &rectOI);
 
  erCvSmooth( &ec, &param_smooth1);
    if(outputIntermediateImages())
    {
      char* nomc= const_cast< char*>( (output_name+"_1_smooth").c_str());
      erSaveImage( &ec, file_name, nomc);
    };
  erCvAdaptiveThreshold( &ec, &param_adaptive_threshold);
  if(outputIntermediateImages())
    {
      char* nomc= const_cast< char*>( (output_name+"_2_adaptThresh").c_str());
      erSaveImage( &ec, file_name, nomc);
    };
  erCvSmooth( &ec, &param_smooth2);
  if(outputIntermediateImages())
    {
      char* nomc= const_cast< char*>( (output_name+"_3_smooth").c_str());
      erSaveImage( &ec, file_name, nomc);
    };
  erCvCanny( &ec, &param_canny);
   if(outputIntermediateImages())
    {
      char* nomc= const_cast< char*>( (output_name+"_4_canny").c_str());
      erSaveImage( &ec, file_name, nomc);
    };
 
  IsEqualTo is_equal_255( 255);
  erExtractCvPoints( cvPts, &ec, is_equal_255, rectOI);
  
  convertCvToCgalpoints( cvPts, cgalPts);

  erAlphaEdges( cgalPts, cgalSeg, &param_alpha_shape);

  //std::list< CgalSegmt>::iterator dede=cgalSeg.begin();
  //std::string naname(nom);
  //std::string extension("_after_alpha_shape_");
  //std::string final=nom+extension;
  //char* Cnom = const_cast< char*>( final.c_str());
  //erPrintCgalPoint( cgalSeg, currentFileName(),Cnom);
    
  erLargestClosedPolygon( cgalSeg, bgraphSeg);
  
  erPrintCgalPoint( bgraphSeg,currentFileName(), nom);
  writeOutGeometry(bgraphSeg);
  // if(output_geometry_characteristics && bgraphSeg.size() > 6)
  //   {
  //     std::list<CgalTrian> triangs=erGeometryExtractTriangles(bgraphSeg.begin(),bgraphSeg.end());
  //     double area   = getArea(triangs.begin(),triangs.end());
  //     CgalLine  line;
  //     CgalPoint pt;
  //     CgalFTrai fit = linear_least_squares_fitting_2(triangs.begin(),triangs.end(),line,pt,CGAL::Dimension_tag<2>());	
  //     std::ofstream ot(output_geometry_file.c_str(),std::ios_base::app);
  //     CgalVect vect=line.to_vector();
  //     ot << std::setprecision(10) << currentFileName() << "\t" << pt.x() << "\t" << pt.y() << "\t" << area << "\t" << vect.x() << "\t" << vect.y() <<"\t" << fit << std::endl;    
  //   };
 

  return true;
};
/********************************************************************


             MULTI_TRANSFERT_ANALYSIS


 *******************************************************************/

erMultiMetalTransfertAnalysis::erMultiMetalTransfertAnalysis(){ };

erMultiMetalTransfertAnalysis::erMultiMetalTransfertAnalysis( std::string name, std::string infofile):
  erAnalysis( name, infofile), rectOI( ), param_smooth1( ), param_smooth2( ), param_canny( ), 
  param_adaptive_threshold( ), param_alpha_shape()
{}; 



void erMultiMetalTransfertAnalysis::defineParameters( CvRect rect, erSmootP smooth1, erSmootP smooth2, erCannyP cann, erAdThrP adthr, erAlphaP alphas)
{
                    rectOI = rect;
             param_smooth1 = smooth1;
             param_smooth2 = smooth2;
               param_canny = cann;
  param_adaptive_threshold = adthr;
         param_alpha_shape = alphas;
};


bool erMultiMetalTransfertAnalysis::doIt( std::string fich)
{
  erImage ea;
  bool loaded;
  char* file_name         = const_cast< char*>( fich.c_str());
  setCurrentFileName(file_name);
  boost::tie(ea, loaded) = erLoadImage( file_name);
  if( !loaded) return false;
  return doItImage(ea);
};
bool erMultiMetalTransfertAnalysis::doItImage(erImage& ea)
{
  erImage eb, ec;
  std::list< CvPoint>   cvPts;
  std::list< CgalPoint> cgalPts;
  std::list< CgalSegmt> cgalSeg;
  BgraphSegmtMap  connectedSegments; 
  erEqualP pequ;
  //std::cout << name << std::endl;
  output_name = dir_analysis+"/"+name+"_multi_mtl";
  
 
 
  eb = erConvertToBlackAndWhite( &ea);
  if(outputIntermediateImages())
    {
      char* nomb= const_cast< char*>( (output_name+"_1_blackWhite").c_str());
      erSaveImage( &eb, file_name, nomb);
    };
  ec = erDef_ROI( &eb, &rectOI);
 
  erCvSmooth( &ec, &param_smooth1);
  if(outputIntermediateImages())
    {
      char* nomc= const_cast< char*>( (output_name+"_2_smooth").c_str());
      erSaveImage( &ec, file_name, nomc);
    };
  erCvAdaptiveThreshold( &ec, &param_adaptive_threshold);
  if(outputIntermediateImages())
    {
      char* nomd= const_cast< char*>( (output_name+"_3_adaptive").c_str());
      erSaveImage( &ec, file_name, nomd);
    };
  erCvSmooth( &ec, &param_smooth2);
  if(outputIntermediateImages())
    {
      char* nome= const_cast< char*>( (output_name+"_4_smooth").c_str());
      erSaveImage( &ec, file_name, nome);
    };
  erCvCanny( &ec, &param_canny);
  if(outputIntermediateImages())
    {
      char* nomf= const_cast< char*>( (output_name+"_5_canny").c_str());
      erSaveImage( &ec, file_name, nomf);
    };

  IsEqualTo is_equal_255( 255);
  erExtractCvPoints( cvPts, &ec, is_equal_255, rectOI);
  
  convertCvToCgalpoints( cvPts, cgalPts);

  erAlphaEdges( cgalPts, cgalSeg, &param_alpha_shape);

  erConnectedSegments( cgalSeg, connectedSegments);
  BgraphSegmtMap::iterator dede = connectedSegments.begin();
  uint idf=0;
  for(;dede!=connectedSegments.end();dede++)
    { std::string num=boost::lexical_cast<std::string>(idf);
      std::string fich=output_name+"_"+num;
      char* fileOut = const_cast< char*>(fich.c_str());
      erPrintCgalPoint( dede->second,currentFileName(), fileOut);
      writeOutGeometry(dede->second,fich);
      idf+=1;
    }
 
 

  return true;
};


/* Analysis pour billes de plomb*/
/********************************************************************

                      CREATIS_ANALYSIS

*********************************************************************/
erCreatisAnalysis::erCreatisAnalysis(){ };

erCreatisAnalysis::erCreatisAnalysis( std::string name, std::string infofile):
  erAnalysis( name, infofile), rectOI( ), param_smooth1( ), param_smooth2( ), param_canny( ), 
  param_adaptive_threshold( ), param_alpha_shape()
{}; 



void erCreatisAnalysis::defineParameters( CvRect rect, erSmootP smooth1, erSmootP smooth2, erCannyP cann, erAdThrP adthr, erAlphaP alphas)
{
                    rectOI = rect;
             param_smooth1 = smooth1;
             param_smooth2 = smooth2;
               param_canny = cann;
  param_adaptive_threshold = adthr;
         param_alpha_shape = alphas;
};


bool erCreatisAnalysis::doIt( std::string fich)
{
  erImage ea;
  bool loaded;
  char* file_name         = const_cast< char*>( fich.c_str());
  setCurrentFileName(file_name);
  boost::tie(ea, loaded) = erLoadImage( file_name);
  if( !loaded) return false;
  return doItImage(ea);
};
bool erCreatisAnalysis::doItImage(erImage& ea)
{
  erImage eb, ec;
  std::list< CvPoint>   cvPts;
  std::list< CgalPoint> cgalPts;
  std::list< CgalSegmt> cgalSeg;
  BgraphSegmtMap  connectedSegments; 
  erEqualP pequ;
 
  output_name = (dir_analysis+"/"+name+"_creatis");
  
 
 
  eb = erConvertToBlackAndWhite( &ea);
  if(outputIntermediateImages())
    {
      char* nomb= const_cast< char*>( (output_name+"_1_blackWhite").c_str());
      erSaveImage( &eb, file_name, nomb);
    };
  ec = erDef_ROI( &eb, &rectOI);
 
  erCvSmooth( &ec, &param_smooth1);
  if(outputIntermediateImages())
    {
      char* nomc= const_cast< char*>( (output_name+"_2_smooth").c_str());
      erSaveImage( &ec, file_name, nomc);
    };
  erCvAdaptiveThreshold( &ec, &param_adaptive_threshold);
  if(outputIntermediateImages())
    {
      char* nomd= const_cast< char*>( (output_name+"_3_adaptive").c_str());
      erSaveImage( &ec, file_name, nomd);
    };
  erCvSmooth( &ec, &param_smooth2);
  if(outputIntermediateImages())
    {
      char* nome= const_cast< char*>( (output_name+"_4_smooth").c_str());
      erSaveImage( &ec, file_name, nome);
    };
  erCvCanny( &ec, &param_canny);
  if(outputIntermediateImages())
    {
      char* nomf= const_cast< char*>( (output_name+"_5_canny").c_str());
      erSaveImage( &ec, file_name, nomf);
    };

  IsEqualTo is_equal_255( 255);
  erExtractCvPoints( cvPts, &ec, is_equal_255, rectOI);
  
  convertCvToCgalpoints( cvPts, cgalPts);

  erAlphaEdges( cgalPts, cgalSeg, &param_alpha_shape);

  
  erConnectedSegments( cgalSeg, connectedSegments);
  
  //erPrintCgalPoint( bgraphSeg,currentFileName(), nom);
  //writeOutGeometry(bgraphSeg);
 
 

  return true;
};


/* Analysis pour la goutelette de metal de tranfer*/
/********************************************************************

                      SOLIDIFICATION_ANALYSIS

*********************************************************************/
erSolidificationAnalysis::erSolidificationAnalysis(){ };

erSolidificationAnalysis::erSolidificationAnalysis( std::string name, std::string infofile):
  erAnalysis( name, infofile), rectOI( ), param_smooth1( ), param_canny( ), 
  param_threshold( ), param_alpha_shape()
{ }; 





void erSolidificationAnalysis::defineParameters( CvRect rect, erSmootP smooth1, erCannyP cann, erThresP adthr, erAlphaP alphas)
{
                    rectOI = rect;
             param_smooth1 = smooth1;
               param_canny = cann;
           param_threshold = adthr;
         param_alpha_shape = alphas;
};



bool erSolidificationAnalysis::doIt( std::string fich)
{
  erImage ea;
  bool loaded;
  char* file_name         = const_cast< char*>( fich.c_str());
  setCurrentFileName(file_name);
  boost::tie(ea, loaded) = erLoadImage( file_name);
  if( !loaded) return false;
  doItImage(ea);
};

bool erSolidificationAnalysis::doItImage(erImage& ea)
{
  erImage eb, ec;
  std::list< CvPoint>   cvPts;
  std::list< CgalPoint> cgalPts;
  std::list< CgalSegmt> cgalSeg, bgraphSeg;
  erEqualP pequ;
 
  output_name = (dir_analysis+"/"+name+"_mtl");
  char* nom = const_cast< char*>( output_name.c_str());
  
  erSaveImage( &ea,currentFileName(), nom);

  eb = erConvertToBlackAndWhite( &ea);

  ec = erDef_ROI( &eb, &rectOI);
 
  erCvSmooth( &ec, &param_smooth1);
  if(outputIntermediateImages())
    {
      char* nomc= const_cast< char*>( (output_name+"_1_smooth").c_str());
      erSaveImage( &ec, file_name, nomc);
    };
 
  erCvThreshold( &ec, &param_threshold);
 if(outputIntermediateImages())
    {
      char* nomc= const_cast< char*>( (output_name+"_2_threshold").c_str());
      erSaveImage( &ec, file_name, nomc);
    };
  
  erCvCanny( &ec, &param_canny);
 if(outputIntermediateImages())
    {
      char* nomc= const_cast< char*>( (output_name+"_3_canny").c_str());
      erSaveImage( &ec, file_name, nomc);
    };
  
  IsEqualTo is_equal_255( 255);
  erExtractCvPoints( cvPts, &ec, is_equal_255, rectOI);
 
  convertCvToCgalpoints( cvPts, cgalPts);

  erAlphaEdges( cgalPts, cgalSeg, &param_alpha_shape);


    
  erLargestClosedPolygon( cgalSeg, bgraphSeg);
  
  erPrintCgalPoint( bgraphSeg,currentFileName(), nom);
  writeOutGeometry(bgraphSeg); 

  return true;
};


/********************************************************************

                      WELD_POOL_ANALYSIS

*********************************************************************/
/* Constructeur par defaut */
erWeldPoolAnalysis::erWeldPoolAnalysis(){};

//** Constructeur avec des paramettres determines ailleurs */
erWeldPoolAnalysis::erWeldPoolAnalysis( std::string name, std::string infofile): 
  erAnalysis( name, infofile), rectOI( ), param_white_blob( ), param_smooth1( ), param_smooth2( ), param_dilate( ), param_canny( ), param_threshold( ), param_template( ), param_alpha_shape( ){setOutputConvex(true);setWhiteBlobDetection(true); }; 
bool erWeldPoolAnalysis::whiteBlobDetection()
{return white_blob_detection;};
void erWeldPoolAnalysis::setWhiteBlobDetection(bool ii)
{
  white_blob_detection = ii;
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



bool erWeldPoolAnalysis::doIt(std::string fich)
{ 
  bool loaded;
  char* file_name         = const_cast< char*>( fich.c_str());
  std::cout << "Nom du fichier:" << file_name << std::endl;
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
  
  output_name = dir_analysis+"/"+name+"_wep";
  char* nom = const_cast< char*>( output_name.c_str());

  eb = erConvertToBlackAndWhite( &ea); 
  if (whiteBlobDetection()){
    erWhiteBlobCorrection( &eb, &param_white_blob);};

  /** Jusque la */
  if( _with_calibration)
    {
      ec = _calibration.transform_image(eb);
      if(outputIntermediateImages())
	{
	  std::string calib_name = dir_analysis+"/"+name+"_calib";
	  char* nomcalib = const_cast< char*>( calib_name.c_str());
	  erSaveImage(&ec,file_name, nomcalib);
	}
  
    }
  else
    {
      ec = eb;
    };
  
  ed = erDef_ROI( &ec, &rectOI);
  erCvSmooth( &ed, &param_smooth1);
 if(outputIntermediateImages())
    {
      char* nomc= const_cast< char*>( (output_name+"_1_smooth").c_str());
      erSaveImage( &ed, file_name, nomc);
    };
 //erCvCanny( &ed, &param_canny);
  
  
   erCvDilate( &ed, &param_dilate);
   if(outputIntermediateImages())
    {
      char* nomc= const_cast< char*>( (output_name+"_2_dilate").c_str());
      erSaveImage( &ed, file_name, nomc);
    };
   erCvSmooth( &ed, &param_smooth2); 
   if(outputIntermediateImages())
    {
      char* nomc= const_cast< char*>( (output_name+"_3_smooth").c_str());
      erSaveImage( &ed, file_name, nomc);
    };
  
   
  ee = erCvTemplate( &ed, &param_template);
   if(outputIntermediateImages())
    {
      
      char* nomc= const_cast< char*>( (output_name+"_4_template").c_str());
      
      erSaveImage( &ee, file_name, nomc);
    };
  erCvThreshold( &ee, &param_threshold);
  
  if(outputIntermediateImages())
    {
      char* nomt= const_cast< char*>( (output_name+"_5_threshold").c_str());
      erSaveImage( &ee, file_name, nomt);
    }
  erCvCanny( &ee, &param_canny);
  if(outputIntermediateImages())
    {
      char* nomca= const_cast< char*>( (output_name+"_6_canny").c_str());
      erSaveImage( &ee, file_name, nomca);
    };
  IsEqualTo is_equal_255(255);

  erExtractCvPoints( cvPts, &ee, is_equal_255, rectOI);
  //char * nomc;

  convertCvToCgalpoints( cvPts, cgalPts);  
  
  erAlphaEdges( cgalPts, cgalSeg, &param_alpha_shape);
  erPrintCgalPoint(cgalSeg,file_name,nom);
 
  erLargestClosedPolygon( cgalSeg, bgraphSeg);
  
  char * nomcg = const_cast< char*>( (output_name + "_extrac").c_str());
  erPrintCgalPoint( bgraphSeg, file_name, nomcg);
  erConvexHull( bgraphSeg, cgalPts2);
  double area;
  double area_axi;

  if(outputConvex())
  {
      std::list<CgalPoint> polygon = erGeometryExtractConvexPolygon(bgraphSeg.begin(),bgraphSeg.end());
      std::string output_nam = (dir_analysis+"/"+name+"_wep_poly");
      char* name = const_cast< char*>( output_nam.c_str());
      erPrintCgalPoint(polygon,currentFileName(),name);
     
    };
  writeOutGeometry(bgraphSeg);
 
  return true;
 
};




/********************************************************************

                      LASER_ANALYSIS

*********************************************************************/


/* Constructeur par defaut */
erLaserPrototypageAnalysis::erLaserPrototypageAnalysis(){};

//** Constructeur avec des paramettres determines ailleurs */
erLaserPrototypageAnalysis::erLaserPrototypageAnalysis( std::string name, std::string infofile): 
  erAnalysis( name, infofile), rectOI( ), param_smooth1( ), param_smooth2( ), param_canny( ),  param_dilate( ), param_threshold( ), param_adaptive_threshold( ), param_template( ), param_alpha_shape( ){ }; 


void erLaserPrototypageAnalysis::defineParameters_diffuse( CvRect rect, erSmootP smooth, erCannyP canny, erAdThrP adthr, erAlphaP alphas)
{
  rectOI = rect;
  param_smooth1 = smooth;
  param_canny = canny;
  param_adaptive_threshold = adthr;
  param_alpha_shape = alphas;
};


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




bool erLaserPrototypageAnalysis::doIt_diffuse(std::string fich)
{ 
  bool loaded;
  char* file_name         = const_cast< char*>( fich.c_str());
  setCurrentFileName(file_name);
  output_name = (dir_analysis+"/"+name+"_wep");
  char* nom = const_cast< char*>( output_name.c_str());
  erImage ea, eb, ec, ed, ee;
  std::list< CvPoint>   cvPts;
  std::list< CgalPoint> cgalPts;
  SegmentList cgalSeg, bgraphSeg;
  
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
 
  erAlphaEdges( cgalPts, cgalSeg, &param_alpha_shape);
 
  erLargestClosedPolygon( cgalSeg, bgraphSeg);
 
  erPrintCgalPoint( bgraphSeg,currentFileName(), nom);
 
  if(outputConvex())
  {
      std::list<CgalPoint> polygon = erGeometryExtractConvexPolygon(bgraphSeg.begin(),bgraphSeg.end());
      std::string output_nam = (dir_analysis+"/"+name+"_wep_poly");
      char* name = const_cast< char*>( output_nam.c_str());
      erPrintCgalPoint(polygon,currentFileName(),name);
    };
  writeOutGeometry(bgraphSeg);
  // if(output_geometry_characteristics && bgraphSeg.size() > 6)
  //   {
  //     std::list<CgalTrian> triangs=erGeometryExtractTriangles(bgraphSeg.begin(),bgraphSeg.end());
  //     double area   = getArea(triangs.begin(),triangs.end());
  //     CgalLine  line;
  //     CgalPoint pt;
  //     CgalFTrai fit = linear_least_squares_fitting_2(triangs.begin(),triangs.end(),line,pt,CGAL::Dimension_tag<2>());	
  //     std::ofstream ot(output_geometry_file.c_str(),std::ios_base::app);
  //     CgalVect vect=line.to_vector();
  //     ot << std::setprecision(10) << currentFileName() << "\t" << pt.x() << "\t" << pt.y() << "\t" << area << "\t" << vect.x() << "\t" << vect.y() <<"\t" << fit << std::endl;    
  //   };

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

  output_name = (dir_analysis+"/"+name+"_wep");
  char* nom = const_cast< char*>( output_name.c_str());
  erImage eb, ec, ed, ee;
  std::list< CvPoint>   cvPts;
  std::list< CgalPoint> cgalPts, cgalPts2;
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

  erAlphaEdges( cgalPts, cgalSeg, &param_alpha_shape);

  erLargestClosedPolygon( cgalSeg, bgraphSeg);

  erPrintCgalPoint( bgraphSeg,currentFileName(), nom);
 

  if(output_convex_polygon)
  {
      std::list<CgalPoint> polygon = erGeometryExtractConvexPolygon(bgraphSeg.begin(),bgraphSeg.end());
      std::string output_nam = (dir_analysis+"/"+name+"_wep_poly");
      char* name = const_cast< char*>( output_nam.c_str());
      erPrintCgalPoint(polygon,currentFileName(),name);
    };
  writeOutGeometry(bgraphSeg);
  // if(output_geometry_characteristics && bgraphSeg.size() > 6)
  //   {
  //     std::list<CgalTrian> triangs=erGeometryExtractTriangles(bgraphSeg.begin(),bgraphSeg.end());
  //     double area   = getArea(triangs.begin(),triangs.end());
  //     CgalLine  line;
  //     CgalPoint pt;
  //     CgalFTrai fit = linear_least_squares_fitting_2(triangs.begin(),triangs.end(),line,pt,CGAL::Dimension_tag<2>());	
  //     std::ofstream ot(output_geometry_file.c_str(),std::ios_base::app);
  //     CgalVect vect=line.to_vector();
  //     ot << std::setprecision(10) << currentFileName() << "\t" << pt.x() << "\t" << pt.y() << "\t" << area << "\t" << vect.x() << "\t" << vect.y() <<"\t" << fit << std::endl;    
  //   };
  return true;
};
