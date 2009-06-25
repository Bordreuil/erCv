# Created by the script cgal_create_cmake_script
# This is the CMake script for compiling a CGAL application.

CMAKE_MINIMUM_REQUIRED(VERSION 2.6.1)

project( erCv )

SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} tools/cmake/modules)
FIND_PACKAGE(OpenCV REQUIRED)
FIND_PACKAGE(CGAL REQUIRED)


FIND_PACKAGE(Boost COMPONENTS python)

MESSAGE(STATUS "OPENCV: " ${OPENCV_FOUND} )
MESSAGE(STATUS "CGAL  : " ${CGAL_FOUND} )
MESSAGE(STATUS "Boost  : " ${Boost_FOUND} )

if ( CGAL_FOUND )
  include( ${CGAL_USE_FILE} )
endif()
  
SET(ERCV_INCLUDE_DIR include)
SET(ERCV_LIBRARY_DIR src)

ADD_SUBDIRECTORY(src)
ADD_SUBDIRECTORY(tests)




