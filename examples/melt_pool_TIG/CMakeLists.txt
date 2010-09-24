CMAKE_MINIMUM_REQUIRED(VERSION 2.6.0)

INCLUDE_DIRECTORIES(${ERCV_INCLUDE_DIR} ${OPENCV_INCLUDE_DIR} ${CGAL_INCLUDE_DIR})
LINK_DIRECTORIES(${OPENCV_LIBRARY_DIR})

ADD_EXECUTABLE(white_blob_detection white_blob_detection.cpp)
TARGET_LINK_LIBRARIES(white_blob_detection erCv ${OPENCV_LIBS})

ADD_EXECUTABLE(fusion_bain fusion_bain.cpp)
TARGET_LINK_LIBRARIES(fusion_bain erCv ${OPENCV_LIBS})

ADD_EXECUTABLE(melt_pool_tig melt_pool_tig.cpp)
TARGET_LINK_LIBRARIES(melt_pool_tig erCv ${OPENCV_LIBS})

ADD_EXECUTABLE(fusion_bain_python fusion_bain_python.cpp)
TARGET_LINK_LIBRARIES(fusion_bain_python erCv ${OPENCV_LIBS})

CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/imageExemple_1.bmp
			${CMAKE_CURRENT_BINARY_DIR}/imageExemple_1.bmp
			COPYONLY)

CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/imageExemple_2.bmp
			${CMAKE_CURRENT_BINARY_DIR}/imageExemple_2.bmp
			COPYONLY)

CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/imageExemple_3.bmp
			${CMAKE_CURRENT_BINARY_DIR}/imageExemple_3.bmp
			COPYONLY)
CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/example_full_bain_1.bmp
			${CMAKE_CURRENT_BINARY_DIR}/example_full_bain_1.bmp
			COPYONLY)

CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/example_full_bain_2.bmp
			${CMAKE_CURRENT_BINARY_DIR}/example_full_bain_2.bmp
			COPYONLY)

CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/example_full_bain_3.bmp
			${CMAKE_CURRENT_BINARY_DIR}/example_full_bain_3.bmp
			COPYONLY)

CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/example_full_bain_4.bmp
			${CMAKE_CURRENT_BINARY_DIR}/example_full_bain_4.bmp
			COPYONLY)

CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/calibration_target.bmp
			${CMAKE_CURRENT_BINARY_DIR}/calibration_target.bmp
			COPYONLY)

CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/calibration_source.jpg
			${CMAKE_CURRENT_BINARY_DIR}/calibration_source.jpg
			COPYONLY)
