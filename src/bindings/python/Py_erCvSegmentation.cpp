#include "boost/python.hpp"

#include "erCv/erCvSegmentation.hpp"

namespace bp = boost::python;

void export_erCvSegmentation()
{


  typedef void ( *erWhiteBlobDelete_function_type )(std::string);
  
  bp::def( 
	  "erWhiteBlobDelete"
	  , erWhiteBlobDelete_function_type( &::erWhiteBloborCorrection )
	  , ( bp::arg("arg0")) );
};
