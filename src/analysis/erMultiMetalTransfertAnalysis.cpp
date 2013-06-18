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



#include <erCv/graph/erConnectedSegments.hpp>
#include <erCv/graph/erShortestPaths.hpp>

#include<boost/lexical_cast.hpp>
/********************************************************************


             MULTI_TRANSFERT_ANALYSIS


 *******************************************************************/

erMultiMetalTransfertAnalysis::erMultiMetalTransfertAnalysis(){ };

erMultiMetalTransfertAnalysis::erMultiMetalTransfertAnalysis( std::string name, 
							      std::string infofile):
  erAnalysis( name, infofile), 
  rectOI( ), 
  param_smooth1( ), 
  param_smooth2( ), 
  param_canny( ), 
  param_adaptive_threshold( ), 
  param_alpha_shape()
{}; 



void erMultiMetalTransfertAnalysis::defineParameters( CvRect rect, 
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
  erImage               eb, ec;
  std::list< CvPoint>   cvPts;
  std::list< CgalPoint> cgalPts;
  std::list< CgalSegmt> cgalSeg;
  BgraphSegmtMap        connectedSegments; 
  erEqualP              pequ;
 
  output_name = dir_analysis+"/"+name+"_mult_mtl";
 
  eb = erConvertToBlackAndWhite( &ea);

  if(outputIntermediateImages())
    {
      char* nomb= const_cast<char*>( (output_name+"_1").c_str());
      erSaveImage( &eb, file_name, nomb);
    };

  ec = erDef_ROI( &eb, &rectOI);
 
  erCvSmooth( &ec, &param_smooth1);

  if(outputIntermediateImages())
    {
    
      char* nomc= const_cast< char*>( (output_name+"_2").c_str());
      erSaveImage( &ec, file_name, nomc);
    };

  erCvAdaptiveThreshold( &ec, &param_adaptive_threshold);

  if(outputIntermediateImages())
    {
     
      char* nomd= const_cast< char*>( (output_name+"_3").c_str());
      erSaveImage( &ec, file_name, nomd);

    };

  erCvSmooth( &ec, &param_smooth2);

  if(outputIntermediateImages())
    {
    
      char* nome= const_cast< char*>( (output_name+"_4").c_str());
      
      erSaveImage( &ec, file_name, nome);
    };

  erCvCanny( &ec, &param_canny);

  if(outputIntermediateImages())
    {
     
      char* nomf= const_cast< char*>( (output_name+"_5").c_str());
      
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
    { 
      std::string num=boost::lexical_cast<std::string>(idf);
      std::string fich=output_name+"_"+num;
      Graph localgraph;
      PointVertexMap ptvmap;
      char* fileOut = const_cast< char*>(fich.c_str());
      //boost::tie(localgraph,ptvmap) = constructGraphFromSegments(dede->second.begin(),dede->second.end());
      //std::cout << "nbre segments:" << dede->second.size() << " ";
      //std::list<CgalPoint> contour  = erLinkedListOfVertex(localgraph);
      //std::cout << "nbre de points:" << contour.size() << std::endl;
      erPrintCgalPoint(dede->second,currentFileName(), fileOut);
      writeOutGeometry(dede->second,fich);
      idf+=1;
    } 

  return true;
};
