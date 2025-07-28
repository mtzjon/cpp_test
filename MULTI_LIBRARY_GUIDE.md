# Multi-Library C++ Template Guide

This guide explains how to work with the multi-library and multi-application structure of the CppTemplate project.

## 📁 Project Structure

```
cpp-template/
├── libs/                           # Libraries
│   ├── core/                      # Core library (fundamental functionality)
│   │   ├── include/cpptemplate/core/
│   │   │   ├── logger.hpp
│   │   │   ├── config.hpp
│   │   │   └── exception.hpp
│   │   ├── src/
│   │   │   ├── logger.cpp
│   │   │   ├── config.cpp
│   │   │   └── exception.cpp
│   │   └── CMakeLists.txt
│   ├── math/                      # Math library (mathematical operations)
│   │   ├── include/cpptemplate/math/
│   │   │   ├── calculator.hpp
│   │   │   ├── matrix.hpp
│   │   │   ├── statistics.hpp
│   │   │   └── geometry.hpp
│   │   ├── src/
│   │   │   ├── calculator.cpp
│   │   │   ├── matrix.cpp
│   │   │   ├── statistics.cpp
│   │   │   └── geometry.cpp
│   │   └── CMakeLists.txt
│   ├── utils/                     # Utils library (utility functions)
│   │   ├── include/cpptemplate/utils/
│   │   │   ├── string_utils.hpp
│   │   │   ├── file_utils.hpp
│   │   │   ├── time_utils.hpp
│   │   │   └── crypto_utils.hpp
│   │   ├── src/
│   │   │   ├── string_utils.cpp
│   │   │   ├── file_utils.cpp
│   │   │   ├── time_utils.cpp
│   │   │   └── crypto_utils.cpp
│   │   └── CMakeLists.txt
│   └── network/                   # Network library (networking functionality)
│       ├── include/cpptemplate/network/
│       │   ├── tcp_client.hpp
│       │   ├── tcp_server.hpp
│       │   ├── http_client.hpp
│       │   └── websocket.hpp
│       ├── src/
│       │   ├── tcp_client.cpp
│       │   ├── tcp_server.cpp
│       │   ├── http_client.cpp
│       │   └── websocket.cpp
│       └── CMakeLists.txt
├── apps/                          # Applications
│   ├── main/                      # Main application
│   │   ├── src/
│   │   │   ├── main.cpp
│   │   │   └── application.cpp
│   │   └── CMakeLists.txt
│   ├── cli/                       # CLI application
│   │   ├── src/
│   │   │   ├── main.cpp
│   │   │   ├── cli_parser.cpp
│   │   │   └── commands.cpp
│   │   └── CMakeLists.txt
│   └── server/                    # Server application
│       ├── src/
│       │   ├── main.cpp
│       │   ├── server.cpp
│       │   ├── handlers.cpp
│       │   └── middleware.cpp
│       └── CMakeLists.txt
└── examples/                      # Example applications
    └── (example projects)
```

## 🛠️ Building Libraries and Applications

### Build Everything (Default)

```bash
./scripts/build.sh
```

This builds all libraries and applications by default.

### Selective Building

#### Build Only Specific Libraries

```bash
# Build only core and math libraries
./scripts/build.sh --disable-utils --disable-network

# Build only utils library
./scripts/build.sh --disable-core --disable-math --disable-network
```

#### Build Only Specific Applications

```bash
# Build only the main application
./scripts/build.sh --disable-cli --disable-server

# Build only the server application
./scripts/build.sh --disable-main --disable-cli
```

#### Shared vs Static Libraries

```bash
# Build shared libraries (.so/.dll)
./scripts/build.sh --shared

# Build static libraries (.a/.lib) - default
./scripts/build.sh --static
```

### Advanced Build Configurations

```bash
# Debug build with shared libraries and only core+math
./scripts/build.sh -t Debug --shared --disable-utils --disable-network --disable-server

# Release build with static libraries and no applications
./scripts/build.sh -t Release --static --disable-main --disable-cli --disable-server

# Build with sanitizers for development
./scripts/build.sh -t Debug --sanitizers --disable-network --disable-server
```

## 📚 Library Dependencies

The libraries have the following dependency hierarchy:

```
core (base library)
├── math (depends on core)
├── utils (depends on core)
└── network (depends on core + utils)
```

### Dependency Rules

1. **Core library** is the foundation - other libraries depend on it
2. **Math library** only depends on core
3. **Utils library** only depends on core
4. **Network library** depends on core and utils
5. Applications can depend on any combination of libraries

## 🎯 Using Libraries in Your Code

### Including Headers

```cpp
// Core library
#include "cpptemplate/core/logger.hpp"
#include "cpptemplate/core/config.hpp"
#include "cpptemplate/core/exception.hpp"

// Math library
#include "cpptemplate/math/calculator.hpp"
#include "cpptemplate/math/matrix.hpp"

// Utils library
#include "cpptemplate/utils/string_utils.hpp"
#include "cpptemplate/utils/file_utils.hpp"

// Network library
#include "cpptemplate/network/tcp_client.hpp"
#include "cpptemplate/network/http_client.hpp"
```

### Linking Libraries in CMake

```cmake
# Link specific libraries
target_link_libraries(your_target
    PRIVATE
        CppTemplate::core
        CppTemplate::math
        CppTemplate::utils
)

# Link all libraries at once
target_link_libraries(your_target
    PRIVATE
        CppTemplate::all
)
```

### Namespace Structure

All code is organized under the `cpptemplate` namespace:

```cpp
// Core functionality
auto logger = cpptemplate::core::Logger::create("MyApp");

// Math operations
cpptemplate::math::Calculator calc;
double result = calc.add(1.0, 2.0);

// String utilities
std::string trimmed = cpptemplate::utils::trim("  hello  ");

// Network operations (when implemented)
cpptemplate::network::TcpClient client;
```

## 🔧 Adding New Libraries

### 1. Create Library Structure

```bash
mkdir -p libs/mylibrary/{include/cpptemplate/mylibrary,src}
```

### 2. Create CMakeLists.txt

```cmake
# libs/mylibrary/CMakeLists.txt
add_library(CppTemplate_mylibrary
    src/myclass.cpp
)

add_library(CppTemplate::mylibrary ALIAS CppTemplate_mylibrary)

target_compile_features(CppTemplate_mylibrary PUBLIC cxx_std_20)

target_include_directories(CppTemplate_mylibrary
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_link_libraries(CppTemplate_mylibrary
    PUBLIC
        CppTemplate::core  # or other dependencies
)

# Set library properties
set_target_properties(CppTemplate_mylibrary PROPERTIES
    OUTPUT_NAME "cpptemplate_mylibrary"
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
    POSITION_INDEPENDENT_CODE ON
)

# Install targets
install(TARGETS CppTemplate_mylibrary
    EXPORT CppTemplateTargets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(DIRECTORY include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    FILES_MATCHING PATTERN "*.hpp"
)
```

### 3. Update Main CMakeLists.txt

Add a new option:

```cmake
option(BUILD_MYLIBRARY_LIB "Build my library" ON)
```

### 4. Update libs/CMakeLists.txt

```cmake
if(BUILD_MYLIBRARY_LIB)
    add_subdirectory(mylibrary)
endif()

# Add to convenience target
if(BUILD_MYLIBRARY_LIB)
    list(APPEND ALL_LIBRARIES CppTemplate::mylibrary)
endif()
```

### 5. Update Build Script

Add new options to `scripts/build.sh`:

```bash
BUILD_MYLIBRARY_LIB="ON"

# Add to argument parsing
--disable-mylibrary)
    BUILD_MYLIBRARY_LIB="OFF"
    shift
    ;;

# Add to cmake command
-DBUILD_MYLIBRARY_LIB="$BUILD_MYLIBRARY_LIB" \
```

## 🎯 Adding New Applications

### 1. Create Application Structure

```bash
mkdir -p apps/myapp/src
```

### 2. Create Application CMakeLists.txt

```cmake
# apps/myapp/CMakeLists.txt
add_executable(cpp_template_myapp
    src/main.cpp
    src/myapp.cpp
)

target_compile_features(cpp_template_myapp PRIVATE cxx_std_20)

target_link_libraries(cpp_template_myapp
    PRIVATE
        CppTemplate::core
        CppTemplate::utils
        # Add other libraries as needed
)

setup_application(cpp_template_myapp)

target_compile_definitions(cpp_template_myapp
    PRIVATE
        APP_VERSION="${PROJECT_VERSION}"
        APP_NAME="My Application"
)
```

### 3. Update Main CMakeLists.txt

Add new option:

```cmake
option(BUILD_MYAPP_APP "Build my application" ON)
```

### 4. Update apps/CMakeLists.txt

```cmake
if(BUILD_MYAPP_APP)
    add_subdirectory(myapp)
endif()
```

## 📦 Export Macros for Dynamic Libraries

Each library includes export macros for Windows DLL support:

```cpp
// In your header file
#ifdef CPPTEMPLATE_MYLIBRARY_STATIC
    #define CPPTEMPLATE_MYLIBRARY_API
#else
    #ifdef CPPTEMPLATE_MYLIBRARY_BUILDING
        #if defined(_WIN32) || defined(_WIN64)
            #define CPPTEMPLATE_MYLIBRARY_API __declspec(dllexport)
        #else
            #define CPPTEMPLATE_MYLIBRARY_API __attribute__((visibility("default")))
        #endif
    #else
        #if defined(_WIN32) || defined(_WIN64)
            #define CPPTEMPLATE_MYLIBRARY_API __declspec(dllimport)
        #else
            #define CPPTEMPLATE_MYLIBRARY_API
        #endif
    #endif
#endif

// Use in class declarations
class CPPTEMPLATE_MYLIBRARY_API MyClass {
    // ...
};

// Use in function declarations
CPPTEMPLATE_MYLIBRARY_API void my_function();
```

## 🧪 Testing Multiple Libraries

Tests are organized by library:

```bash
# Run tests for specific libraries
./scripts/test.sh --filter "*Core*"
./scripts/test.sh --filter "*Math*"
./scripts/test.sh --filter "*Utils*"

# Run all tests
./scripts/test.sh
```

## 📋 CMake Configuration Summary

After configuration, CMake displays a summary:

```
CppTemplate Configuration Summary:
  Build type: Release
  C++ standard: 20
  Shared libraries: OFF

Libraries:
  Core library: ON
  Math library: ON
  Utils library: ON
  Network library: ON

Applications:
  Main app: ON
  CLI app: ON
  Server app: ON

Optional components:
  Tests: ON
  Documentation: OFF
  Examples: ON
  Clang-tidy: OFF
  Sanitizers: OFF
```

## 🚀 Best Practices

### Library Design

1. **Single Responsibility**: Each library should have a clear, focused purpose
2. **Minimal Dependencies**: Keep inter-library dependencies minimal
3. **Clean Interfaces**: Use well-defined public APIs
4. **Export Control**: Use export macros for Windows DLL compatibility
5. **Namespace Organization**: Use consistent namespace hierarchy

### Build Configuration

1. **Selective Building**: Allow disabling unused components
2. **Shared/Static Choice**: Support both shared and static builds
3. **Cross-Platform**: Ensure builds work on all target platforms
4. **Version Management**: Use consistent versioning across all libraries

### Application Structure

1. **Library Reuse**: Applications should primarily use library functionality
2. **Clean Separation**: Keep application logic separate from library code
3. **Configuration**: Use consistent configuration patterns
4. **Error Handling**: Implement proper error handling and logging

This multi-library structure provides flexibility and modularity while maintaining ease of use and clear organization.