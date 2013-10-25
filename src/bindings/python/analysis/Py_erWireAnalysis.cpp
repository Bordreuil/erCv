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
//    ER_WIRE_ANALYSIS_WRAPPER
//
//-----------------------------------------------------------------------

struct erWireAnalysis_wrapper : erWireAnalysis, bp::wrapper< erWireAnalysis > {

    erWireAnalysis_wrapper(erWireAnalysis const & arg )
    : erWireAnalysis( arg )
      , bp::wrapper< erWireAnalysis >(){
        // copy constructor
        
    }

  erWireAnalysis_wrapper(std::string name, std::string infofile="info" )
    : erWireAnalysis( name, infofile )
      , bp::wrapper< erWireAnalysis >(){
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
 bool doItNumPy(pyublas::numpy_array<unsigned short>& arr,std::string file_name="test_1.bmp")
  {
    char*  file_c   =   const_cast<char*>(file_name.c_str());
    setCurrentFileName(file_c);
    erImage eim = erConvertNumpyArray16ToImage(arr);
    erWireAnalysis::doItImage(eim);

    return true;
  }
};

  //-----------------------------------------------------------------------------------------------------------
  //
  // 
  // Python ::::   ER_WIRE_ANALYSIS
  //
  //
  //-----------------------------------------------------------------------------------------------------------  
void export_erWireAnalysis()
{
  bp::class_< erWireAnalysis_wrapper, bp::bases< erMacroDropAnalysis > >( "erWireAnalysis", bp::init< std::string, bp::optional< std::string > >(( bp::arg("name"), bp::arg("infofile")="info" )) )    
        .def( 
            "setBeginZone"
            , (void ( ::erWireAnalysis::* )( ::erCerc ) )( &::erWireAnalysis::setBeginZone )
            , ( bp::arg("arg0") ) )    
        .def( 
            "setEndZone"
            , (void ( ::erWireAnalysis::* )( ::erCerc ) )( &::erWireAnalysis::setEndZone )
            , ( bp::arg("arg0") ) )    
        .def_readwrite( "cerc_to_end", &erWireAnalysis::cerc_to_end )    
        .def_readwrite( "param_alpha_shape", &erWireAnalysis::param_alpha_shape )    
        .def(
	 "doItNumPy"
	 ,  (bool ( ::erWireAnalysis_wrapper::* )(boost::python::numeric::array& ,std::string ) )(&::erWireAnalysis_wrapper::doItNumPy))
        .def( 
            "doIt"
            , (bool ( ::erMacroDropAnalysis::* )( std::string ) )(&::erMacroDropAnalysis::doIt)
            , (bool ( erWireAnalysis_wrapper::* )( std::string) )(&erWireAnalysis_wrapper::default_doIt)
            , ( bp::arg("arg0") ) );
};
