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
#include "boost/python.hpp"
#include "pyublas/numpy.hpp"
#include "erCv/erCvAnalysis.hpp"
#include <erCv/erCvFilters.hpp>
#include <erCv/erCvSegmentation.hpp>
#include <erCv/utilities/erPredicates.hpp>
#include <erCv/erCvExtract.hpp>
#include <erCv/erCvToCgal.hpp>

#include <erCv/geometry/erCgalConvexPolygone.hpp>

#include <erCv/graph/erConnectedSegments.hpp>
#include <erCv/graph/erShortestPaths.hpp>
#include <erCv/bindings/python/erNumpyTools.hpp>

namespace bp = boost::python;

//-----------------------------------------------------------------------
//
//    ER_WELD_ANALYSIS_SOLIDIFICATION_WRAPPER
//
//-----------------------------------------------------------------------

struct erWeldPoolSolidificationAnalysis_wrapper : erWeldPoolSolidificationAnalysis, bp::wrapper< erWeldPoolSolidificationAnalysis > {
  
  erWeldPoolSolidificationAnalysis_wrapper(erWeldPoolSolidificationAnalysis const & arg )
    : erWeldPoolSolidificationAnalysis( arg )
    , bp::wrapper< erWeldPoolSolidificationAnalysis >(){
    // copy constructor
    
  }
  
  erWeldPoolSolidificationAnalysis_wrapper( )
    : erWeldPoolSolidificationAnalysis( )
    , bp::wrapper< erWeldPoolSolidificationAnalysis >(){
    // null constructor
    
  }
  
  erWeldPoolSolidificationAnalysis_wrapper(std::string name,std::string infofile="info" )
    : erWeldPoolSolidificationAnalysis( name, infofile )
    , bp::wrapper< erWeldPoolSolidificationAnalysis >(){
    // constructor
    
  }
  
  virtual bool doIt(std::string arg0 ) {
    if( bp::override func_doIt = this->get_override( "doIt" ) )
      return func_doIt( arg0 );
    else
      return this->erWeldPoolSolidificationAnalysis::doIt( arg0 );
  }
  
  
  bool default_doIt(std::string arg0 ) {
    return erWeldPoolSolidificationAnalysis::doIt( arg0 );
  }
  bool doItNumPy(pyublas::numpy_array<unsigned short>& arr,std::string file_name="test_1.bmp")
  {

    char*  file_c   =   const_cast<char*>(file_name.c_str());
    setCurrentFileName(file_c);

    erImage eim = erConvertNumpyArray16ToImage(arr);
    erWeldPoolSolidificationAnalysis::doItImage(eim);

    return true;
  }
  bp::list getSegments(pyublas::numpy_array<unsigned short>& arr,std::string file_name="test_1.bmp")
  {

    char*  file_c   =   const_cast<char*>(file_name.c_str());
    setCurrentFileName(file_c);


    erImage ea = erConvertNumpyArray16ToImage(arr);
    erImage  eb, ec, ed, ee;
    std::list< CvPoint>   cvPts;
    std::list< CgalPoint> cgalPts, cgalPts2;
    std::list< CgalSegmt> cgalSeg, bgraphSeg;


    eb = erConvertToBlackAndWhite( &ea); 
 
    /** Jusque la */
    if( _with_calibration)
    {
      ec = _calibration.transform_image(eb);
      if(outputIntermediateImages())
	{
	  std::string calib_name = dir_analysis+"/"+name+"_calib";
	  char* nomcalib = const_cast< char*>( calib_name.c_str());
	  erSaveImage(&ec,file_c, nomcalib);
	}
  
    }
    else
    {
      ec = eb;
    };
  
    ed = erDef_ROI( &ec, &rectOI);
   
    ee = erCvTemplate( &ed, &param_template);
    if(outputIntermediateImages())
    {
      
      char* nomc= const_cast< char*>( (output_name+"_4_template").c_str());
      
      erSaveImage( &ee, file_c, nomc);
    };
    erCvThreshold( &ee, &param_threshold);
  
    if(outputIntermediateImages())
    {
      char* nomt= const_cast< char*>( (output_name+"_5_threshold").c_str());
      erSaveImage( &ee, file_c, nomt);
    }
    erCvCanny( &ee, &param_canny);
    if(outputIntermediateImages())
    {
      char* nomca= const_cast< char*>( (output_name+"_6_canny").c_str());
      erSaveImage( &ee, file_c, nomca);
    };
    IsEqualTo is_equal_255(255);

    erExtractCvPoints( cvPts, &ee, is_equal_255, rectOI);
    //char * nomc;

    convertCvToCgalpoints( cvPts, cgalPts);  
  
     erAlphaEdges( cgalPts, cgalSeg, &param_alpha_shape);
     BgraphSegmtMap  connectedSegments = getConnectedSegments( cgalSeg.begin(), cgalSeg.end());
     bp::list output;
     BgraphSegmtMap::iterator debut,fin;
     fin= connectedSegments.end();
     for(debut=connectedSegments.begin();debut!=fin;debut++)
     {
       BgraphSegmt          sgs = debut->second;
       BgraphSegmt::iterator ds,fs;
       ds=sgs.begin();
       fs=sgs.end();
       bp::list conn_seg;
       for(;ds!=fs;ds++)
	 {
	   CgalPoint src = ds->source();
	   CgalPoint tar = ds->target();
	   bp::list  psrc,ptar;
	   psrc.append(src.x());psrc.append(src.y());
	   ptar.append(tar.x());ptar.append(tar.y());
	   bp::list seg;
	   seg.append(psrc);seg.append(ptar);
	   conn_seg.append(seg);
	 };
       output.append(conn_seg);
     }
     return output;

  };
}; 
 

  //-----------------------------------------------------------------------------------------------------------
  //
  // 
  // Python ::::   ER_WELD_POOL_SOLIDIFICATION_ANALYSIS
  //
  //
  //-----------------------------------------------------------------------------------------------------------  
void export_erWeldPoolSolidificationAnalysis()
{  
  bp::class_< erWeldPoolSolidificationAnalysis_wrapper, bp::bases< erAnalysis > >( "erWeldPoolSolidificationAnalysis", bp::init< >() )    
    .def( bp::init< std::string, bp::optional< std::string > >(( bp::arg("name"), bp::arg("infofile")="info" )) )    
    .def( 
	 "defineParameters"
	 , (void ( ::erWeldPoolSolidificationAnalysis::* )( ::CvRect, ::erSmootP,::erCannyP,::erThresP,::erTemplP,::erAlphaP ) )( &::erWeldPoolSolidificationAnalysis::defineParameters )
	 , ( bp::arg("arg0"), bp::arg("arg1"), bp::arg("arg2"), bp::arg("arg3"), bp::arg("arg4"), bp::arg("arg5") ) )    
  
    .def( 
	 "doIt"
	 , (bool ( ::erWeldPoolSolidificationAnalysis::* )( std::string ) )(&::erWeldPoolSolidificationAnalysis::doIt)
	 , (bool ( erWeldPoolSolidificationAnalysis_wrapper::* )( std::string ) )(&erWeldPoolSolidificationAnalysis_wrapper::default_doIt)
	 , ( bp::arg("arg0") ) )    
    .def(
	 "doItNumPy"
	 ,  (bool ( ::erWeldPoolSolidificationAnalysis_wrapper::* )(boost::python::numeric::array& ,std::string ) )(&::erWeldPoolSolidificationAnalysis_wrapper::doItNumPy))
  
   .def(
	 "getSegments"
	 ,  (bp::list ( ::erWeldPoolSolidificationAnalysis_wrapper::* )(boost::python::numeric::array& ,std::string ) )(&::erWeldPoolSolidificationAnalysis_wrapper::getSegments))
    //        .def_readwrite( "param_adaptive_threshold", &erWeldPoolAnalysis::param_adaptive_threshold )    
    .def_readwrite( "param_alpha_shape" , &erWeldPoolSolidificationAnalysis::param_alpha_shape )    
    .def_readwrite( "param_canny"       , &erWeldPoolSolidificationAnalysis::param_canny )    

    .def_readwrite( "param_smooth1"     , &erWeldPoolSolidificationAnalysis::param_smooth1 )    
     
    .def_readwrite( "param_template"    , &erWeldPoolSolidificationAnalysis::param_template )  
    .def_readwrite( "param_threshold"   , &erWeldPoolSolidificationAnalysis::param_threshold)
    .def_readwrite( "rectOI"            , &erWeldPoolSolidificationAnalysis::rectOI );
};
