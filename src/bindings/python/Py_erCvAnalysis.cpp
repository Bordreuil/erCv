#include "boost/python.hpp"

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
    
    
    bool default_doIt( std::string arg0 ) {
        return erMetalTransfertAnalysis::doIt( arg0 );
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
            , (void ( ::erMacroDropAnalysis::* )( ::CvRect,::erCerc,::erSmootP,::erSmootP,::erCannyP,::erAdThrP ) )
	    ( &::erMacroDropAnalysis::defineParameters )
            , ( bp::arg("arg0"), bp::arg("arg1"), bp::arg("arg2"), bp::arg("arg3"), bp::arg("arg4"), bp::arg("arg5") ) )    

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
	.def_readwrite( "param_adaptive_threshold",&erMacroDropAnalysis::param_adaptive_threshold );

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

};
