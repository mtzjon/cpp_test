# Test executable
add_executable(${PROJECT_NAME}_tests
    test_calculator.cpp
    test_string_utils.cpp
    test_logger.cpp
)

# Link test dependencies
target_link_libraries(${PROJECT_NAME}_tests
    PRIVATE
        ${PROJECT_NAME}::lib
        GTest::gtest
        GTest::gtest_main
        GTest::gmock
)

# Set test properties
target_compile_features(${PROJECT_NAME}_tests PRIVATE cxx_std_20)

# Include directories for tests
target_include_directories(${PROJECT_NAME}_tests
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/src
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