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
//    ER_METAL_ANALYSIS_WRAPPER
//
//-----------------------------------------------------------------------


struct erMetalTransfertAnalysis_wrapper : erMetalTransfertAnalysis, bp::wrapper< erMetalTransfertAnalysis > {
  
  erMetalTransfertAnalysis_wrapper(erMetalTransfertAnalysis const & arg )
    : erMetalTransfertAnalysis( arg )
    , bp::wrapper< erMetalTransfertAnalysis >(){
    // copy constructor
    
  }
  
  erMetalTransfertAnalysis_wrapper( )
    : erMetalTransfertAnalysis( )
    , bp::wrapper< erMetalTransfertAnalysis >(){
    // null constructor
    
  }
  
  erMetalTransfertAnalysis_wrapper(std::string name, std::string infofile="info" )
    : erMetalTransfertAnalysis( name, infofile )
    , bp::wrapper< erMetalTransfertAnalysis >(){
    // constructor
    
  };
  
  virtual bool doIt( std::string arg0 ) {
    if( bp::override func_doIt = this->get_override( "doIt" ) )
      return func_doIt( arg0 );
    else
      return this->erMetalTransfertAnalysis::doIt( arg0 );
  }
  virtual bool doItImage( erImage& arg0 ) {
    if( bp::override func_doItImage = this->get_override( "doItImage" ) )
      return func_doItImage( arg0 );
    else
      return this->erMetalTransfertAnalysis::doItImage( arg0 );
  }
  
  bool default_doIt( std::string arg0 ) {
    return erMetalTransfertAnalysis::doIt( arg0 );
  };

  bool doItNumPy(pyublas::numpy_array<unsigned short>& arr,std::string file_name="test_1.bmp")
  {
    
    erImage eim = erConvertNumpyArray16ToImage(arr);
    char*  file_c   =   const_cast<char*>(file_name.c_str());
    setCurrentFileName(file_c);
    //erImage eim(im);
    erMetalTransfertAnalysis::doItImage(eim);

    return true;
  }
};

void export_erMetalTransfertAnalysis()
{
//-----------------------------------------------------------------------------------------------------------
  //
  // 
  // Python ::::   ER_METAL_TRANSFERT_ANALYSIS
  //
  //
  //-----------------------------------------------------------------------------------------------------------  

  
  bp::class_< erMetalTransfertAnalysis_wrapper, bp::bases< erAnalysis > >( "erMetalTransfertAnalysis", bp::init< >() )    
    .def( bp::init< std::string, bp::optional< std::string > >(( bp::arg("name"), bp::arg("infofile")="info" )) )    
    
    .def( 
	 "defineParameters"
	 , (void ( ::erMetalTransfertAnalysis::* )( ::CvRect,::erSmootP,::erSmootP,::erCannyP,::erAdThrP,::erAlphaP ) )( &::erMetalTransfertAnalysis::defineParameters )
	 , ( bp::arg("arg0"), bp::arg("arg1"), bp::arg("arg2"), bp::arg("arg3"), bp::arg("arg4"), bp::arg("arg5") ) )  
    
   
    .def( 
	 "doIt"
	 , (bool ( ::erMetalTransfertAnalysis::* )( std::string ) )(&::erMetalTransfertAnalysis::doIt)
	 , (bool ( erMetalTransfertAnalysis_wrapper::* )( std::string ) )(&erMetalTransfertAnalysis_wrapper::default_doIt)
	 , ( bp::arg("arg0") ) )
    .def(
	 "doItNumPy"
	 ,  (bool ( ::erMetalTransfertAnalysis_wrapper::* )(boost::python::numeric::array& ,std::string ) )(&::erMetalTransfertAnalysis_wrapper::doItNumPy))
  
   
    .def_readwrite( "param_adaptive_threshold", &erMetalTransfertAnalysis::param_adaptive_threshold )    
    .def_readwrite( "param_alpha_shape",        &erMetalTransfertAnalysis::param_alpha_shape )    
    .def_readwrite( "param_canny",              &erMetalTransfertAnalysis::param_canny )    
    .def_readwrite( "param_smooth1",            &erMetalTransfertAnalysis::param_smooth1 )    
    .def_readwrite( "param_smooth2",            &erMetalTransfertAnalysis::param_smooth2 )    
    .def_readwrite( "rectOI",                   &erMetalTransfertAnalysis::rectOI );
};
