CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/erCv-config.cmake.in
               ${CMAKE_CURRENT_BINARY_DIR}/ercv-config.cmake @ONLY)

CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/erCv-config-version.cmake.in
               ${CMAKE_CURRENT_BINARY_DIR}/ercv-config-version.cmake @ONLY)

INSTALL(FILES ${CMAKE_CURRENT_BINARY_DIR}/erCv-config.cmake
              ${CMAKE_CURRENT_BINARY_DIR}/ercv-config.cmake
              DESTINATION lib/erCv)