CMAKE_MINIMUM_REQUIRED(VERSION 2.6.0)

INCLUDE_DIRECTORIES(${ERCV_INCLUDE_DIR} ${OPENCV_INCLUDE_DIR} ${CGAL_INCLUDE_DIR})
LINK_DIRECTORIES(${OPENCV_LIBRARY_DIR})


ADD_EXECUTABLE(test_cv test_cv.cpp)
TARGET_LINK_LIBRARIES(test_cv erCv ${OPENCV_LIBS})
# Definition d un test avec passage de ces arguments
ADD_TEST(testBase test_cv peo imageTestBase.bmp)

# Copie du fichier image necessaire au test dans 
# le repertoire de construction 
CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/imageTestBase.bmp
			${CMAKE_CURRENT_BINARY_DIR}/imageTestBase.bmp
			COPYONLY)
