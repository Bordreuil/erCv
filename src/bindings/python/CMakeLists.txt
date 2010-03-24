# Created by the script cgal_create_cmake_script
# This is the CMake script for compiling a CGAL application.


FIND_PACKAGE(PythonLibs REQUIRED)

INCLUDE_DIRECTORIES(${ERCV_INCLUDE_DIR} 
  ${PYTHON_INCLUDE_DIR}
  ${Boost_INCLUDE_DIR})


LINK_DIRECTORIES(${Boost_LIBRARIES_DIRS})

#LINK_LIBRARIES(	    ${Boost_PYTHON_LIBRARY} 
#	       ${PYTHON_LIBRARIES})

ADD_LIBRARY(PyerCv  SHARED Pyercv 
		           Py_erCvFiltersParams
			   Py_erCvTools
			   Py_erCvAnalysis
			   Py_erCvBase)
SET_TARGET_PROPERTIES(PyerCv PROPERTIES PREFIX ""
				            SUFFIX ".so")
TARGET_LINK_LIBRARIES(PyerCv ${Boost_PYTHON_LIBRARY} 
	       ${PYTHON_LIBRARIES}
	       erCv)
