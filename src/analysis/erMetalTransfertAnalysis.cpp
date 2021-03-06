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

/* Analysis pour la goutelette de metal de tranfer*/
/********************************************************************

                      METAL_TRANSFERT_ANALYSIS

*********************************************************************/
erMetalTransfertAnalysis::erMetalTransfertAnalysis(){ };

erMetalTransfertAnalysis::erMetalTransfertAnalysis( std::string name, 
						    std::string infofile):
  erAnalysis( name, infofile), 
  rectOI( ), 
  param_smooth1( ), 
  param_smooth2( ), 
  param_canny( ), 
  param_adaptive_threshold( ), 
  param_alpha_shape()
{}; 



void erMetalTransfertAnalysis::defineParameters( CvRect rect, 
						 erSmootP smooth1, 
						 erSmootP smooth2, 
						 erCannyP cann, 
						 erAdThrP adthr, 
						 erAlphaP alphas)
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
  erImage               eb, ec;
  std::list< CvPoint>   cvPts;
  std::list< CgalPoint> cgalPts;
  std::list< CgalSegmt> cgalSeg, bgraphSeg;
  erEqualP              pequ;
 
  output_name = (dir_analysis+"/"+name+"_mtl");
  char* nom   = const_cast< char*>( output_name.c_str());
  
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
