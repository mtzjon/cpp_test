# C++ Multi-Library Project Structure Guide

This document explains the optimal directory structure for multi-library C++ projects and what each directory should contain.

## 📁 **Recommended Structure**

```
cpp-template/                          # Project root
├── libs/                             # 📚 All reusable libraries
│   ├── core/                         # Core library (foundation)
│   │   ├── include/cpptemplate/core/ # Public headers
│   │   │   ├── logger.hpp
│   │   │   ├── config.hpp
│   │   │   └── exception.hpp
│   │   ├── src/                      # Implementation files
│   │   │   ├── logger.cpp
│   │   │   ├── config.cpp
│   │   │   └── exception.cpp
│   │   └── CMakeLists.txt           # Library build config
│   ├── math/                        # Math library
│   ├── utils/                       # Utilities library
│   └── network/                     # Network library
├── apps/                            # 🎯 Executable applications
│   ├── main/                        # Main application
│   ├── cli/                         # CLI tool
│   └── server/                      # Server application
├── examples/                        # 📖 Example usage (optional)
│   ├── basic_usage/
│   ├── advanced_features/
│   └── tutorials/
├── tests/                           # 🧪 Tests (organized by library)
│   ├── core/                        # Tests for core library
│   ├── math/                        # Tests for math library
│   ├── utils/                       # Tests for utils library
│   ├── integration/                 # Integration tests
│   └── CMakeLists.txt
├── docs/                            # 📚 Documentation
│   ├── api/                         # API documentation
│   ├── guides/                      # User guides
│   └── CMakeLists.txt
├── cmake/                           # 🔧 CMake modules and scripts
├── scripts/                         # 🛠️ Build and utility scripts
├── .devcontainer/                   # 🐳 Development container
├── .github/                         # 🚀 CI/CD workflows
└── CMakeLists.txt                   # Root build configuration
```

## 🚫 **What NOT to Use (Anti-patterns)**

### ❌ Root `src/` Directory
```
❌ BAD:
cpp-template/
├── src/           # Don't use root src in multi-library projects
│   ├── lib1/
│   ├── lib2/
│   └── main.cpp
└── include/       # Don't use root include in multi-library projects
    ├── lib1/
    └── lib2/
```

**Why this is bad:**
- Mixes libraries and applications
- Makes dependency management unclear
- Complicates CMake configuration
- Harder to package individual libraries
- Confuses namespace organization

## ✅ **Directory Purpose and Guidelines**

### 📚 `libs/` - Reusable Libraries

**Purpose:** Contains all reusable library code that could be:
- Used by multiple applications
- Packaged separately
- Distributed independently
- Reused in other projects

**Structure per library:**
```
libs/mylibrary/
├── include/cpptemplate/mylibrary/    # Public API headers
│   ├── public_class.hpp              # Public interface
│   └── public_functions.hpp
├── src/                              # Implementation
│   ├── public_class.cpp              # Public API implementation
│   ├── private_helper.cpp            # Private implementation
│   └── private_helper.hpp            # Private headers (internal)
└── CMakeLists.txt                    # Library build configuration
```

**Guidelines:**
- Each library is self-contained
- Public headers go in `include/cpptemplate/libraryname/`
- Private headers and implementation in `src/`
- Use consistent naming: `libs/name/include/cpptemplate/name/`
- Each library has its own CMakeLists.txt

### 🎯 `apps/` - Executable Applications

**Purpose:** Contains applications that use the libraries to provide end-user functionality.

**Structure per application:**
```
apps/myapp/
├── src/                              # Application source
│   ├── main.cpp                      # Entry point
│   ├── application.cpp               # Application logic
│   └── config.cpp                    # App-specific configuration
├── include/                          # Private headers (optional)
│   └── application.hpp
├── resources/                        # App resources (optional)
│   ├── config.json
│   └── data/
└── CMakeLists.txt                    # Application build config
```

**Guidelines:**
- Applications depend on libraries, not vice versa
- Keep application-specific code here
- Don't put reusable code in apps (move to libs instead)
- Each app is an independent executable

### 📖 `examples/` - Example Code (Optional)

**Purpose:** Demonstrates how to use the libraries.

**Structure:**
```
examples/
├── basic_usage/
│   ├── simple_calculator.cpp
│   └── CMakeLists.txt
├── advanced_features/
│   ├── network_client.cpp
│   └── CMakeLists.txt
└── tutorials/
    ├── getting_started.cpp
    └── README.md
```

**Guidelines:**
- Small, focused examples
- Well-documented code
- Independent from main applications
- Can be built separately

### 🧪 `tests/` - Test Code

**Purpose:** Contains all test code organized by what's being tested.

**Structure:**
```
tests/
├── core/                             # Core library tests
│   ├── test_logger.cpp
│   └── test_config.cpp
├── math/                             # Math library tests
│   ├── test_calculator.cpp
│   └── test_matrix.cpp
├── utils/                            # Utils library tests
├── integration/                      # Cross-library tests
│   ├── test_app_integration.cpp
│   └── test_performance.cpp
├── fixtures/                         # Test data and fixtures
│   ├── test_data.json
│   └── sample_files/
└── CMakeLists.txt
```

**Guidelines:**
- Mirror the library structure
- Keep integration tests separate
- Use descriptive test names
- Include test fixtures and data

## 🔧 **CMake Integration**

### Root CMakeLists.txt Structure
```cmake
cmake_minimum_required(VERSION 3.20)
project(CppTemplate)

# Options for what to build
option(BUILD_CORE_LIB "Build core library" ON)
option(BUILD_MATH_LIB "Build math library" ON)
option(BUILD_MAIN_APP "Build main application" ON)
option(BUILD_TESTS "Build tests" ON)
option(BUILD_EXAMPLES "Build examples" OFF)

# Add subdirectories based on options
add_subdirectory(libs)              # Always build enabled libraries

if(BUILD_MAIN_APP OR BUILD_CLI_APP OR BUILD_SERVER_APP)
    add_subdirectory(apps)
endif()

if(BUILD_TESTS)
    add_subdirectory(tests)
endif()

if(BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()
```

### Library CMakeLists.txt Example
```cmake
# libs/core/CMakeLists.txt
add_library(CppTemplate_core
    src/logger.cpp
    src/config.cpp
)

add_library(CppTemplate::core ALIAS CppTemplate_core)

target_include_directories(CppTemplate_core
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_link_libraries(CppTemplate_core
    PUBLIC
        spdlog::spdlog
        fmt::fmt
)
```

### Application CMakeLists.txt Example
```cmake
# apps/main/CMakeLists.txt
add_executable(cpp_template_main
    src/main.cpp
    src/application.cpp
)

target_link_libraries(cpp_template_main
    PRIVATE
        CppTemplate::core
        CppTemplate::math
        CppTemplate::utils
)
```

## 🎯 **When to Use Each Structure**

### Use `libs/` When:
- Code will be reused across multiple applications
- You want to distribute libraries separately
- Code provides a well-defined API
- Functionality is independent and self-contained
- You want to enable/disable components selectively

### Use `apps/` When:
- Creating end-user applications
- Building command-line tools
- Creating servers or services
- Code is application-specific and not reusable

### Use `examples/` When:
- Demonstrating library usage
- Providing tutorial code
- Creating minimal working examples
- Documentation needs code samples

## 🔄 **Migration from Single-Library Structure**

If you have an existing single-library structure:

### Before (Single Library):
```
src/
├── main.cpp
├── calculator.cpp
├── logger.cpp
└── utils.cpp
include/
├── calculator.hpp
├── logger.hpp
└── utils.hpp
```

### After (Multi-Library):
```
libs/
├── math/
│   ├── include/cpptemplate/math/calculator.hpp
│   └── src/calculator.cpp
├── core/
│   ├── include/cpptemplate/core/logger.hpp
│   └── src/logger.cpp
└── utils/
    ├── include/cpptemplate/utils/helpers.hpp
    └── src/helpers.cpp
apps/
└── main/
    └── src/main.cpp
```

## 🛠️ **Tools and Scripts**

Create helper scripts for common operations:

```bash
# scripts/create-library.sh
#!/bin/bash
LIBRARY_NAME=$1
mkdir -p libs/$LIBRARY_NAME/{include/cpptemplate/$LIBRARY_NAME,src}
# Generate CMakeLists.txt template
```

```bash
# scripts/create-app.sh
#!/bin/bash
APP_NAME=$1
mkdir -p apps/$APP_NAME/src
# Generate CMakeLists.txt template
```

## 📦 **Package and Distribution**

With proper structure, you can:

### Package Individual Libraries
```cmake
# Each library can be packaged separately
install(TARGETS CppTemplate_core EXPORT CoreTargets)
install(EXPORT CoreTargets NAMESPACE CppTemplate:: DESTINATION lib/cmake/Core)
```

### Create Convenience Packages
```cmake
# Package all libraries together
install(TARGETS CppTemplate_core CppTemplate_math CppTemplate_utils
        EXPORT CppTemplateTargets)
```

### Selective Installation
```bash
# Install only specific components
cmake --install build --component Core
cmake --install build --component Math
```

## 🎯 **Best Practices Summary**

1. **Use `libs/` for reusable libraries** - Keep them independent and focused
2. **Use `apps/` for applications** - Executable programs that use libraries
3. **Avoid root `src/` and `include/`** - They create confusion in multi-library projects
4. **Organize tests by library** - Mirror the library structure in tests
5. **Keep examples separate** - Demonstrate usage without cluttering main code
6. **Use consistent naming** - Follow `include/cpptemplate/libraryname/` pattern
7. **Make libraries independent** - Minimize cross-library dependencies
8. **Use modern CMake** - Proper target-based configuration

This structure scales well from small projects to large enterprise codebases and makes it easy to manage dependencies, testing, and distribution.