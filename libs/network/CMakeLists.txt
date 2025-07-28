# Network library - networking functionality
add_library(CppTemplate_network
    src/tcp_client.cpp
    src/tcp_server.cpp
    src/http_client.cpp
    src/websocket.cpp
)

# Add alias for consistent naming
add_library(CppTemplate::network ALIAS CppTemplate_network)

# Set target properties
target_compile_features(CppTemplate_network PUBLIC cxx_std_20)

# Include directories
target_include_directories(CppTemplate_network
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Link dependencies
target_link_libraries(CppTemplate_network
    PUBLIC
        CppTemplate::core
        CppTemplate::utils
        Threads::Threads
    PRIVATE
        # Platform-specific networking libraries
        $<$<PLATFORM_ID:Windows>:ws2_32>
        $<$<PLATFORM_ID:Windows>:wsock32>
)

# Set library properties
set_target_properties(CppTemplate_network PROPERTIES
    OUTPUT_NAME "cpptemplate_network"
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
    POSITION_INDEPENDENT_CODE ON
)

# Define preprocessor macros
target_compile_definitions(CppTemplate_network
    PRIVATE
        CPPTEMPLATE_NETWORK_BUILDING
    PUBLIC
        $<$<NOT:$<BOOL:${BUILD_SHARED_LIBS}>>:CPPTEMPLATE_NETWORK_STATIC>
        $<$<PLATFORM_ID:Windows>:WIN32_LEAN_AND_MEAN>
        $<$<PLATFORM_ID:Windows>:NOMINMAX>
)

# Install targets
install(TARGETS CppTemplate_network
    EXPORT CppTemplateTargets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

# Install headers
install(DIRECTORY include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    FILES_MATCHING PATTERN "*.hpp"
)