# Library target
add_library(${PROJECT_NAME}_lib
    core/calculator.cpp
    core/logger.cpp
    utils/string_utils.cpp
)

# Add alias for consistent naming
add_library(${PROJECT_NAME}::lib ALIAS ${PROJECT_NAME}_lib)

# Set target properties
target_compile_features(${PROJECT_NAME}_lib PUBLIC cxx_std_20)

# Include directories
target_include_directories(${PROJECT_NAME}_lib
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

# Link dependencies
target_link_libraries(${PROJECT_NAME}_lib
    PUBLIC
        fmt::fmt
        spdlog::spdlog
)

# Executable target
add_executable(${PROJECT_NAME}
    main.cpp
)

# Link the library
target_link_libraries(${PROJECT_NAME}
    PRIVATE
        ${PROJECT_NAME}::lib
)

# Set executable properties
set_target_properties(${PROJECT_NAME} PROPERTIES
    OUTPUT_NAME "cpp-template"
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# Install targets
install(TARGETS ${PROJECT_NAME}_lib ${PROJECT_NAME}
    EXPORT ${PROJECT_NAME}Targets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

# Install headers
install(DIRECTORY core/ utils/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}
    FILES_MATCHING PATTERN "*.hpp"
)

# Export targets
install(EXPORT ${PROJECT_NAME}Targets
    FILE ${PROJECT_NAME}Targets.cmake
    NAMESPACE ${PROJECT_NAME}::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)