cmake_minimum_required(VERSION 3.20)

# Set project name and version
project(CppTemplate
    VERSION 1.0.0
    DESCRIPTION "A production-quality C++ template with multiple apps and libraries"
    LANGUAGES CXX
)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set default build type to Release if not specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Export compile commands for clang-tidy
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Add custom CMake modules path
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# Global options
option(BUILD_TESTS "Build tests" ON)
option(BUILD_DOCS "Build documentation" OFF)
option(BUILD_EXAMPLES "Build example applications" ON)
option(ENABLE_CLANG_TIDY "Enable clang-tidy" OFF)
option(ENABLE_SANITIZERS "Enable sanitizers" OFF)

# Library options
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)
option(BUILD_CORE_LIB "Build core library" ON)
option(BUILD_MATH_LIB "Build math library" ON)
option(BUILD_UTILS_LIB "Build utilities library" ON)
option(BUILD_NETWORK_LIB "Build network library" ON)

# Application options
option(BUILD_MAIN_APP "Build main application" ON)
option(BUILD_CLI_APP "Build CLI application" ON)
option(BUILD_SERVER_APP "Build server application" ON)

# Compiler-specific options
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-Wall -Wextra -Wpedantic -Werror)
    
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        add_compile_options(-g -O0)
    endif()
    
    if(CMAKE_BUILD_TYPE STREQUAL "Release")
        add_compile_options(-O3 -DNDEBUG)
    endif()
endif()

# Enable sanitizers if requested
if(ENABLE_SANITIZERS AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-fsanitize=address -fsanitize=undefined)
    add_link_options(-fsanitize=address -fsanitize=undefined)
endif()

# Find dependencies
find_package(fmt REQUIRED)
find_package(spdlog REQUIRED)

# Conditionally find network dependencies
if(BUILD_NETWORK_LIB OR BUILD_SERVER_APP)
    find_package(Threads REQUIRED)
endif()

# Add subdirectories for libraries
add_subdirectory(libs)

# Add subdirectories for applications
if(BUILD_MAIN_APP OR BUILD_CLI_APP OR BUILD_SERVER_APP OR BUILD_EXAMPLES)
    add_subdirectory(apps)
endif()

# Add examples
if(BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

# Add tests
if(BUILD_TESTS)
    find_package(GTest REQUIRED)
    enable_testing()
    add_subdirectory(tests)
endif()

# Add documentation
if(BUILD_DOCS)
    find_package(Doxygen)
    if(DOXYGEN_FOUND)
        add_subdirectory(docs)
    endif()
endif()

# Clang-tidy integration
if(ENABLE_CLANG_TIDY)
    find_program(CLANG_TIDY_EXE NAMES "clang-tidy")
    if(CLANG_TIDY_EXE)
        set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_EXE}")
    endif()
endif()

# Install configuration
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

# Configure package config file
configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/CppTemplateConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/CppTemplateConfig.cmake"
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/CppTemplate
)

# Create version file
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/CppTemplateConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

# Install targets and config files
install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/CppTemplateConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/CppTemplateConfigVersion.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/CppTemplate
)

# Print configuration summary
message(STATUS "")
message(STATUS "CppTemplate Configuration Summary:")
message(STATUS "  Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "  C++ standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "  Shared libraries: ${BUILD_SHARED_LIBS}")
message(STATUS "")
message(STATUS "Libraries:")
message(STATUS "  Core library: ${BUILD_CORE_LIB}")
message(STATUS "  Math library: ${BUILD_MATH_LIB}")
message(STATUS "  Utils library: ${BUILD_UTILS_LIB}")
message(STATUS "  Network library: ${BUILD_NETWORK_LIB}")
message(STATUS "")
message(STATUS "Applications:")
message(STATUS "  Main app: ${BUILD_MAIN_APP}")
message(STATUS "  CLI app: ${BUILD_CLI_APP}")
message(STATUS "  Server app: ${BUILD_SERVER_APP}")
message(STATUS "")
message(STATUS "Optional components:")
message(STATUS "  Tests: ${BUILD_TESTS}")
message(STATUS "  Documentation: ${BUILD_DOCS}")
message(STATUS "  Examples: ${BUILD_EXAMPLES}")
message(STATUS "  Clang-tidy: ${ENABLE_CLANG_TIDY}")
message(STATUS "  Sanitizers: ${ENABLE_SANITIZERS}")
message(STATUS "")