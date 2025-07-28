# Libraries directory CMakeLists.txt
# This file manages the building of all libraries in the project

# Core library - fundamental functionality
if(BUILD_CORE_LIB)
    add_subdirectory(core)
endif()

# Math library - mathematical operations and algorithms
if(BUILD_MATH_LIB)
    add_subdirectory(math)
endif()

# Utils library - utility functions and helpers
if(BUILD_UTILS_LIB)
    add_subdirectory(utils)
endif()

# Network library - networking functionality
if(BUILD_NETWORK_LIB)
    add_subdirectory(network)
endif()

# Create a convenience target that depends on all libraries
set(ALL_LIBRARIES "")

if(BUILD_CORE_LIB)
    list(APPEND ALL_LIBRARIES CppTemplate::core)
endif()

if(BUILD_MATH_LIB)
    list(APPEND ALL_LIBRARIES CppTemplate::math)
endif()

if(BUILD_UTILS_LIB)
    list(APPEND ALL_LIBRARIES CppTemplate::utils)
endif()

if(BUILD_NETWORK_LIB)
    list(APPEND ALL_LIBRARIES CppTemplate::network)
endif()

# Create an interface target that links all libraries
if(ALL_LIBRARIES)
    add_library(CppTemplate_all INTERFACE)
    add_library(CppTemplate::all ALIAS CppTemplate_all)
    target_link_libraries(CppTemplate_all INTERFACE ${ALL_LIBRARIES})
    
    # Install the convenience target
    install(TARGETS CppTemplate_all
        EXPORT CppTemplateTargets
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    )
endif()