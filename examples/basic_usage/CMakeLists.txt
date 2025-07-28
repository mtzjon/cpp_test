# Basic usage example
add_executable(basic_example
    simple_calculator.cpp
)

target_compile_features(basic_example PRIVATE cxx_std_20)

target_link_libraries(basic_example
    PRIVATE
        CppTemplate::core
        CppTemplate::math
)

# Set output directory
set_target_properties(basic_example PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/examples
)