#include "boost/python.hpp"

#include "erCv/erCvAnalysis.hpp"

namespace bp = boost::python;

void export_erCvAnalysis(){
  bp::class_< erAnalysis >( "erAnalysis", bp::init<>())
			    .def(bp::init< std::string, std::string >(( bp::arg("name"), bp::arg("infofile"))) )    
       
        .def_readwrite( "name",       &erAnalysis::name )
        .def_readwrite( "infoFile",   &erAnalysis::infoFile );
       

  bp::class_< erMacroDropAnalysis, bp::bases< erAnalysis > >( "erMacroDropAnalysis",bp::init<>()) 
    .def(bp::init<std::string,std::string >(( bp::arg("name"), bp::arg("infofile") )) )    
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
            , (bool ( ::erMacroDropAnalysis::* )( std::string ) )( &::erMacroDropAnalysis::doIt ) , ( bp::arg("arg0")),
	    "Applique l analyse macro drop au fichier ")
        .def_readwrite( "rectOI",       &erMacroDropAnalysis::rectOI )
        .def_readwrite( "cercToStart",   &erMacroDropAnalysis::cercToStart )
        .def_readwrite( "rectOI",       &erMacroDropAnalysis::rectOI )
        .def_readwrite( "param_smooth1",   &erMacroDropAnalysis::param_smooth1 )
        .def_readwrite( "param_smooth2",       &erMacroDropAnalysis::param_smooth2 )
        .def_readwrite( "param_canny",   &erMacroDropAnalysis::param_canny )
	.def_readwrite( "param_adaptive_threshold",       &erMacroDropAnalysis::param_adaptive_threshold );

};
