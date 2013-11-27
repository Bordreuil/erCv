
#include "boost/python.hpp"

#include "erCv/erCvTools.hpp"

namespace bp = boost::python;

void export_erCvTools()
{
    bp::class_< erImageIncrement >( "erImageIncrement", bp::init< >() )    
        .def( bp::init< int, int, int >(( bp::arg("arg0"), bp::arg("arg1"), bp::arg("arg2") )) )    
        .def( 
            "inc"
            , (int ( ::erImageIncrement::* )(  ) )( &::erImageIncrement::inc ) );
};
