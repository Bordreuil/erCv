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
//    ER_ANALYSIS_WRAPPER
//
//-----------------------------------------------------------------------



struct erAnalysis_wrapper : erAnalysis, bp::wrapper< erAnalysis > {
  
  erAnalysis_wrapper( )
    : erAnalysis( )
    , bp::wrapper< erAnalysis >(){
    // null constructor
    
  }
  
  erAnalysis_wrapper(std::string name, std::string infofile="info" )
    : erAnalysis( name, infofile )
    , bp::wrapper< erAnalysis >(){
    // constructor
    
  }
  
  virtual bool doIt(std::string arg0 ){
    bp::override func_doIt = this->get_override( "doIt" );
    return func_doIt( arg0 );
  }
  virtual bool doItImage(erImage& arg0 ){
    bp::override func_doItImage = this->get_override( "doItImage" );
    return func_doItImage( arg0 );
  }

};



//-----------------------------------------------------------------------
//
//    EXPORT_ANALYSIS
//
//-----------------------------------------------------------------------
void export_erCvAnalysis(){
 
  bp::class_< erAnalysis_wrapper, boost::noncopyable >( "erAnalysis", bp::init< >() )    
    .def( bp::init< std::string, bp::optional< std::string > >(( bp::arg("name"), 
								 bp::arg("infofile")="info"  )) )    
    .def( 
	 "create"
	 , (void ( ::erAnalysis::* )(  ) )( &::erAnalysis::create ) )    
    .def( 
	 "defineCalibration"
	 , (void ( ::erAnalysis::* )(std::string,std::string) )( &::erAnalysis::defineCalibration )
	 , ( bp::arg("arg0"), bp::arg("arg1") ) )    
    .def(
		 "setOutputGeometryFile"
		 ,(void  (::erAnalysis::*)(std::string) )( &::erAnalysis::setOutputGeometryFile)
		 ,(bp::arg("arg0") ))
    .def(
		 "setOutputAxisymmetricGeometry"
		 ,(void  (::erAnalysis::*)(bool) )( &::erAnalysis::setOutputAxisymmetricGeometry)
		 ,(bp::arg("arg0") ))
    .def(
		 "setOutputIntermediateImages"
		 ,(void  (::erAnalysis::*)(bool) )( &::erAnalysis::setOutputIntermediateImages)
		 ,(bp::arg("arg0") ))	    
   
    .def( 
	 "doIt"
	 , bp::pure_virtual( (bool ( ::erAnalysis::* )( std::string ) )(&::erAnalysis::doIt) )
	 , ( bp::arg("arg0") ) )
   .def_readwrite( "dir_analysis",                  &erAnalysis::dir_analysis )
   .def_readwrite( "name",                  &erAnalysis::name)
   .def_readwrite( "output_name",                  &erAnalysis::output_name);
 
};
