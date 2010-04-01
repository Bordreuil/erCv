# Created by the script cgal_create_cmake_script
# This is the CMake script for compiling a CGAL application.

cmake_minimum_required(VERSION 2.6)


INCLUDE_DIRECTORIES(${ERCV_INCLUDE_DIR} 
  ${OPENCV_INCLUDE_DIR})



LINK_LIBRARIES(${OpenCV_CV_LIBRARY} 
               ${OpenCV_CVAUX_LIBRARY} 
               ${OpenCV_HIGHGUI_LIBRARY} 
               ${OpenCV_CXCORE_LIBRARY} 
	       ${Boost_FILESYSTEM_LIBRARY}
	       ${Boost_SYSTEM_LIBRARY}
	       )

ADD_LIBRARY(erCv erCvSegmentation
                 erCalibration 
		 erCvBase 
		 erCvFiltersParams
		 erCvFilters
		 erFileUtilities 
		 erManipFileName
		 erPredicates
		 erCvInfofile
		 erCvTools
		 erCvAnalysis
	         Gui/erCvFiltersUser
		 Gui/erCvUserInteraction
                 Gui/erCvSegmentationUser 
		 params 
		 )

ADD_SUBDIRECTORY(bindings)
