# Created by the script cgal_create_cmake_script
# This is the CMake script for compiling a CGAL application.

if(${BUILD_PYTHON_MODULE})
	FIND_PACKAGE(PythonLibs REQUIRED)
	MESSAGE(STATUS "Python Libs :" ${PythonLibs_FOUND})
	INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR}
			    ${ERCV_INCLUDE_DIR} 
  			    ${PYTHON_INCLUDE_DIR}
			    ${PYTHON_INCLUDE_PATH})

	MESSAGE(STATUS "PYTHON include DIR:"  ${PYTHON_INCLUDE_DIR})
	LINK_DIRECTORIES(${Boost_LIBRARIES_DIRS})

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

endif(${BUILD_PYTHON_MODULE})
