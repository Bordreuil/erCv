CMAKE_MINIMUM_REQUIRED(VERSION 2.6.0)

INCLUDE_DIRECTORIES(${ERCV_INCLUDE_DIR} ${OPENCV_INCLUDE_DIR} ${CGAL_INCLUDE_DIR})
LINK_DIRECTORIES(${OPENCV_LIBRARY_DIR})


ADD_EXECUTABLE(test_blob blob_detect.cpp)
TARGET_LINK_LIBRARIES(test_blob erCv ${OPENCV_LIBS})
# Definition d un test avec passage de ces arguments
#ADD_TEST(testBlob test_blob peo imageTestBase.bmp)