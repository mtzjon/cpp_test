# Directory Usage Guide

## 📁 **What Each Directory Is For**

### ✅ **Current Clean Structure**

```
cpp-template/
├── libs/           📚 REUSABLE LIBRARIES - Self-contained, reusable components
├── apps/           🎯 APPLICATIONS - Executable programs that use libraries  
├── examples/       📖 USAGE EXAMPLES - Demonstrates how to use libraries
├── tests/          🧪 TESTS - Organized by library + integration tests
├── docs/           📚 DOCUMENTATION - Project documentation
├── scripts/        🛠️ BUILD SCRIPTS - Build, test, format utilities
├── cmake/          🔧 CMAKE MODULES - Reusable CMake configuration
├── .devcontainer/  🐳 DEVELOPMENT ENV - VS Code container setup
└── .github/        🚀 CI/CD WORKFLOWS - Automation and workflows
```

## 🎯 **Directory Purposes**

### 📚 `libs/` - **Reusable Libraries**
**USE FOR:** Code that can be reused across multiple applications
```
libs/core/           # Foundation library (logging, config, exceptions)
libs/math/           # Mathematical operations (calculator, matrix, stats)
libs/utils/          # Utility functions (string, file, time operations)
libs/network/        # Network operations (TCP, HTTP, WebSocket)
```

**STRUCTURE:**
```
libs/mylibrary/
├── include/cpptemplate/mylibrary/    # 📁 Public headers (API)
├── src/                              # 📁 Implementation files
└── CMakeLists.txt                    # 📄 Build configuration
```

**GUIDELINES:**
- ✅ **DO:** Put reusable, self-contained functionality
- ✅ **DO:** Follow `include/cpptemplate/libraryname/` pattern
- ✅ **DO:** Keep libraries independent
- ❌ **DON'T:** Put application-specific code
- ❌ **DON'T:** Create circular dependencies

### 🎯 `apps/` - **Executable Applications**  
**USE FOR:** End-user programs that use the libraries
```
apps/main/           # Main application
apps/cli/            # Command-line tool
apps/server/         # Network server application
```

**STRUCTURE:**
```
apps/myapp/
├── src/             # 📁 Application source code
├── include/         # 📁 Private headers (optional)
└── CMakeLists.txt   # 📄 Build configuration
```

**GUIDELINES:**
- ✅ **DO:** Put application-specific logic
- ✅ **DO:** Link to libraries via CMake targets
- ✅ **DO:** Keep each app independent
- ❌ **DON'T:** Put reusable code here (move to libs instead)

### 📖 `examples/` - **Usage Examples**
**USE FOR:** Demonstrating how to use the libraries
```
examples/basic_usage/        # Simple usage examples
examples/advanced_features/  # Complex usage patterns
examples/tutorials/          # Step-by-step guides
```

**GUIDELINES:**
- ✅ **DO:** Create small, focused examples
- ✅ **DO:** Include comprehensive documentation
- ✅ **DO:** Make examples buildable independently
- ❌ **DON'T:** Put production code here

### 🧪 `tests/` - **Test Code**
**USE FOR:** Testing libraries and integration
```
tests/core/          # Tests for core library
tests/math/          # Tests for math library
tests/utils/         # Tests for utils library
tests/integration/   # Cross-library tests
```

**GUIDELINES:**
- ✅ **DO:** Mirror the library structure
- ✅ **DO:** Test both individual libraries and integration
- ✅ **DO:** Use descriptive test names
- ❌ **DON'T:** Test application UI (keep unit/integration focused)

## 🚫 **Removed/Deprecated Directories**

### ❌ `src/` (Root Source Directory)
**WHY REMOVED:** 
- Confusing in multi-library projects
- Mixes libraries and applications
- Makes dependency management unclear
- Complicates CMake configuration

**MIGRATION:**
```bash
# OLD (removed):
src/main.cpp          → apps/main/src/main.cpp
src/calculator.cpp    → libs/math/src/calculator.cpp
src/logger.cpp        → libs/core/src/logger.cpp
```

### ❌ `include/` (Root Include Directory)  
**WHY NOT USED:**
- Conflicts with library-specific includes
- Makes namespace organization unclear
- Complicates header installation

**INSTEAD USE:**
```bash
# CORRECT:
libs/math/include/cpptemplate/math/calculator.hpp
libs/core/include/cpptemplate/core/logger.hpp
```

## 🔧 **How to Use Each Directory**

### **Adding a New Library**
```bash
# 1. Create structure
mkdir -p libs/mylibrary/{include/cpptemplate/mylibrary,src}

# 2. Create files
touch libs/mylibrary/include/cpptemplate/mylibrary/myclass.hpp
touch libs/mylibrary/src/myclass.cpp
touch libs/mylibrary/CMakeLists.txt

# 3. Update main CMakeLists.txt
# Add: option(BUILD_MYLIBRARY_LIB "Build my library" ON)

# 4. Update libs/CMakeLists.txt
# Add: if(BUILD_MYLIBRARY_LIB) add_subdirectory(mylibrary) endif()
```

### **Adding a New Application**
```bash
# 1. Create structure  
mkdir -p apps/myapp/src

# 2. Create files
touch apps/myapp/src/main.cpp
touch apps/myapp/CMakeLists.txt

# 3. Update main CMakeLists.txt
# Add: option(BUILD_MYAPP_APP "Build my app" ON)

# 4. Update apps/CMakeLists.txt
# Add: if(BUILD_MYAPP_APP) add_subdirectory(myapp) endif()
```

### **Adding Tests**
```bash
# 1. Create test in appropriate library directory
touch tests/mylibrary/test_myclass.cpp

# 2. Update tests/CMakeLists.txt
# Add test file to the appropriate section
```

### **Adding Examples**
```bash
# 1. Create example
mkdir -p examples/my_example
touch examples/my_example/{example.cpp,CMakeLists.txt}

# 2. Update examples/CMakeLists.txt
# Add: add_subdirectory(my_example)
```

## 📋 **Quick Reference**

| Directory | Purpose | When to Use | Example Content |
|-----------|---------|-------------|-----------------|
| `libs/` | Reusable libraries | Shared functionality | logger, calculator, utils |
| `apps/` | Applications | End-user programs | main app, CLI tool, server |
| `examples/` | Usage demos | Show how to use libs | tutorials, samples |
| `tests/` | Test code | Verify functionality | unit tests, integration |
| `docs/` | Documentation | User guides, API docs | README, guides |
| `scripts/` | Build tools | Automation | build.sh, format.sh |

## 🎯 **Best Practices**

1. **Keep libraries independent** - Minimize cross-library dependencies
2. **Use consistent naming** - Follow `cpptemplate::libraryname` pattern  
3. **Organize tests by library** - Mirror the library structure
4. **Make examples simple** - Focus on demonstrating specific features
5. **Keep apps thin** - Most logic should be in libraries
6. **Use modern CMake** - Target-based configuration throughout

This structure scales from small projects to large enterprise codebases! 🚀