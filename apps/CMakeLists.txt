# Applications directory CMakeLists.txt
# This file manages the building of all applications in the project

# Main application - the primary application
if(BUILD_MAIN_APP)
    add_subdirectory(main)
endif()

# CLI application - command-line interface tool
if(BUILD_CLI_APP)
    add_subdirectory(cli)
endif()

# Server application - network server
if(BUILD_SERVER_APP)
    add_subdirectory(server)
endif()

# Set common properties for all applications
function(setup_application target_name)
    # Set executable properties
    set_target_properties(${target_name} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
        OUTPUT_NAME "${target_name}"
    )
    
    # Enable debugging symbols for Debug builds
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        target_compile_definitions(${target_name} PRIVATE DEBUG_BUILD)
    endif()
    
    # Set optimization for Release builds
    if(CMAKE_BUILD_TYPE STREQUAL "Release")
        target_compile_definitions(${target_name} PRIVATE RELEASE_BUILD)
    endif()
    
    # Install the application
    install(TARGETS ${target_name}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    )
endfunction()

# Create a convenience script for running applications
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/run_app.sh.in
    ${CMAKE_BINARY_DIR}/run_app.sh
    @ONLY
)

# Make the script executable
if(UNIX)
    file(COPY ${CMAKE_BINARY_DIR}/run_app.sh
         DESTINATION ${CMAKE_BINARY_DIR}
         FILE_PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE)
endif()