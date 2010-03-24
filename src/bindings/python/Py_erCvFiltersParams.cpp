#include "boost/python.hpp"

#include "erCv/erCvFiltersParams.hpp"

namespace bp = boost::python;

void export_erCvFiltersParams()
{
    bp::enum_< SmoothType>("SmoothType")
        .value("BLUR_NO_SCALE", BLUR_NO_SCALE)
        .value("BLUR", BLUR)
        .value("GAUSSIAN", GAUSSIAN)
        .value("MEDIAN", MEDIAN)
        .value("BILATERAL", BILATERAL)
        .export_values()
        ;

    bp::class_< erAdThrP >( "erAdThrP" )    
        .def_readwrite( "adpt", &erAdThrP::adpt )    
        .def_readwrite( "neig", &erAdThrP::neig )    
        .def_readwrite( "trh0", &erAdThrP::trh0 )    
        .def_readwrite( "trhP", &erAdThrP::trhP )    
        .def_readwrite( "type", &erAdThrP::type );

    bp::class_< erCannyP >( "erCannyP" )    
        .def_readwrite( "trh1", &erCannyP::trh1 )    
        .def_readwrite( "trh2", &erCannyP::trh2 );

    bp::class_< erDilatP >( "erDilatP" )    
        .def_readwrite( "iter", &erDilatP::iter );

    bp::class_< erErodeP >( "erErodeP" )    
        .def_readwrite( "iter", &erErodeP::iter );

    bp::class_< erSmootP >( "erSmootP" )    
        .def_readwrite( "size", &erSmootP::size )    
        .def_readwrite( "type", &erSmootP::type );

    bp::class_< erSobelP >( "erSobelP" )    
        .def_readwrite( "trhX", &erSobelP::trhX )    
        .def_readwrite( "trhY", &erSobelP::trhY );

    bp::class_< erThresP >( "erThresP" )    
        .def_readwrite( "trh1", &erThresP::trh1 )    
        .def_readwrite( "trh2", &erThresP::trh2 )    
        .def_readwrite( "type", &erThresP::type );

    // bp::scope().attr("nbSmoothType") = nbSmoothType;
};
