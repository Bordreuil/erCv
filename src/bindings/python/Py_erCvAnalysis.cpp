#include "boost/python.hpp"

#include "erCv/erCvAnalysis.hpp"

namespace bp = boost::python;

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



void export_erCvAnalysis(){
  // Seul les applications sont a wrapper: - erMacroDropAnalysis
  //                                       - erMetalTransfer
  //                                       - erMeltPool

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

};
