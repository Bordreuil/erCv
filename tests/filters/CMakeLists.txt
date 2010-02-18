CMAKE_MINIMUM_REQUIRED(VERSION 2.6.0)

INCLUDE_DIRECTORIES(${ERCV_INCLUDE_DIR} ${OPENCV_INCLUDE_DIR} ${CGAL_INCLUDE_DIR})


ADD_EXECUTABLE(test_cv_filters test_cv_filters.cpp)
TARGET_LINK_LIBRARIES(test_cv_filters erCv ${OPENCV_LIBS})
ADD_TEST(testFilters test_cv_filters peo imageTestFilter.bmp)
CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/imageTestFilter.bmp
			${CMAKE_CURRENT_BINARY_DIR}/imageTestFilter.bmp
			COPYONLY)

