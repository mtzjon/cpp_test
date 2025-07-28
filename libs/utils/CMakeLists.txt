# Utils library - utility functions and helpers
add_library(CppTemplate_utils
    src/string_utils.cpp
    src/file_utils.cpp
    src/time_utils.cpp
    src/crypto_utils.cpp
)

# Add alias for consistent naming
add_library(CppTemplate::utils ALIAS CppTemplate_utils)

# Set target properties
target_compile_features(CppTemplate_utils PUBLIC cxx_std_20)

# Include directories
target_include_directories(CppTemplate_utils
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Link dependencies
target_link_libraries(CppTemplate_utils
    PUBLIC
        CppTemplate::core
    PRIVATE
        # Add filesystem library if needed
        $<$<AND:$<CXX_COMPILER_ID:GNU>,$<VERSION_LESS:$<CXX_COMPILER_VERSION>,9.0>>:stdc++fs>
)

# Set library properties
set_target_properties(CppTemplate_utils PROPERTIES
    OUTPUT_NAME "cpptemplate_utils"
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
    POSITION_INDEPENDENT_CODE ON
)

# Define preprocessor macros
target_compile_definitions(CppTemplate_utils
    PRIVATE
        CPPTEMPLATE_UTILS_BUILDING
    PUBLIC
        $<$<NOT:$<BOOL:${BUILD_SHARED_LIBS}>>:CPPTEMPLATE_UTILS_STATIC>
)

# Install targets
install(TARGETS CppTemplate_utils
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