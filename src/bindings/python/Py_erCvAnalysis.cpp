#include "boost/python.hpp"

#include "erCv/erCvAnalysis.hpp"

namespace bp = boost::python;

void export_erCvAnalysis(){
  bp::class_< erAnalysis >( "erAnalysis", bp::init<>())
			    .def(bp::init< std::string, std::string,std::string >(( bp::arg("name"), bp::arg("infofile"), bp::arg("firstImage") )) )    
        .def( 
            "setImageIncrement"
            , (void ( ::erAnalysis::* )( ::erImageIncrement ) )( &::erAnalysis::setImageIncrement )
            , ( bp::arg("ii") ) )    
        .def( 
            "setTotalImages"
            , (void ( ::erAnalysis::* )( int ) )( &::erAnalysis::setTotalImages )
            , ( bp::arg("arg0") ) ) 
        .def_readwrite( "name",       &erAnalysis::name )
        .def_readwrite( "infoFile",   &erAnalysis::infoFile )
        .def_readwrite( "firstImage", &erAnalysis::firstImage )
        .def_readwrite( "incImage",   &erAnalysis::incImage )    
        .def_readwrite( "totalImage", &erAnalysis::totalImage );

  bp::class_< erMacroDropAnalysis, bp::bases< erAnalysis > >( "erMacroDropAnalysis",bp::init<>()) 
    .def(bp::init<std::string,std::string, std::string >(( bp::arg("name"), bp::arg("infofile"), bp::arg("firstImage") )) )    
        .def( 
            "defineParameterUI"
            , (bool ( ::erMacroDropAnalysis::* )(  ) )( &::erMacroDropAnalysis::defineParameterUI ));


};
