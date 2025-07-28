# Math library - mathematical operations and algorithms
add_library(CppTemplate_math
    src/calculator.cpp
    src/matrix.cpp
    src/statistics.cpp
    src/geometry.cpp
)

# Add alias for consistent naming
add_library(CppTemplate::math ALIAS CppTemplate_math)

# Set target properties
target_compile_features(CppTemplate_math PUBLIC cxx_std_20)

# Include directories
target_include_directories(CppTemplate_math
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Link dependencies
target_link_libraries(CppTemplate_math
    PUBLIC
        CppTemplate::core
    PRIVATE
        # Math library typically doesn't need external dependencies
        # Add here if needed: Eigen3::Eigen, BLAS::BLAS, etc.
)

# Set library properties
set_target_properties(CppTemplate_math PROPERTIES
    OUTPUT_NAME "cpptemplate_math"
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
    POSITION_INDEPENDENT_CODE ON
)

# Define preprocessor macros
target_compile_definitions(CppTemplate_math
    PRIVATE
        CPPTEMPLATE_MATH_BUILDING
    PUBLIC
        $<$<NOT:$<BOOL:${BUILD_SHARED_LIBS}>>:CPPTEMPLATE_MATH_STATIC>
)

# Install targets
install(TARGETS CppTemplate_math
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