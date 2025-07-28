# Tests directory CMakeLists.txt
# Organized by library for better structure

# Test executable with all tests
add_executable(${PROJECT_NAME}_tests
    # Core library tests
    core/test_logger.cpp
    core/test_config.cpp
    core/test_exception.cpp
    
    # Math library tests  
    math/test_calculator.cpp
    math/test_matrix.cpp
    math/test_statistics.cpp
    
    # Utils library tests
    utils/test_string_utils.cpp
    utils/test_file_utils.cpp
    utils/test_time_utils.cpp
    
    # Integration tests
    integration/test_multi_library.cpp
    integration/test_performance.cpp
)

# Set target properties
target_compile_features(${PROJECT_NAME}_tests PRIVATE cxx_std_20)

# Include directories for tests
target_include_directories(${PROJECT_NAME}_tests
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/libs/core/include
        ${CMAKE_SOURCE_DIR}/libs/math/include
        ${CMAKE_SOURCE_DIR}/libs/utils/include
        ${CMAKE_SOURCE_DIR}/libs/network/include
)

# Link test dependencies - only link libraries that are enabled
set(TEST_LIBRARIES "")

if(BUILD_CORE_LIB)
    list(APPEND TEST_LIBRARIES CppTemplate::core)
endif()

if(BUILD_MATH_LIB)
    list(APPEND TEST_LIBRARIES CppTemplate::math)
endif()

if(BUILD_UTILS_LIB)
    list(APPEND TEST_LIBRARIES CppTemplate::utils)
endif()

if(BUILD_NETWORK_LIB)
    list(APPEND TEST_LIBRARIES CppTemplate::network)
endif()

target_link_libraries(${PROJECT_NAME}_tests
    PRIVATE
        ${TEST_LIBRARIES}
        GTest::gtest
        GTest::gtest_main
        GTest::gmock
)

# Discover tests
include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}_tests
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
)

# Add custom target for running tests with verbose output
add_custom_target(test_verbose
    COMMAND ${CMAKE_CTEST_COMMAND} --verbose
    DEPENDS ${PROJECT_NAME}_tests
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)

# Add library-specific test targets
if(BUILD_CORE_LIB)
    add_custom_target(test_core
        COMMAND ${CMAKE_CTEST_COMMAND} -R "Core" --verbose
        DEPENDS ${PROJECT_NAME}_tests
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    )
endif()

if(BUILD_MATH_LIB)
    add_custom_target(test_math
        COMMAND ${CMAKE_CTEST_COMMAND} -R "Math" --verbose
        DEPENDS ${PROJECT_NAME}_tests
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    )
endif()

if(BUILD_UTILS_LIB)
    add_custom_target(test_utils
        COMMAND ${CMAKE_CTEST_COMMAND} -R "Utils" --verbose
        DEPENDS ${PROJECT_NAME}_tests
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    )
endif()

# Integration test target
add_custom_target(test_integration
    COMMAND ${CMAKE_CTEST_COMMAND} -R "Integration" --verbose
    DEPENDS ${PROJECT_NAME}_tests
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)