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



struct erCreatisAnalysis_wrapper : erCreatisAnalysis, bp::wrapper< erCreatisAnalysis > {
  
  erCreatisAnalysis_wrapper(erCreatisAnalysis const & arg )
    : erCreatisAnalysis( arg )
    , bp::wrapper< erCreatisAnalysis >(){
    // copy constructor
    
  }
  
  erCreatisAnalysis_wrapper( )
    : erCreatisAnalysis( )
    , bp::wrapper< erCreatisAnalysis >(){
    // null constructor
    
  }
  
  erCreatisAnalysis_wrapper(std::string name, std::string infofile="info" )
    : erCreatisAnalysis( name, infofile )
    , bp::wrapper< erCreatisAnalysis >(){
    // constructor
    
  };
  
  virtual bool doIt( std::string arg0 ) {
    if( bp::override func_doIt = this->get_override( "doIt" ) )
      return func_doIt( arg0 );
    else
      return this->erCreatisAnalysis::doIt( arg0 );
  }
  virtual bool doItImage( erImage& arg0 ) {
    if( bp::override func_doItImage = this->get_override( "doItImage" ) )
      return func_doItImage( arg0 );
    else
      return this->erCreatisAnalysis::doItImage( arg0 );
  }
  
  bool default_doIt( std::string arg0 ) {
    return erCreatisAnalysis::doIt( arg0 );
  };

  bool doItNumPy(pyublas::numpy_array<unsigned short>& arr,std::string file_name="test_1.bmp")
  {
    // const npy_intp* dims = arr.dims();
    // int ncol = dims[0];
    // int nlig = dims[1];
    // //std::cout << ncol << " " << nlig << std::endl;
    // unsigned short* storage = arr.data();
    // char*  file_c   =   const_cast<char*>(file_name.c_str());
    // setCurrentFileName(file_c);
    
    // IplImage* im = cvCreateImage(cvSize(nlig,ncol),IPL_DEPTH_8U,3);
    // for(int i=0;i<ncol;i++)
    //    {
    // 	  for(int j=0;j < nlig;j++)
    // 	  { 

    // 	    unsigned short va = storage[j+i*nlig];
    // 	    //std::cout << va << " ";
    // 	    CvScalar val      = cvScalarAll(va);
    // 	    cvSet2D(im,i,j,val);
    // 	  };

    //   }; 
    // //std::cout << std::endl;

    // erImage eim(im);
    char*  file_c   =   const_cast<char*>(file_name.c_str());
    setCurrentFileName(file_c);
    erImage eim = erConvertNumpyArray16ToImage(arr);
    erCreatisAnalysis::doItImage(eim);

    return true;
  }
};

void export_erCreatisAnalysis()
{  
  bp::class_< erCreatisAnalysis_wrapper, bp::bases< erAnalysis > >( "erCreatisAnalysis", bp::init< >() )    
    .def( bp::init< std::string, bp::optional< std::string > >(( bp::arg("name"), bp::arg("infofile")="info" )) )    
    
    .def( 
	 "defineParameters"
	 , (void ( ::erCreatisAnalysis::* )( ::CvRect,::erSmootP,::erSmootP,::erCannyP,::erAdThrP,::erAlphaP ) )( &::erCreatisAnalysis::defineParameters )
	 , ( bp::arg("arg0"), bp::arg("arg1"), bp::arg("arg2"), bp::arg("arg3"), bp::arg("arg4"), bp::arg("arg5") ) )  
    
   
    .def( 
	 "doIt"
	 , (bool ( ::erCreatisAnalysis::* )( std::string ) )(&::erCreatisAnalysis::doIt)
	 , (bool ( erCreatisAnalysis_wrapper::* )( std::string ) )(&erCreatisAnalysis_wrapper::default_doIt)
	 , ( bp::arg("arg0") ) )
    .def(
	 "doItNumPy"
	 ,  (bool ( ::erCreatisAnalysis_wrapper::* )(boost::python::numeric::array& ,std::string ) )(&::erCreatisAnalysis_wrapper::doItNumPy))
 
   
    .def_readwrite( "param_adaptive_threshold", &erCreatisAnalysis::param_adaptive_threshold )    
    .def_readwrite( "param_alpha_shape",        &erCreatisAnalysis::param_alpha_shape )    
    .def_readwrite( "param_canny",              &erCreatisAnalysis::param_canny )    
    .def_readwrite( "param_smooth1",            &erCreatisAnalysis::param_smooth1 )    
    .def_readwrite( "param_smooth2",            &erCreatisAnalysis::param_smooth2 )    
    .def_readwrite( "rectOI",                   &erCreatisAnalysis::rectOI );
};
