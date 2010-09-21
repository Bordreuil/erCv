#include "boost/python.hpp"

#include "erCv/erCvSegmentation.hpp"

namespace bp = boost::python;

void export_erCvSegmentation()
{

   typedef void ( *erWhiteBlobDelete_function_type )( char *,::erWhitBP );
        
        bp::def( 
            "erWhiteBlobDelete"
            , erWhiteBlobDelete_function_type( &::erWhiteBlobDelete )
            , ( bp::arg("arg0"), bp::arg("arg1") ) );
};
