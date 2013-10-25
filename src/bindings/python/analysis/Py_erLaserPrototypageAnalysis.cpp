
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
//    ER_LASER_PROTOTYPAGE_ANALYSIS_WRAPPER
//
//-----------------------------------------------------------------------
struct erLaserPrototypageAnalysis_wrapper : erLaserPrototypageAnalysis, bp::wrapper< erLaserPrototypageAnalysis > {

    erLaserPrototypageAnalysis_wrapper(erLaserPrototypageAnalysis const & arg )
    : erLaserPrototypageAnalysis( arg )
      , bp::wrapper< erLaserPrototypageAnalysis >(){
        // copy constructor
        
    }

    erLaserPrototypageAnalysis_wrapper( )
    : erLaserPrototypageAnalysis( )
      , bp::wrapper< erLaserPrototypageAnalysis >(){
        // null constructor
    
    }

    erLaserPrototypageAnalysis_wrapper(std::string name, std::string infofile="info" )
    : erLaserPrototypageAnalysis( name, infofile )
      , bp::wrapper< erLaserPrototypageAnalysis >(){
        // constructor
    
    }

    virtual bool doIt( std::string arg0 ) {
        if( bp::override func_doIt = this->get_override( "doIt" ) )
            return func_doIt( arg0 );
        else
            return this->erLaserPrototypageAnalysis::doIt( arg0 );
    }
    
    
    bool default_doIt( std::string arg0 ) {
        return erLaserPrototypageAnalysis::doIt( arg0 );
    }

};


  //-----------------------------------------------------------------------------------------------------------
  //
  // 
  // Python ::::   ER_LASER_PROTOTYPAGE_ANALYSIS
  //
  //
  //-----------------------------------------------------------------------------------------------------------  
  
void export_erLaserPrototypageAnalysis()
{
 bp::class_< erLaserPrototypageAnalysis_wrapper, bp::bases< erAnalysis > >( "erLaserPrototypageAnalysis", bp::init< >() )    
        .def( bp::init< std::string, bp::optional< std::string > >(( bp::arg("name"), bp::arg("infofile")="info" )) )    
        .def( 
            "defineParameters"
            , (void ( ::erLaserPrototypageAnalysis::* )( ::CvRect,::erSmootP,::erSmootP,::erCannyP,::erDilatP,::erThresP,::erTemplP,::erAlphaP ) )( &::erLaserPrototypageAnalysis::defineParameters )
            , ( bp::arg("arg0"), bp::arg("arg1"), bp::arg("arg2"), bp::arg("arg3"), bp::arg("arg4"), bp::arg("arg5"), bp::arg("arg6"), bp::arg("arg7") ) )    
       
        .def( 
            "defineParameters_diffuse"
            , (void ( ::erLaserPrototypageAnalysis::* )( ::CvRect,::erSmootP,::erCannyP,::erAdThrP,::erAlphaP ) )( &::erLaserPrototypageAnalysis::defineParameters_diffuse )
            , ( bp::arg("arg0"), bp::arg("arg1"), bp::arg("arg2"), bp::arg("arg3"), bp::arg("arg4") ) )    
        .def( 
            "doIt"
            , (bool ( ::erLaserPrototypageAnalysis::* )( std::string ) )(&::erLaserPrototypageAnalysis::doIt)
            , (bool ( erLaserPrototypageAnalysis_wrapper::* )( std::string ) )(&erLaserPrototypageAnalysis_wrapper::default_doIt)
            , ( bp::arg("arg0") ) )    
        .def( 
            "doIt_diffuse"
            , (bool ( ::erLaserPrototypageAnalysis::* )( std::string ) )( &::erLaserPrototypageAnalysis::doIt_diffuse )
            , ( bp::arg("arg0") ) )    

        .def_readwrite( "param_adaptive_threshold", &erLaserPrototypageAnalysis::param_adaptive_threshold )    
        .def_readwrite( "param_alpha_shape", &erLaserPrototypageAnalysis::param_alpha_shape )    
        .def_readwrite( "param_canny", &erLaserPrototypageAnalysis::param_canny )    
        .def_readwrite( "param_dilate", &erLaserPrototypageAnalysis::param_dilate )    
        .def_readwrite( "param_smooth1", &erLaserPrototypageAnalysis::param_smooth1 )    
        .def_readwrite( "param_smooth2", &erLaserPrototypageAnalysis::param_smooth2 )    
        .def_readwrite( "param_template", &erLaserPrototypageAnalysis::param_template )    
        .def_readwrite( "param_threshold", &erLaserPrototypageAnalysis::param_threshold )    
        .def_readwrite( "rectOI", &erLaserPrototypageAnalysis::rectOI );
};
