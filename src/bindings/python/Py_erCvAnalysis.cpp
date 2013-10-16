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
    const npy_intp* dims = arr.dims();
    int ncol = dims[0];
    int nlig = dims[1];
    
    unsigned short* storage = arr.data();
    char*  file_c   =   const_cast<char*>(file_name.c_str());
    setCurrentFileName(file_c);
    
    IplImage* im = cvCreateImage(cvSize(nlig,ncol),IPL_DEPTH_8U,3);
    for(int i=0;i<ncol;i++)
       {
	  for(int j=0;j < nlig;j++)
	  { 

	    unsigned short va = storage[j+i*nlig]*256/65536;
	    CvScalar val      = cvScalarAll(va);
	    cvSet2D(im,i,j,val);
	  };

      }; 


    erImage eim(im);
    erMetalTransfertAnalysis::doItImage(eim);

    return true;
  }
};
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
     const npy_intp* dims = arr.dims();
    int ncol = dims[0];
    int nlig = dims[1];
    
    unsigned short* storage = arr.data();
    char*  file_c   =   const_cast<char*>(file_name.c_str());
    setCurrentFileName(file_c);
    
    IplImage* im = cvCreateImage(cvSize(nlig,ncol),IPL_DEPTH_8U,3);
    for(int i=0;i<ncol;i++)
       {
	  for(int j=0;j < nlig;j++)
	  { 

	    unsigned short va = storage[j+i*nlig]*256/65536;
	    CvScalar val      = cvScalarAll(va);
	    cvSet2D(im,i,j,val);
	  };

      }; 


    erImage eim(im);
   
    erMultiMetalTransfertAnalysis::doItImage(eim);

    return true;
  }
};


//-----------------------------------------------------------------------
//
//    ER_METAL_ANALYSIS_WRAPPER
//
//-----------------------------------------------------------------------


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
    const npy_intp* dims = arr.dims();
    int ncol = dims[0];
    int nlig = dims[1];
    //std::cout << ncol << " " << nlig << std::endl;
    unsigned short* storage = arr.data();
    char*  file_c   =   const_cast<char*>(file_name.c_str());
    setCurrentFileName(file_c);
    
    IplImage* im = cvCreateImage(cvSize(nlig,ncol),IPL_DEPTH_8U,3);
    for(int i=0;i<ncol;i++)
       {
	  for(int j=0;j < nlig;j++)
	  { 

	    unsigned short va = storage[j+i*nlig];
	    //std::cout << va << " ";
	    CvScalar val      = cvScalarAll(va);
	    cvSet2D(im,i,j,val);
	  };

      }; 
    //std::cout << std::endl;

    erImage eim(im);
    erCreatisAnalysis::doItImage(eim);

    return true;
  }
};


//-----------------------------------------------------------------------
//
//    ER_SOLIDIFICATION_ANALYSIS_WRAPPER
//
//-----------------------------------------------------------------------

struct erSolidificationAnalysis_wrapper : erSolidificationAnalysis, bp::wrapper< erSolidificationAnalysis > {
  
  erSolidificationAnalysis_wrapper(erSolidificationAnalysis const & arg )
    : erSolidificationAnalysis( arg )
    , bp::wrapper< erSolidificationAnalysis >(){
    // copy constructor
    
  }
  
  erSolidificationAnalysis_wrapper( )
    : erSolidificationAnalysis( )
    , bp::wrapper< erSolidificationAnalysis >(){
    // null constructor
    
  }
  
  erSolidificationAnalysis_wrapper(std::string name, std::string infofile="info" )
    : erSolidificationAnalysis( name, infofile )
    , bp::wrapper< erSolidificationAnalysis >(){
    // constructor
    
  };
  
  virtual bool doIt( std::string arg0 ) {
    if( bp::override func_doIt = this->get_override( "doIt" ) )
      return func_doIt( arg0 );
    else
      return this->erSolidificationAnalysis::doIt( arg0 );
  };
  //virtual bool doItImage( erImage& arg0 ) {
  //  if( bp::override func_doItImage = this->get_override( "doItImage" ) )
  //    return func_doItImage( arg0 );
  //  else
  //    return this->erSolidificationAnalysis::doItImage( arg0 );
  //}
  
  bool default_doIt( std::string arg0 ) {
    return erSolidificationAnalysis::doIt( arg0 );
  };

  bool doItNumPy(pyublas::numpy_array<unsigned short>& arr,std::string file_name="test_1.bmp")
  {
    const npy_intp* dims = arr.dims();
    int ncol = dims[0];
    int nlig = dims[1];
    
    unsigned short* storage = arr.data();
    char*  file_c   =   const_cast<char*>(file_name.c_str());
    setCurrentFileName(file_c);
    
    IplImage* im = cvCreateImage(cvSize(nlig,ncol),IPL_DEPTH_8U,3);
    for(int i=0;i<ncol;i++)
       {
	  for(int j=0;j < nlig;j++)
	  { 

	    unsigned short va = storage[j+i*nlig]*256/65536;
	    CvScalar val      = cvScalarAll(va);
	    cvSet2D(im,i,j,val);
	  };

      }; 

    erImage eim(im);
    erSolidificationAnalysis::doItImage(eim);

    return true;
  }
};
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




    const npy_intp* dims = arr.dims();

    int ncol = dims[0];
    int nlig = dims[1];
    unsigned short* storage = arr.data();
    char*  file_c   =   const_cast<char*>(file_name.c_str());
    setCurrentFileName(file_c);
    
    IplImage* im = cvCreateImage(cvSize(nlig,ncol),IPL_DEPTH_8U,3);

    for(int i=0;i<ncol;i++)
      {
	for(int j=0;j < nlig;j++)
	  { 
	    unsigned short va = storage[i*ncol+j]*256/65536;
	    CvScalar val = cvScalarAll(va);
	    cvSet2D(im,i,j,val);
	  };
      }; 




    erImage eim(im);
    erWireAnalysis::doItImage(eim);

    return true;
  }
};
//----------------------------------------------------------------------
//  ER_TRANSFOR
//




//-----------------------------------------------------------------------
//
//    ER_WELD_ANALYSIS_WRAPPER
//
//-----------------------------------------------------------------------

struct erWeldPoolAnalysis_wrapper : erWeldPoolAnalysis, bp::wrapper< erWeldPoolAnalysis > {
  
  erWeldPoolAnalysis_wrapper(erWeldPoolAnalysis const & arg )
    : erWeldPoolAnalysis( arg )
    , bp::wrapper< erWeldPoolAnalysis >(){
    // copy constructor
    
  }
  
  erWeldPoolAnalysis_wrapper( )
    : erWeldPoolAnalysis( )
    , bp::wrapper< erWeldPoolAnalysis >(){
    // null constructor
    
  }
  
  erWeldPoolAnalysis_wrapper(std::string name,std::string infofile="info" )
    : erWeldPoolAnalysis( name, infofile )
    , bp::wrapper< erWeldPoolAnalysis >(){
    // constructor
    
  }
  
  virtual bool doIt(std::string arg0 ) {
    if( bp::override func_doIt = this->get_override( "doIt" ) )
      return func_doIt( arg0 );
    else
      return this->erWeldPoolAnalysis::doIt( arg0 );
  }
  
  
  bool default_doIt(std::string arg0 ) {
    return erWeldPoolAnalysis::doIt( arg0 );
  }
bool doItNumPy(pyublas::numpy_array<unsigned short>& arr,std::string file_name="test_1.bmp")
  {




    const npy_intp* dims = arr.dims();

    int ncol = dims[0];
    int nlig = dims[1];
    unsigned short* storage = arr.data();
    char*  file_c   =   const_cast<char*>(file_name.c_str());
    setCurrentFileName(file_c);
    
    IplImage* im = cvCreateImage(cvSize(nlig,ncol),IPL_DEPTH_8U,3);

    for(int i=0;i<ncol;i++)
      {
	for(int j=0;j < nlig;j++)
	  { 
	    unsigned short va = storage[i*ncol+j]*256/65536;
	    CvScalar val = cvScalarAll(va);
	    cvSet2D(im,i,j,val);
	  };
      }; 




    erImage eim(im);
    erWeldPoolAnalysis::doItImage(eim);

    return true;
  }
  
};

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




    const npy_intp* dims = arr.dims();

    int ncol = dims[0];
    int nlig = dims[1];
    unsigned short* storage = arr.data();
    char*  file_c   =   const_cast<char*>(file_name.c_str());
    setCurrentFileName(file_c);
    
    IplImage* im = cvCreateImage(cvSize(nlig,ncol),IPL_DEPTH_8U,3);

    for(int i=0;i<ncol;i++)
      {
	for(int j=0;j < nlig;j++)
	  { 
	    unsigned short va = storage[i*ncol+j]*256/65536;
	    CvScalar val = cvScalarAll(va);
	    cvSet2D(im,i,j,val);
	  };
      }; 




    erImage eim(im);
    erWeldPoolSolidificationAnalysis::doItImage(eim);

    return true;
  }
  
};
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

//-----------------------------------------------------------------------
//
//    EXPORT_ANALYSIS
//
//-----------------------------------------------------------------------
void export_erCvAnalysis(){
  // Seul les applications sont a wrapper: - erMacroDropAnalysis
  //                                       - erMetalTransfer
  //                                       - erMeltPool
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
    //   .def(
    //		 "useCalibration"
    //		 ,  (boost::python::numeric::array ( ::erAnalysis_wrapper::* )(boost::python::numeric::array&  ) )(&::erAnalysis_wrapper::useCalibration))
   
    .def( 
	 "doIt"
	 , bp::pure_virtual( (bool ( ::erAnalysis::* )( std::string ) )(&::erAnalysis::doIt) )
	 , ( bp::arg("arg0") ) )
   .def_readwrite( "dir_analysis",                  &erAnalysis::dir_analysis )
   .def_readwrite( "name",                  &erAnalysis::name)
   .def_readwrite( "output_name",                  &erAnalysis::output_name);
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
  //-----------------------------------------------------------------------------------------------------------
  //
  // 
  // Python ::::   ER_MULTI_TRANSFERT_ANALYSIS
  //
  //
  //-----------------------------------------------------------------------------------------------------------  

  
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
 //-----------------------------------------------------------------------------------------------------------
  //
  // 
  // Python ::::   ER_CREATIS_ANALYSIS
  //
  //
  //-----------------------------------------------------------------------------------------------------------  

  
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
//-----------------------------------------------------------------------------------------------------------
  //
  // 
  // Python ::::   ER_SOLIDIFICATION_ANALYSIS
  //
  //
  //-----------------------------------------------------------------------------------------------------------  

  
  bp::class_< erSolidificationAnalysis_wrapper, bp::bases< erAnalysis > >( "erSolidificationAnalysis", bp::init< >() )    
    .def( bp::init< std::string, bp::optional< std::string > >(( bp::arg("name"), bp::arg("infofile")="info" )) )    
    
    .def( 
	 "defineParameters"
	 , (void ( ::erSolidificationAnalysis::* )( ::CvRect,::erSmootP,::erCannyP,::erThresP,::erAlphaP ) )( &::erSolidificationAnalysis::defineParameters )
	 , ( bp::arg("arg0"), bp::arg("arg1"), bp::arg("arg2"), bp::arg("arg3"), bp::arg("arg4")) )  
    
   
    .def( 
	 "doIt"
	 , (bool ( ::erSolidificationAnalysis::* )( std::string ) )(&::erSolidificationAnalysis::doIt)
	 , (bool ( erSolidificationAnalysis_wrapper::* )( std::string ) )(&erSolidificationAnalysis_wrapper::default_doIt)
	 , ( bp::arg("arg0") ) )
    .def(
	 "doItNumPy"
	 ,  (bool ( ::erSolidificationAnalysis_wrapper::* )(boost::python::numeric::array& ,std::string ) )(&::erSolidificationAnalysis_wrapper::doItNumPy))
  
 
    .def_readwrite( "param_threshold"           , &erSolidificationAnalysis::param_threshold )    
    .def_readwrite( "param_alpha_shape"         , &erSolidificationAnalysis::param_alpha_shape )    
    .def_readwrite( "param_canny"               , &erSolidificationAnalysis::param_canny )    
    .def_readwrite( "param_smooth1"             , &erSolidificationAnalysis::param_smooth1 )    
    .def_readwrite( "rectOI"                    , &erSolidificationAnalysis::rectOI );
  //-----------------------------------------------------------------------------------------------------------
  //
  // 
  // Python ::::   ER_WIRE_ANALYSIS
  //
  //
  //-----------------------------------------------------------------------------------------------------------  
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
  //-----------------------------------------------------------------------------------------------------------
  //
  // 
  // Python ::::   ER_WELD_POOL_ANALYSIS
  //
  //
  //-----------------------------------------------------------------------------------------------------------  
  
  bp::class_< erWeldPoolAnalysis_wrapper, bp::bases< erAnalysis > >( "erWeldPoolAnalysis", bp::init< >() )    
    .def( bp::init< std::string, bp::optional< std::string > >(( bp::arg("name"), bp::arg("infofile")="info" )) )    
    .def( 
	 "defineParameters"
	 , (void ( ::erWeldPoolAnalysis::* )( ::CvRect, ::erWhitBP, ::erSmootP,::erSmootP,::erCannyP,::erDilatP,::erThresP,::erTemplP,::erAlphaP ) )( &::erWeldPoolAnalysis::defineParameters )
	 , ( bp::arg("arg0"), bp::arg("arg1"), bp::arg("arg2"), bp::arg("arg3"), bp::arg("arg4"), bp::arg("arg5"), bp::arg("arg6"), bp::arg("arg7"), bp::arg("arg8") ) )    
  
    .def( 
	 "doIt"
	 , (bool ( ::erWeldPoolAnalysis::* )( std::string ) )(&::erWeldPoolAnalysis::doIt)
	 , (bool ( erWeldPoolAnalysis_wrapper::* )( std::string ) )(&erWeldPoolAnalysis_wrapper::default_doIt)
	 , ( bp::arg("arg0") ) )    
    .def(
	 "doItNumPy"
	 ,  (bool ( ::erWeldPoolAnalysis_wrapper::* )(boost::python::numeric::array& ,std::string ) )(&::erWeldPoolAnalysis_wrapper::doItNumPy))
  
    .def(
		 "setWhiteBlobDetection"
		 ,(void  (::erWeldPoolAnalysis::*)(bool) )( &::erWeldPoolAnalysis::setWhiteBlobDetection)
		 ,(bp::arg("arg0") ))


    //        .def_readwrite( "param_adaptive_threshold", &erWeldPoolAnalysis::param_adaptive_threshold )    
    .def_readwrite( "param_alpha_shape" , &erWeldPoolAnalysis::param_alpha_shape )    
    .def_readwrite( "param_canny"       , &erWeldPoolAnalysis::param_canny )    
    .def_readwrite( "param_white_blob"  , &erWeldPoolAnalysis::param_white_blob )
    .def_readwrite( "param_dilate"      , &erWeldPoolAnalysis::param_dilate )      
    //        .def_readwrite( "param_equalizer_histogram", &erWeldPoolAnalysis::param_equalizer_histogram )    
    //        .def_readwrite( "param_find_contours", &erWeldPoolAnalysis::param_find_contours )    
    .def_readwrite( "param_smooth1"     , &erWeldPoolAnalysis::param_smooth1 )    
    .def_readwrite( "param_smooth2"     , &erWeldPoolAnalysis::param_smooth2 )    
    .def_readwrite( "param_template"    , &erWeldPoolAnalysis::param_template )  
    .def_readwrite( "param_threshold"   , &erWeldPoolAnalysis::param_threshold)
    .def_readwrite( "rectOI"            , &erWeldPoolAnalysis::rectOI );
  //-----------------------------------------------------------------------------------------------------------
  //
  // 
  // Python ::::   ER_WELD_POOL_SOLIDIFICATION_ANALYSIS
  //
  //
  //-----------------------------------------------------------------------------------------------------------  
  
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
  
   
    //        .def_readwrite( "param_adaptive_threshold", &erWeldPoolAnalysis::param_adaptive_threshold )    
    .def_readwrite( "param_alpha_shape" , &erWeldPoolSolidificationAnalysis::param_alpha_shape )    
    .def_readwrite( "param_canny"       , &erWeldPoolSolidificationAnalysis::param_canny )    

    .def_readwrite( "param_smooth1"     , &erWeldPoolSolidificationAnalysis::param_smooth1 )    
     
    .def_readwrite( "param_template"    , &erWeldPoolSolidificationAnalysis::param_template )  
    .def_readwrite( "param_threshold"   , &erWeldPoolSolidificationAnalysis::param_threshold)
    .def_readwrite( "rectOI"            , &erWeldPoolSolidificationAnalysis::rectOI );
  //-----------------------------------------------------------------------------------------------------------
  //
  // 
  // Python ::::   ER_LASER_PROTOTYPAGE_ANALYSIS
  //
  //
  //-----------------------------------------------------------------------------------------------------------  
  

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
