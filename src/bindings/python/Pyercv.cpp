#include "boost/python.hpp"

//namespace bp = boost::python;

extern void export_erCvFiltersParams();
extern void export_erCvSegmentationParams();
extern void export_erCvTools();
extern void export_erCvBase();
extern void export_erCvAnalysis();
extern void export_erGeometricalParams();


BOOST_PYTHON_MODULE(PyerCv)
{ export_erGeometricalParams();
  export_erCvFiltersParams();
  export_erCvSegmentationParams();
  export_erCvAnalysis();
  export_erCvTools();
  export_erCvBase();
};
