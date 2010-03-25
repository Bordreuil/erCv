#include "boost/python.hpp"

#include "erCv/erCvBase.hpp"

namespace bp = boost::python;

void export_erCvBase()
{
    bp::class_< CvPoint >( "CvPoint" )    
        .def_readwrite( "x", &CvPoint::x )    
        .def_readwrite( "y", &CvPoint::y );

    bp::class_< CvRect >( "CvRect" )    
        .def_readwrite( "height", &CvRect::height )    
        .def_readwrite( "width", &CvRect::width )    
        .def_readwrite( "x", &CvRect::x )    
        .def_readwrite( "y", &CvRect::y );

    bp::class_< erCerc >( "erCerc" , bp::init< >())    
        .def( bp::init< int, int, int >(( bp::arg("arg0"), bp::arg("arg1"), bp::arg("arg2") )) ) 
        .def_readonly( "centro", &erCerc::centro )    
        .def_readwrite( "radio", &erCerc::radio );
};
