# Copyright Universite Montpellier 2/CNRS 
# Contributor(s) : 
#         Edward Romero 
#         Cyril Bordreuil
# Contact: cyril.bordreuil@univ-montp2.fr
# 
# This software is a computer program whose purpose is to [describe
#  functionalities and technical features of your software].
#
# This software is governed by the CeCILL license under French law and
# abiding by the rules of distribution of free software.  You can  use, 
# modify and/ or redistribute the software under the terms of the CeCILL
# license as circulated by CEA, CNRS and INRIA at the following URL
# "http:#www.cecill.info". 
#
# As a counterpart to the access to the source code and  rights to copy,
# modify and redistribute granted by the license, users are provided only
# with a limited warranty  and the software's author,  the holder of the
# economic rights,  and the successive licensors  have only  limited
# liability. 
#
# In this respect, the user's attention is drawn to the risks associated
# with loading,  using,  modifying and/or developing or reproducing the
# software by the user in light of its specific status of free software,
# that may mean  that it is complicated to manipulate,  and  that  also
# therefore means  that it is reserved for developers  and  experienced
# professionals having in-depth computer knowledge. Users are therefore
# encouraged to load and test the software's suitability as regards their
# requirements in conditions enabling the security of their systems and/or 
# data to be ensured and,  more generally, to use and operate it in the 
# same conditions as regards security. 
# 
# The fact that you are presently reading this means that you have had
# knowledge of the CeCILL license and that you accept its terms.
# Created by the script cgal_create_cmake_script
# This is the CMake script for compiling a CGAL application.

if(${ENABLE_PYTHON})
	FIND_PACKAGE(PythonLibs REQUIRED)
	MESSAGE(STATUS "Python Libs :" ${PythonLibs_FOUND})
	INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR}
			    ${ERCV_INCLUDE_DIR} 
  			    ${PYTHON_INCLUDE_DIR}
			    ${PYTHON_INCLUDE_PATH})

	MESSAGE(STATUS "PYTHON include DIR:"  ${PYTHON_INCLUDE_DIR})
	LINK_DIRECTORIES(${Boost_LIBRARIES_DIRS})

	ADD_LIBRARY(PyerCv  SHARED Pyercv 

			   Py_erGeometricalParams
			   Py_erCvSegmentationParams
			   Py_erCvSegmentation
		           Py_erCvFiltersParams
			   Py_erCvTools
			   Py_erCvAnalysis
			   Py_erCalibration
			   Py_erCvBase
			   Py_erGeometricalProperties
			   Py_erSkeleton
			   Py_erChainPoints)

         SET_TARGET_PROPERTIES(PyerCv PROPERTIES PREFIX ""
				            SUFFIX ".so")

         TARGET_LINK_LIBRARIES(PyerCv 
	       ${PYTHON_LIBRARIES}
	       ${Boost_PYTHON_LIBRARY} 
	       erCv)
	 install(TARGETS PyerCv DESTINATION lib 
	                        COMPONENT Runtime
				EXPORT erCv-targets)
			      
endif(${ENABLE_PYTHON})
