# Find Doxygen
find_package(Doxygen REQUIRED)

# Set Doxygen configuration
set(DOXYGEN_INPUT_DIR ${CMAKE_SOURCE_DIR}/src)
set(DOXYGEN_OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/doxygen)
set(DOXYGEN_INDEX_FILE ${DOXYGEN_OUTPUT_DIR}/html/index.html)

# Configure Doxygen
set(DOXYFILE_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
set(DOXYFILE_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

configure_file(${DOXYFILE_IN} ${DOXYFILE_OUT} @ONLY)

# Create output directory
file(MAKE_DIRECTORY ${DOXYGEN_OUTPUT_DIR})

# Custom command to generate documentation
add_custom_command(OUTPUT ${DOXYGEN_INDEX_FILE}
    DEPENDS ${DOXYFILE_OUT}
    COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYFILE_OUT}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    MAIN_DEPENDENCY ${DOXYFILE_OUT}
    COMMENT "Generating API documentation with Doxygen"
    VERBATIM
)

# Custom target for documentation
add_custom_target(docs ALL DEPENDS ${DOXYGEN_INDEX_FILE})

# Install documentation
install(DIRECTORY ${DOXYGEN_OUTPUT_DIR}/html 
        DESTINATION ${CMAKE_INSTALL_DOCDIR}
        OPTIONAL
)