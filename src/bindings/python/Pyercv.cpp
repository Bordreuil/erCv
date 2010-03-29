#include "boost/python.hpp"

//namespace bp = boost::python;

extern void export_erCvFiltersParams();
extern void export_erCvTools();
extern void export_erCvBase();
extern void export_erCvAnalysis();

BOOST_PYTHON_MODULE(PyerCv)
{
  export_erCvFiltersParams();
  export_erCvAnalysis();
  export_erCvTools();
  export_erCvBase();
};
