# Examples directory CMakeLists.txt
# Demonstrates how to use the libraries

# Basic usage example
if(BUILD_CORE_LIB AND BUILD_MATH_LIB)
    add_subdirectory(basic_usage)
endif()

# Advanced features example
if(BUILD_UTILS_LIB AND BUILD_NETWORK_LIB)
    add_subdirectory(advanced_features)
endif()

# Tutorial examples
add_subdirectory(tutorials)