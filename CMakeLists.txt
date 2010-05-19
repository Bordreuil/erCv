# Created by the script cgal_create_cmake_script
# This is the CMake script for compiling a CGAL application.

CMAKE_MINIMUM_REQUIRED(VERSION 2.6.0)
MESSAGE(".....ErCv Message : For any trouble with install send e-mail : cyril.bordreuil@univ-montp2.fr")
project( erCv )

SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/tools/cmake/modules)
FIND_PACKAGE(OpenCV REQUIRED)
FIND_PACKAGE(CGAL REQUIRED)
FIND_PACKAGE(Boost COMPONENTS graph python filesystem system)

# A COMMENTER Pour Julien
OPTION(BUILD_PYTHON_MODULE  "Build python module for erCv" 1)
# A DECOMMENTER Pour Julien
#SET(BUILD_PYTHON_MODULE 1)
if(NOT ${BUILD_PYTHON_MODULE})
       MESSAGE(STATUS "Python Module of erCv will not be built")
endif(NOT ${BUILD_PYTHON_MODULE})

MESSAGE(STATUS "OPENCV: " ${OPENCV_FOUND} )
MESSAGE(STATUS "CGAL  : " ${CGAL_FOUND} )
MESSAGE(STATUS "Boost  : " ${Boost_FOUND} )

if ( CGAL_FOUND )
  include( ${CGAL_USE_FILE} )
endif()
  
SET(ERCV_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
#SET(ERCV_LIBRARY_DIR ${CMAKE_SOURCE_DIR}/src)
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/libs)

ADD_SUBDIRECTORY(src)
ADD_SUBDIRECTORY(tests)
ADD_SUBDIRECTORY(examples)

MESSAGE(".....ErCv Message : Some python Tools are available in :'tools/python'")



