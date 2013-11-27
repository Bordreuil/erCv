configure_file(${CMAKE_CURRENT_SOURCE_DIR}/doxygen.cfg.in
                 ${CMAKE_BINARY_DIR}/doxygen.cfg
                )

add_custom_target(docs ${DOXYGEN_EXECUTABLE}
                  doxygen.cfg
                 )