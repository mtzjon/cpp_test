# CLI application
add_executable(cpp_template_cli
    src/main.cpp
    src/cli_parser.cpp
    src/commands.cpp
)

# Set target properties
target_compile_features(cpp_template_cli PRIVATE cxx_std_20)

# Include directories
target_include_directories(cpp_template_cli
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Link dependencies
target_link_libraries(cpp_template_cli
    PRIVATE
        CppTemplate::core
        CppTemplate::math
        CppTemplate::utils
)

# Apply common application setup
setup_application(cpp_template_cli)

# Add version information
target_compile_definitions(cpp_template_cli
    PRIVATE
        APP_VERSION="${PROJECT_VERSION}"
        APP_NAME="CppTemplate CLI"
)