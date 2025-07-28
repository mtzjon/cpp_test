# Server application
add_executable(cpp_template_server
    src/main.cpp
    src/server.cpp
    src/handlers.cpp
    src/middleware.cpp
)

# Set target properties
target_compile_features(cpp_template_server PRIVATE cxx_std_20)

# Include directories
target_include_directories(cpp_template_server
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Link dependencies
target_link_libraries(cpp_template_server
    PRIVATE
        CppTemplate::core
        CppTemplate::utils
        CppTemplate::network
        Threads::Threads
)

# Apply common application setup
setup_application(cpp_template_server)

# Add version information
target_compile_definitions(cpp_template_server
    PRIVATE
        APP_VERSION="${PROJECT_VERSION}"
        APP_NAME="CppTemplate Server"
)