CMAKE_MINIMUM_REQUIRED(VERSION 2.6.0)

INCLUDE_DIRECTORIES(${ERCV_INCLUDE_DIR} ${OPENCV_INCLUDE_DIR} ${CGAL_INCLUDE_DIR})
LINK_DIRECTORIES(${OPENCV_LIBRARY_DIR})

ADD_EXECUTABLE(laser_bain laser_bain.cpp)
TARGET_LINK_LIBRARIES(laser_bain erCv ${OPENCV_LIBS})


ADD_EXECUTABLE(laser_bain_python laser_bain_python.cpp)
TARGET_LINK_LIBRARIES(laser_bain_python erCv ${OPENCV_LIBS})


CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/example_laser_prototypage_1.jpg
			${CMAKE_CURRENT_BINARY_DIR}/example_laser_prototypage_1.jpg
			COPYONLY)

CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/example_laser_prototypage_2.jpg
			${CMAKE_CURRENT_BINARY_DIR}/example_laser_prototypage_2.jpg
			COPYONLY)

CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/example_laser_prototypage_3.jpg
			${CMAKE_CURRENT_BINARY_DIR}/example_laser_prototypage_3.jpg
			COPYONLY)

CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/example_laser_prototypage_4.jpg
			${CMAKE_CURRENT_BINARY_DIR}/example_laser_prototypage_4.jpg
			COPYONLY)

CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/example_laser_prototypage_5.jpg
			${CMAKE_CURRENT_BINARY_DIR}/example_laser_prototypage_5.jpg
			COPYONLY)
CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/visu.py
			${CMAKE_CURRENT_BINARY_DIR}/visu.py
			COPYONLY)