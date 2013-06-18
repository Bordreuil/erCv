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

#include <erCv/geometry/erCgalConvexPolygone.hpp>

#include <erCv/graph/erConnectedSegments.hpp>
#include <erCv/graph/erShortestPaths.hpp>

#include<boost/lexical_cast.hpp>


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

