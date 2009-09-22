# Created by the script cgal_create_cmake_script
# This is the CMake script for compiling a CGAL application.


INCLUDE_DIRECTORIES(${ERCV_INCLUDE_DIR} 
                     ${OPENCV_INCLUDE_DIR})

SET(LIBRARY_OUTPUT_PATH ../lib)

LINK_LIBRARIES(${OpenCV_CV_LIBRARY} 
               ${OpenCV_CVAUX_LIBRARY} 
	       ${OpenCV_HIGHGUI_LIBRARY} 
	       ${OpenCV_CXCORE_LIBRARY} )

ADD_LIBRARY(erCv erCvSegmentation
                 erCalibration 
		 erCvBase 
		 erCvUser_interac
		 erFileUtilities 
		 erCvFilters
		 erCvFiltersUser
		 erPredicates)

