#include "boost/python.hpp"

#include "erCv/erCvSegmentationParams.hpp"

namespace bp = boost::python;

void export_erCvSegmentationParams()
{
         bp::enum_< FindContoursMeth>("FindContoursMeth")
        .value("erCV_CHAIN_CODE", erCV_CHAIN_CODE)
        .value("erCV_CHAIN_APPROX_NONE", erCV_CHAIN_APPROX_NONE)
        .value("erCV_CHAIN_APPROX_SIMPLE", erCV_CHAIN_APPROX_SIMPLE)
        .value("erCV_CHAIN_APPROX_TC89_L1", erCV_CHAIN_APPROX_TC89_L1)
        .export_values()
        ;

    bp::enum_< FindContoursMode>("FindContoursMode")
        .value("erCV_RETR_EXTERNAL", erCV_RETR_EXTERNAL)
        .value("erCV_RETR_LIST", erCV_RETR_LIST)
        .value("erCV_RETR_CCOM", erCV_RETR_CCOM)
        .value("erCV_RETR_TREE", erCV_RETR_TREE)
        .export_values()
        ;

    bp::enum_< MatchTemplateType>("MatchTemplateType")
        .value("SQDIFF", SQDIFF)
        .value("SQDIFF_NORMED", SQDIFF_NORMED)
        .value("CCORR", CCORR)
        .value("CCORR_NORMED", CCORR_NORMED)
        .value("CCOEFF", CCOEFF)
        .value("CCOEFF_NORMED", CCOEFF_NORMED)
        .export_values()
        ;

    bp::class_< erFindcP >( "erFindcP", bp::init< >() )    
        .def( bp::init< FindContoursMode, FindContoursMeth, int >(( bp::arg("arg0"), 
								    bp::arg("arg1"), 
								    bp::arg("arg2") )) )    
        .def_readwrite( "level", &erFindcP::level )    
        .def_readwrite( "meth" , &erFindcP::meth )    
        .def_readwrite( "mode" , &erFindcP::mode );

    bp::class_< erPyramP >( "erPyramP", bp::init< >() )    
        .def( bp::init< int, int, int >(( bp::arg("arg0"), bp::arg("arg1"), bp::arg("arg2") )) )    
        .def_readwrite( "levl", &erPyramP::levl )    
        .def_readwrite( "trh1", &erPyramP::trh1 )    
        .def_readwrite( "trh2", &erPyramP::trh2 );


    bp::class_< erTemplP >( "erTemplP", bp::init< MatchTemplateType, CvRect, bool >
			    (( bp::arg("arg0"), bp::arg("arg1"), bp::arg("arg2") )) )    
        .def( bp::init< >() )    
        .def_readwrite( "drawing", &erTemplP::drawing )    
        .def_readonly( "rectan", &erTemplP::rectan )    
        .def_readwrite( "type", &erTemplP::type );

   bp::class_< erEqualP >( "erEqualP" )    
        .def_readwrite( "applic", &erEqualP::applic );

   bp::class_< erWhitBP >( "erWhitBP", bp::init< >() )    
        .def( bp::init< unsigned char, unsigned char, int, int >(( bp::arg("arg0"), bp::arg("arg1"), bp::arg("arg2"), bp::arg("arg3") )) )    
        .def_readwrite( "blob_b", &erWhitBP::blob_b )    
        .def_readwrite( "size_b", &erWhitBP::size_b )    
        .def_readwrite( "trh_b", &erWhitBP::trh_b )    
        .def_readwrite( "trh_w", &erWhitBP::trh_w );
};
