#include "erCalibration.hpp"
#include <boost/python.hpp>
#include <boost/cstdint.hpp>
#include <list>
#include <iostream>


// Using =======================================================================
using namespace boost::python;



void Py_erCalibration()
{
  // Object Calibration
    class_< erCalibration >("erCalibration","Calibration made by Edward", 
	 init<  >())

      .def(init<char*,char*,int,int>())
      //.def("getPatron",&erCalibration::getPatron,return_value_policy<manage_new_object>(),"permet d avoir l image")
      .def("getPatron",&erCalibration::getPatron,"permet d avoir l image de reference")
      .def("getMesure",&erCalibration::getMesure,"permet d avoir l image mesure")
      //.def("transformImage",&erCalibration::transformImage,return_value_policy<manage_new_object>());
      .def("transformImage",&erCalibration::transformImage);
    // Object d opencv

    class_< IplImage >("IplImage","IplImage d openCv",init< >());


    class_<Image>("Image","Wrap class for image",init<char *>());

    class_<CvPoint2D32f >("cvPoint2D32f","Point flottant d opencv")
      .def_readwrite("x",&CvPoint2D32f::x)
      .def_readwrite("y",&CvPoint2D32f::y);

    def("erShowImage",&erShowImage);
    def("erLoadImage",&erLoadImage);


}

