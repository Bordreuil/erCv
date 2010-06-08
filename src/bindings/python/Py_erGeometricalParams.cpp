#include<boost/python.hpp>

#include<erCv/geometry/geometricalParams.hpp>

namespace bp = boost::python;

void export_erGeometricalParams()
{
	//::erAlphaP
        typedef bp::class_< erAlphaP > erAlphaP_exposer_t;
        erAlphaP_exposer_t erAlphaP_exposer = erAlphaP_exposer_t( "erAlphaP", bp::init< >() );
        bp::scope erAlphaP_scope( erAlphaP_exposer );
        erAlphaP_exposer.def( bp::init< double >(( bp::arg("arg0") )) );
        bp::implicitly_convertible< double, erAlphaP >();
        erAlphaP_exposer.def_readwrite( "alpha", &erAlphaP::alpha );

};
