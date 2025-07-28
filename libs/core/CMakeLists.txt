# Core library - fundamental functionality
add_library(CppTemplate_core
    src/logger.cpp
    src/config.cpp
    src/exception.cpp
)

# Add alias for consistent naming
add_library(CppTemplate::core ALIAS CppTemplate_core)

# Set target properties
target_compile_features(CppTemplate_core PUBLIC cxx_std_20)

# Include directories
target_include_directories(CppTemplate_core
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Link dependencies
target_link_libraries(CppTemplate_core
    PUBLIC
        spdlog::spdlog
        fmt::fmt
)

# Set library properties
set_target_properties(CppTemplate_core PROPERTIES
    OUTPUT_NAME "cpptemplate_core"
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
    POSITION_INDEPENDENT_CODE ON
)

# Define preprocessor macros
target_compile_definitions(CppTemplate_core
    PRIVATE
        CPPTEMPLATE_CORE_BUILDING
    PUBLIC
        $<$<NOT:$<BOOL:${BUILD_SHARED_LIBS}>>:CPPTEMPLATE_CORE_STATIC>
)

# Install targets
install(TARGETS CppTemplate_core
    EXPORT CppTemplateTargets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

# Install headers
install(DIRECTORY include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    FILES_MATCHING PATTERN "*.hpp"
)