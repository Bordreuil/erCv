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
//    ER_MULTI_METAL_ANALYSIS_WRAPPER
//
//-----------------------------------------------------------------------


struct erMultiMetalTransfertAnalysis_wrapper : erMultiMetalTransfertAnalysis, bp::wrapper< erMultiMetalTransfertAnalysis > {
  
  erMultiMetalTransfertAnalysis_wrapper(erMultiMetalTransfertAnalysis const & arg )
    : erMultiMetalTransfertAnalysis( arg )
    , bp::wrapper< erMultiMetalTransfertAnalysis >(){
    // copy constructor
    
  }
  
  erMultiMetalTransfertAnalysis_wrapper( )
    : erMultiMetalTransfertAnalysis( )
    , bp::wrapper< erMultiMetalTransfertAnalysis >(){
    // null constructor
    
  }
  
  erMultiMetalTransfertAnalysis_wrapper(std::string name, std::string infofile="info" )
    : erMultiMetalTransfertAnalysis( name, infofile )
    , bp::wrapper< erMultiMetalTransfertAnalysis >(){
    // constructor
    
  };
  
  virtual bool doIt( std::string arg0 ) {
    if( bp::override func_doIt = this->get_override( "doIt" ) )
      return func_doIt( arg0 );
    else
      return this->erMultiMetalTransfertAnalysis::doIt( arg0 );
  }
  virtual bool doItImage( erImage& arg0 ) {
    if( bp::override func_doItImage = this->get_override( "doItImage" ) )
      return func_doItImage( arg0 );
    else
      return this->erMultiMetalTransfertAnalysis::doItImage( arg0 );
  }
  
  bool default_doIt( std::string arg0 ) {
    return erMultiMetalTransfertAnalysis::doIt( arg0 );
  };

  bool doItNumPy(pyublas::numpy_array<unsigned short>& arr,std::string file_name="test_1.bmp")
  {

    char*  file_c   =   const_cast<char*>(file_name.c_str());
    setCurrentFileName(file_c);
    erImage eim = erConvertNumpyArray16ToImage(arr);
  
   
    erMultiMetalTransfertAnalysis::doItImage(eim);

    return true;
  }
};
 //-----------------------------------------------------------------------------------------------------------
  //
  // 
  // Python ::::   ER_MULTI_TRANSFERT_ANALYSIS
  //
  //
  //-----------------------------------------------------------------------------------------------------------  

void export_erMultiMetalTransfertAnalysis()
{
  bp::class_< erMultiMetalTransfertAnalysis_wrapper, bp::bases< erAnalysis > >( "erMultiMetalTransfertAnalysis", bp::init< >() )    
    .def( bp::init< std::string, bp::optional< std::string > >(( bp::arg("name"), bp::arg("infofile")="info" )) )    
    
    .def( 
	 "defineParameters"
	 , (void ( ::erMultiMetalTransfertAnalysis::* )( ::CvRect,::erSmootP,::erSmootP,::erCannyP,::erAdThrP,::erAlphaP ) )( &::erMultiMetalTransfertAnalysis::defineParameters )
	 , ( bp::arg("arg0"), bp::arg("arg1"), bp::arg("arg2"), bp::arg("arg3"), bp::arg("arg4"), bp::arg("arg5") ) )  
    
   
    .def( 
	 "doIt"
	 , (bool ( ::erMultiMetalTransfertAnalysis::* )( std::string ) )(&::erMultiMetalTransfertAnalysis::doIt)
	 , (bool ( erMultiMetalTransfertAnalysis_wrapper::* )( std::string ) )(&erMultiMetalTransfertAnalysis_wrapper::default_doIt)
	 , ( bp::arg("arg0") ) )
    .def(
	 "doItNumPy"
	 ,  (bool ( ::erMultiMetalTransfertAnalysis_wrapper::* )(boost::python::numeric::array& ,std::string ) )(&::erMultiMetalTransfertAnalysis_wrapper::doItNumPy))
  
   
    .def_readwrite( "param_adaptive_threshold", &erMultiMetalTransfertAnalysis::param_adaptive_threshold )    
    .def_readwrite( "param_alpha_shape",        &erMultiMetalTransfertAnalysis::param_alpha_shape )    
    .def_readwrite( "param_canny",              &erMultiMetalTransfertAnalysis::param_canny )    
    .def_readwrite( "param_smooth1",            &erMultiMetalTransfertAnalysis::param_smooth1 )    
    .def_readwrite( "param_smooth2",            &erMultiMetalTransfertAnalysis::param_smooth2 )    
    .def_readwrite( "rectOI",                   &erMultiMetalTransfertAnalysis::rectOI );
};
