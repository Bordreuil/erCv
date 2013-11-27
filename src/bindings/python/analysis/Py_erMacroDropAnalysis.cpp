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
//    ER_MACRO_ANALYSIS_WRAPPER
//
//-----------------------------------------------------------------------



// Wrapper parce que erMacroDropAnalysis derive de erAnalysis et que erAnalysis
// a une methode virtuelle pure pour etre utilise dans la BAME
// Genere par py++

struct erMacroDropAnalysis_wrapper : erMacroDropAnalysis, bp::wrapper< erMacroDropAnalysis > {
  
  erMacroDropAnalysis_wrapper(erMacroDropAnalysis const & arg )
    : erMacroDropAnalysis( arg )
    , bp::wrapper< erMacroDropAnalysis >(){
    // copy constructor
    
  }
  
  erMacroDropAnalysis_wrapper( )
    : erMacroDropAnalysis( )
    , bp::wrapper< erMacroDropAnalysis >(){
    // null constructor
    
  }
  
  erMacroDropAnalysis_wrapper(std::string name, std::string infofile="info" )
    : erMacroDropAnalysis( name, infofile )
    , bp::wrapper< erMacroDropAnalysis >(){
    // constructor
    
  }
  
  virtual bool doIt( std::string arg0 ) {
    if( bp::override func_doIt = this->get_override( "doIt" ) )
      return func_doIt( arg0 );
    else
      return this->erMacroDropAnalysis::doIt( arg0 );
  }
  
  
  bool default_doIt(std::string arg0 ) {
    return erMacroDropAnalysis::doIt( arg0 );
  }
  
};
void export_erMacroDropAnalysis(){
//-----------------------------------------------------------------------------------------------------------
  //
  // 
  // Python ::::   ER_MACRO_DROP_ANALYSIS
  //
  //
  //-----------------------------------------------------------------------------------------------------------  
  bp::class_< erMacroDropAnalysis_wrapper, bp::bases< erAnalysis > >( "erMacroDropAnalysis",bp::init<>())
    .def(bp::init<std::string,bp::optional<std::string> >(( bp::arg("name"), bp::arg("infofile")="info" )))   
    
    
    .def( 
	 "defineParameters"
	 , (void ( ::erMacroDropAnalysis::* )( ::CvRect,::erCerc,::erSmootP,::erSmootP,::erCannyP,::erAdThrP ,::erEqualP) )
	 ( &::erMacroDropAnalysis::defineParameters )
	 , ( bp::arg("arg0"), bp::arg("arg1"), bp::arg("arg2"), bp::arg("arg3"), bp::arg("arg4"), bp::arg("arg5"), bp::arg("equal")=::erEqualP( 1 )) )    
    
    .def( 
	 "doIt"
	 , (bool ( ::erMacroDropAnalysis::* )( std::string) )(&::erMacroDropAnalysis::doIt)
	 , (bool ( erMacroDropAnalysis_wrapper::* )( std::string ) )(&erMacroDropAnalysis_wrapper::default_doIt)
	 , ( bp::arg("arg0") ) ,"Applique l analyse macro drop au fichier ")
    
   
    .def_readwrite( "rectOI",                  &erMacroDropAnalysis::rectOI )
    .def_readwrite( "cerc_to_start",             &erMacroDropAnalysis::cerc_to_start )
    .def_readwrite( "rectOI",                  &erMacroDropAnalysis::rectOI )
    .def_readwrite( "param_smooth1",           &erMacroDropAnalysis::param_smooth1 )
    .def_readwrite( "param_smooth2",           &erMacroDropAnalysis::param_smooth2 )
    .def_readwrite( "param_canny",             &erMacroDropAnalysis::param_canny )
    .def_readwrite( "param_adaptive_threshold",&erMacroDropAnalysis::param_adaptive_threshold )
    .def_readwrite( "param_equalizer_histogram",&erMacroDropAnalysis::param_equalizer_histogram );

};
