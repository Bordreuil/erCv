#include "boost/python.hpp"

//namespace bp = boost::python;

extern void export_erCvFiltersParams();
extern void export_erCvSegmentationParams();
extern void export_erCvTools();
extern void export_erCvBase();
extern void export_erCvAnalysis();
extern void export_erGeometricalParams();
extern void export_erCvSegmentation();

BOOST_PYTHON_MODULE(PyerCv)
{ 
  boost::python::numeric::array::set_module_and_type("numpy", "ndarray");
  export_erGeometricalParams();
  export_erCvFiltersParams();
  export_erCvSegmentationParams();
  export_erCvSegmentation();
  export_erCvAnalysis();
  export_erCvTools();
  export_erCvBase();
};
