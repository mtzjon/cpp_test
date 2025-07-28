# Main application
add_executable(cpp_template_main
    src/main.cpp
    src/application.cpp
)

# Set target properties
target_compile_features(cpp_template_main PRIVATE cxx_std_20)

# Include directories
target_include_directories(cpp_template_main
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Link dependencies
target_link_libraries(cpp_template_main
    PRIVATE
        CppTemplate::core
        CppTemplate::math
        CppTemplate::utils
)

# Apply common application setup
setup_application(cpp_template_main)

# Add version information
target_compile_definitions(cpp_template_main
    PRIVATE
        APP_VERSION="${PROJECT_VERSION}"
        APP_NAME="CppTemplate Main"
)