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
       if(outputIntermediateImages())
	 {
	   char* nomc= const_cast< char*>( (output_name+"_1_adp").c_str());
	   erSaveImage( &ec, file_name, nomc);
	 };
       erCvSmooth( &ec, &param_smooth2);
       
       erCvCanny( &ec, &param_canny);
         if(outputIntermediateImages())
	 {
	   char* nomc= const_cast< char*>( (output_name+"_2_can").c_str());
	   erSaveImage( &ec, file_name, nomc);
	 };
	 //erSaveImage( &ec, currentFileName(), nom);
       IsEqualTo is_equal_255( 255); 
       erExtractCvPoints( cv_pts, &ec, is_equal_255, rectOI);
       convertCvToCgalpoints( cv_pts, cgal_pts);

       erAlphaEdges( cgal_pts, cgalSeg, &param_alpha_shape);
      
       cgal_wire_pts = erGetShortestPath(cgalSeg.begin(),cgalSeg.end(),cerc_to_start,cerc_to_end);
      
  
       erPrintCgalPoint( cgal_wire_pts,currentFileName(), nom);

             
       return true;
};
