# Created by the script cgal_create_cmake_script
# This is the CMake script for compiling a CGAL application.

CMAKE_MINIMUM_REQUIRED(VERSION 2.6.0)
MESSAGE(".....ErCv Message : For any trouble with install send e-mail : cyril.bordreuil@univ-montp2.fr")
project( erCv )


SET(ERCV_MAJOR_VERSION "1")
SET(ERCV_MINOR_VERSION "2")
SET(ERCV_PATCH_VERSION "0")

SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/tools/cmake/modules)
FIND_PACKAGE(OpenCV REQUIRED)
FIND_PACKAGE(CGAL REQUIRED)
FIND_PACKAGE(Boost COMPONENTS graph python filesystem system)
FIND_PACKAGE(Doxygen)

MESSAGE(STATUS "Doxygen Found: " ${DOXYGEN_FOUND} "'make docs' to generate documentation") 

if(DOXYGEN_FOUND)
  ADD_SUBDIRECTORY(docs)
endif(DOXYGEN_FOUND)


OPTION(ENABLE_PYTHON "Variable to build python bindings" OFF)

if(NOT ${ENABLE_PYTHON})
       MESSAGE(STATUS "Python Module of erCv will not be built")
endif(NOT ${ENABLE_PYTHON})

MESSAGE(STATUS "OPENCV: " ${OPENCV_FOUND} )
MESSAGE(STATUS "CGAL  : " ${CGAL_FOUND} )
MESSAGE(STATUS "Boost  : " ${Boost_FOUND} )

if ( CGAL_FOUND )
  include( ${CGAL_USE_FILE} )
endif()
MESSAGE(STATUS "OpenCv LIBS:" ${OpenCV_LIBS})
MESSAGE(STATUS "OpenCv include:" ${OpenCV_INCLUDE_DIRS})
SET(CV_LIBRARIES ${OpenCV_LIBS})
SET(CV_INCLUDE_DIR ${OpenCV_INCLUDE_DIRS})
MESSAGE(STATUS "CV Libraries:" ${CV_LIBRARIES})
SET(ERCV_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/erCv)

ADD_SUBDIRECTORY(src)
ADD_SUBDIRECTORY(tests)
ADD_SUBDIRECTORY(include)
ADD_SUBDIRECTORY(examples)
ADD_SUBDIRECTORY(config)
ADD_SUBDIRECTORY(tools)

MESSAGE(".....ErCv Message : Some python Tools are available in :'tools/python'")



install(EXPORT erCv-targets DESTINATION lib/erCv)

include(InstallRequiredSystemLibraries)

set(CPACK_PACKAGE_NAME   "erCV")
set(CPACK_PACKAGE_VENDOR "LMGC/UM2/UM5508")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "erCv is an software dedicated to contour analysis
for images acquired during welding process")
set(CPACK_PACKAGE_VERSION_MAJOR ${ERCV_MAJOR_VERSION})
set(CPACK_PACKAGE_VERSION_MINOR ${ERCV_MINOR_VERSION})
set(CPACK_PACKAGE_VERSION_PATCH ${ERCV_PATCH_VERSION})
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/Licence_CeCILL_V1.1-US.txt")
include(CPack)
