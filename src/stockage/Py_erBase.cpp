#include "erBase.hpp"
#include "boost/python.hpp"

using namespace boost::python;

void Py_erBase()
{
    class_< IplImage >("IplImage","IplImage d openCv",init< >());
    class_<Image>("Image","Wrap class for image",init<char *>());

    class_<CvPoint2D32f >("cvPoint2D32f","Point flottant d opencv")
      .def_readwrite("x",&CvPoint2D32f::x)
      .def_readwrite("y",&CvPoint2D32f::y);

    def("erShowImage",&erShowImage);
    def("erLoadImage",&erLoadImage);
    def("erSaveImage",&erSaveImage);
};
