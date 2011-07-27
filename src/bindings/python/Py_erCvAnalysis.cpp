#include "boost/python.hpp"
#include "pyublas/numpy.hpp"
#include "erCv/erCvAnalysis.hpp"

namespace bp = boost::python;

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
    
  }
  
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
  }
  bool doItNumPy(pyublas::numpy_array<unsigned short>& arr,std::string file_name="test_1.bmp")
  {
    const npy_intp* dims = arr.dims();
    
    int ncol = dims[0];
    int nlig = dims[1];
    unsigned short* storage = arr.data();
    char*  file_c   =   const_cast<char*>(file_name.c_str());
    setCurrentFileName(file_c);
    
    IplImage* im = cvCreateImage(cvSize(ncol,nlig),IPL_DEPTH_8U,3);

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
    erMetalTransfertAnalysis::doItImage(eim);

    return true;
  }
};

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
  
};

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


void export_erCvAnalysis(){
  // Seul les applications sont a wrapper: - erMacroDropAnalysis
  //                                       - erMetalTransfer
  //                                       - erMeltPool
  bp::class_< erAnalysis_wrapper, boost::noncopyable >( "erAnalysis", bp::init< >() )    
    .def( bp::init< std::string, bp::optional< std::string > >(( bp::arg("name"), bp::arg("infofile")="info" )) )    
    .def( 
	 "create"
	 , (void ( ::erAnalysis::* )(  ) )( &::erAnalysis::create ) )    
    .def( 
	 "defineCalibration"
	 , (void ( ::erAnalysis::* )(std::string,std::string) )( &::erAnalysis::defineCalibration )
	 , ( bp::arg("arg0"), bp::arg("arg1") ) )    
  
    .def( 
	 "doIt"
	 , bp::pure_virtual( (bool ( ::erAnalysis::* )( std::string ) )(&::erAnalysis::doIt) )
	 , ( bp::arg("arg0") ) );
  
  bp::class_< erMacroDropAnalysis_wrapper, bp::bases< erAnalysis > >( "erMacroDropAnalysis",bp::init<>())
    .def(bp::init<std::string,bp::optional<std::string> >(( bp::arg("name"), bp::arg("infofile")="info" )))   
    
    .def( 
	 "defineParametersUI"
	 , (bool ( ::erMacroDropAnalysis::* )(std::string  ) )( &::erMacroDropAnalysis::defineParametersUI ),(bp::arg("arg0") ))
    
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
    
    .def( 
	 "saveParameters"
	 , (void ( ::erMacroDropAnalysis::* )(std::string ) )( &::erMacroDropAnalysis::saveParameters )
	 , ( bp::arg("arg0") ) )
    
    .def_readwrite( "rectOI",                  &erMacroDropAnalysis::rectOI )
    .def_readwrite( "cercToStart",             &erMacroDropAnalysis::cercToStart )
    .def_readwrite( "rectOI",                  &erMacroDropAnalysis::rectOI )
    .def_readwrite( "param_smooth1",           &erMacroDropAnalysis::param_smooth1 )
    .def_readwrite( "param_smooth2",           &erMacroDropAnalysis::param_smooth2 )
    .def_readwrite( "param_canny",             &erMacroDropAnalysis::param_canny )
    .def_readwrite( "param_adaptive_threshold",&erMacroDropAnalysis::param_adaptive_threshold )
    .def_readwrite( "param_equalizer_histogram",&erMacroDropAnalysis::param_equalizer_histogram );
  

  
  bp::class_< erMetalTransfertAnalysis_wrapper, bp::bases< erAnalysis > >( "erMetalTransfertAnalysis", bp::init< >() )    
    .def( bp::init< std::string, bp::optional< std::string > >(( bp::arg("name"), bp::arg("infofile")="info" )) )    
    
    .def( 
	 "defineParameters"
	 , (void ( ::erMetalTransfertAnalysis::* )( ::CvRect,::erSmootP,::erSmootP,::erCannyP,::erAdThrP,::erAlphaP ) )( &::erMetalTransfertAnalysis::defineParameters )
	 , ( bp::arg("arg0"), bp::arg("arg1"), bp::arg("arg2"), bp::arg("arg3"), bp::arg("arg4"), bp::arg("arg5") ) )  
    
    .def( 
	 "defineParametersUI"
	 , (bool ( ::erMetalTransfertAnalysis::* )( std::string ) )( &::erMetalTransfertAnalysis::defineParametersUI )
	 , ( bp::arg("image") ) )    
    .def( 
	 "doIt"
	 , (bool ( ::erMetalTransfertAnalysis::* )( std::string ) )(&::erMetalTransfertAnalysis::doIt)
	 , (bool ( erMetalTransfertAnalysis_wrapper::* )( std::string ) )(&erMetalTransfertAnalysis_wrapper::default_doIt)
	 , ( bp::arg("arg0") ) )
    .def(
	 "doItNumPy"
	 ,  (bool ( ::erMetalTransfertAnalysis_wrapper::* )(boost::python::numeric::array& ,std::string ) )(&::erMetalTransfertAnalysis_wrapper::doItNumPy))
  
    //.def( 
    //         "loadParameters"
    //         , (void ( ::erMetalTransfertAnalysis::* )( std::string ) )( &::erMetalTransfertAnalysis::loadParameters )
    //         , ( bp::arg("arg0") ) )    
    .def( 
	 "saveParameters"
	 , (void ( ::erMetalTransfertAnalysis::* )( std::string ) )( &::erMetalTransfertAnalysis::saveParameters )
	 , ( bp::arg("arg0") ) )   
    .def( 
	 "setOutputGeometryFile"
	 , (void ( ::erMetalTransfertAnalysis::* )( std::string ) )( &::erMetalTransfertAnalysis::setOutputGeometryFile )
	 , ( bp::arg("arg0") ) )   
    .def_readwrite( "param_adaptive_threshold", &erMetalTransfertAnalysis::param_adaptive_threshold )    
    .def_readwrite( "param_alpha_shape",        &erMetalTransfertAnalysis::param_alpha_shape )    
    .def_readwrite( "param_canny",              &erMetalTransfertAnalysis::param_canny )    
    .def_readwrite( "param_smooth1",            &erMetalTransfertAnalysis::param_smooth1 )    
    .def_readwrite( "param_smooth2",            &erMetalTransfertAnalysis::param_smooth2 )    
    .def_readwrite( "output_geo",               &erMetalTransfertAnalysis::output_geometry_characteristics )
    .def_readwrite( "rectOI",                   &erMetalTransfertAnalysis::rectOI );
  
  
  
  bp::class_< erWeldPoolAnalysis_wrapper, bp::bases< erAnalysis > >( "erWeldPoolAnalysis", bp::init< >() )    
    .def( bp::init< std::string, bp::optional< std::string > >(( bp::arg("name"), bp::arg("infofile")="info" )) )    
    .def( 
	 "defineParameters"
	 , (void ( ::erWeldPoolAnalysis::* )( ::CvRect, ::erWhitBP, ::erSmootP,::erSmootP,::erCannyP,::erDilatP,::erThresP,::erTemplP,::erAlphaP ) )( &::erWeldPoolAnalysis::defineParameters )
	 , ( bp::arg("arg0"), bp::arg("arg1"), bp::arg("arg2"), bp::arg("arg3"), bp::arg("arg4"), bp::arg("arg5"), bp::arg("arg6"), bp::arg("arg7"), bp::arg("arg8") ) )    
    .def( 
	 "defineParametersUI"
	 , (bool ( ::erWeldPoolAnalysis::* )( std::string ) )( &::erWeldPoolAnalysis::defineParametersUI )
	 , ( bp::arg("image") ) )    
    .def( 
	 "doIt"
	 , (bool ( ::erWeldPoolAnalysis::* )( std::string ) )(&::erWeldPoolAnalysis::doIt)
	 , (bool ( erWeldPoolAnalysis_wrapper::* )( std::string ) )(&erWeldPoolAnalysis_wrapper::default_doIt)
	 , ( bp::arg("arg0") ) )    
    //  .def( 
    //             "loadParameters"
    //             , (void ( ::erWeldPoolAnalysis::* )( std::string ) )( &::erWeldPoolAnalysis::loadParameters )
    //             , ( bp::arg("arg0") ) )    
    //         .def( 
    //             "saveParameters"
    //             , (void ( ::erWeldPoolAnalysis::* )( std::string ) )( &::erWeldPoolAnalysis::saveParameters )
    //             , ( bp::arg("arg0") ) )    
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
  

  

 bp::class_< erLaserPrototypageAnalysis_wrapper, bp::bases< erAnalysis > >( "erLaserPrototypageAnalysis", bp::init< >() )    
        .def( bp::init< std::string, bp::optional< std::string > >(( bp::arg("name"), bp::arg("infofile")="info" )) )    
        .def( 
            "defineParameters"
            , (void ( ::erLaserPrototypageAnalysis::* )( ::CvRect,::erSmootP,::erSmootP,::erCannyP,::erDilatP,::erThresP,::erTemplP,::erAlphaP ) )( &::erLaserPrototypageAnalysis::defineParameters )
            , ( bp::arg("arg0"), bp::arg("arg1"), bp::arg("arg2"), bp::arg("arg3"), bp::arg("arg4"), bp::arg("arg5"), bp::arg("arg6"), bp::arg("arg7") ) )    
        .def( 
            "defineParametersUI"
            , (bool ( ::erLaserPrototypageAnalysis::* )( std::string ) )( &::erLaserPrototypageAnalysis::defineParametersUI )
            , ( bp::arg("image") ) )    
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
   // .def( 
   //         "loadParameters"
   //         , (void ( ::erLaserPrototypageAnalysis::* )( std::string ) )( &::erLaserPrototypageAnalysis::loadParameters )
   //         , ( bp::arg("arg0") ) )    
        .def( 
            "saveParameters"
            , (void ( ::erLaserPrototypageAnalysis::* )( std::string ) )( &::erLaserPrototypageAnalysis::saveParameters )
            , ( bp::arg("arg0") ) )    
        .def( 
            "setOutputGeometryFile"
            , (void ( ::erLaserPrototypageAnalysis::* )( std::string ) )( &::erLaserPrototypageAnalysis::setOutputGeometryFile )
            , ( bp::arg("arg0") ) )    
        .def_readwrite( "output_convex_polygon", &erLaserPrototypageAnalysis::output_convex_polygon )    
        .def_readwrite( "output_geometry_characteristics", &erLaserPrototypageAnalysis::output_geometry_characteristics )    
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
