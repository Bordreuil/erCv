//#include "Py_erCalibration_doc.hpp"
#include <erCv/erCalibration.hpp>
#include <boost/python.hpp>

#include "boost/python.hpp"
#include "pyublas/numpy.hpp"
#include <boost/numeric/ublas/storage.hpp>
namespace bp = boost::python;

//-----------------------------------------------------------------------
//
//    ER_CALIBRATION_WRAPPER
//
//-----------------------------------------------------------------------



struct erCalibration_wrapper : erCalibration, bp::wrapper< erCalibration > {
  
  erCalibration_wrapper( )
    : erCalibration( )
    , bp::wrapper< erCalibration >(){
    // null constructor
    
  };
  erCalibration_wrapper(std::string src,std::string tar,int ncx ,int ncy)
    : erCalibration(src.c_str(),tar.c_str(),ncx,ncy )
  {
  }

  pyublas::numpy_array<unsigned char> useCalibration(pyublas::numpy_array<unsigned char> arr_in)		   
  {
    const npy_intp* dims = arr_in.dims();
    int ncol = dims[0];
    int nlig = dims[1];
    //std::cout << ncol << " " << nlig << " " << arr_in.ndim()  << std::endl;

    unsigned char * storage = arr_in.data();
    IplImage*       imref   = cvCreateImage(cvSize(nlig,ncol),IPL_DEPTH_8U,1);
    //std::ofstream out("test.dat");
    for(int i=0;i<ncol;i++)
       {
	  for(int j=0;j < nlig;j++)
	  { 
	    
	    unsigned char va = storage[j+i*nlig]; //*256/65536;
	    //out << int(va) << " ";
	    CvScalar val      = cvScalarAll(va);
	    cvSet2D(imref,i,j,val);
	  };
	  //out << std::endl;
	  
       };

    erImage eim(imref);
    
    erImage eout;

    eout = this->transform_image(eim);

    IplImage * iout = &eout;
    CvSize cvs      = cvGetSize(iout);
   
    pyublas::numpy_array<unsigned char> arr_out(cvs.width*cvs.height);
    unsigned char* storout  = arr_out.data();
    for(int i=0;i<cvs.height;i++)
     	  {
     	  for(int j=0;j < cvs.width;j++)
     	  { 
	
     	    CvScalar val      = cvGet2D(&eout,i,j);
	   
     	    storout[j+i*cvs.width]     = val.val[0];
	  
     	  };
       };
   
    npy_intp dimsout [2] = {cvs.height,cvs.width};
    arr_out.reshape(2,dimsout);
    return arr_out;
  }

pyublas::numpy_array<double> distanceBetweenReferenceCorner()
{
  pyublas::numpy_array<double> dists(2);
  std::pair<double,double> distRef = distance_between_reference_corner();
  dists[0] = distRef.first;
  dists[1] = distRef.second;
  return dists;
  
};

pyublas::numpy_array<double> wrapPoint(double x,double y)
{
  pyublas::numpy_array<double> dists(2);
  std::pair<double,double> distRef = transformPoint(x,y);
  dists[0] = distRef.first;
  dists[1] = distRef.second;
  return dists;
};

};


// Using =======================================================================
//using namespace boost::python;

void export_erCalibration()
{
  // Object Calibration
  bp::class_< erCalibration_wrapper, boost::noncopyable >("erCalibration","Calibration made by Edward", 
			      bp::init<  >())

    .def(bp::init<std::string,std::string,int,int>())
      //.def("getPatron",&erCalibration::getPatron,return_value_policy<manage_new_object>(),"permet d avoir l image")
    // .def("getPatron",&erCalibration::get_patron,"permet d avoir l image de reference")
    //.def("getMesure",&erCalibration::get_mesure,"permet d avoir l image mesure")
      //.def("transformImage",&erCalibration::transformImage,return_value_policy<manage_new_object>());
      //.def("transformImage",&erCalibration::transform_image)
      .def(
    		 "useCalibration"
    		 ,  (boost::python::numeric::array ( ::erCalibration_wrapper::* )(boost::python::numeric::array&  ) )(&::erCalibration_wrapper::useCalibration))
    .def("distanceBetweenReferenceCorner"
	 ,  (boost::python::numeric::array ( ::erCalibration_wrapper::* )( ) )(&::erCalibration_wrapper::distanceBetweenReferenceCorner ))
    .def("wrapPoint"
	 ,  (boost::python::numeric::array ( ::erCalibration_wrapper::* )(double,double ) )(&::erCalibration_wrapper::wrapPoint    ) )
    .def("setWrapOffset",
	 &erCalibration::setWrapOffset)
    .def("checkCorners",
	 &erCalibration::checkCorners);
};

