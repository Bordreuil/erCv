# Created by the script cgal_create_cmake_script
# This is the CMake script for compiling a CGAL application.

CMAKE_MINIMUM_REQUIRED(VERSION 2.6.0)

ENABLE_TESTING()


ADD_SUBDIRECTORY(base)
ADD_SUBDIRECTORY(calibration)
ADD_SUBDIRECTORY(cgal)
ADD_SUBDIRECTORY(filters)


