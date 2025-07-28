# CppTemplate

A production-quality C++ project template with modern tools and best practices.

## Features

This template provides a complete, production-ready C++ project setup with:

### 🛠️ **Modern Build System**
- **CMake 3.20+** with modern practices
- **Conan 2.0** for dependency management
- **C++20** standard support
- Cross-platform builds (Linux, Windows, macOS)

### 🧪 **Testing & Quality Assurance**
- **Google Test** for unit testing
- **clang-format** for code formatting
- **clang-tidy** for static analysis
- **Sanitizers** support (AddressSanitizer, UBSan)
- **Valgrind** integration for memory checking
- **Code coverage** reporting

### 🚀 **CI/CD**
- **GitHub Actions** workflows
- Multi-platform testing
- Automated formatting checks
- Memory leak detection
- Coverage reporting

### 📚 **Documentation**
- **Doxygen** integration
- Comprehensive code documentation
- API reference generation

### 🔧 **Development Tools**
- Build scripts for easy compilation
- Formatting and linting scripts
- Test runner with various options
- Docker support

## Project Structure

```
cpp-template/
├── src/                    # Source code
│   ├── core/              # Core functionality
│   │   ├── calculator.hpp
│   │   ├── calculator.cpp
│   │   ├── logger.hpp
│   │   └── logger.cpp
│   ├── utils/             # Utility functions
│   │   ├── string_utils.hpp
│   │   └── string_utils.cpp
│   └── main.cpp           # Application entry point
├── tests/                 # Unit tests
│   ├── test_calculator.cpp
│   ├── test_string_utils.cpp
│   ├── test_logger.cpp
│   └── CMakeLists.txt
├── scripts/               # Build and utility scripts
│   ├── build.sh          # Main build script
│   ├── format.sh         # Code formatting
│   ├── lint.sh           # Static analysis
│   └── test.sh           # Test runner
├── docs/                  # Documentation
│   ├── Doxyfile.in       # Doxygen configuration
│   └── CMakeLists.txt
├── cmake/                 # CMake modules
│   └── CppTemplateConfig.cmake.in
├── .github/workflows/     # CI/CD pipelines
│   └── ci.yml
├── CMakeLists.txt         # Main CMake file
├── conanfile.txt          # Dependencies
├── conanfile.py           # Advanced Conan recipe
├── .clang-format          # Code formatting rules
├── .clang-tidy           # Static analysis rules
├── Dockerfile            # Multi-stage Docker build
└── README.md
```

## Quick Start

### Prerequisites

- **C++20 capable compiler** (GCC 11+, Clang 15+, MSVC 2019+)
- **CMake 3.20+**
- **Python 3.8+** (for Conan)
- **Git**

### Installation

1. **Clone the repository:**
   ```bash
   git clone https://github.com/yourusername/cpp-template.git
   cd cpp-template
   ```

2. **Install Conan:**
   ```bash
   pip install "conan>=2.0"
   conan profile detect --force
   ```

3. **Build the project:**
   ```bash
   ./scripts/build.sh
   ```

4. **Run the application:**
   ```bash
   ./build/bin/cpp-template
   ```

## Usage

### Building

The build script provides various options:

```bash
# Release build with tests (default)
./scripts/build.sh

# Debug build with sanitizers
./scripts/build.sh -t Debug --sanitizers

# Clean build with documentation
./scripts/build.sh --clean --docs

# Build with clang-tidy analysis
./scripts/build.sh --clang-tidy

# Build and install
./scripts/build.sh --install
```

### Testing

Run tests with the test script:

```bash
# Run all tests
./scripts/test.sh

# Run specific tests
./scripts/test.sh --filter "*Calculator*"

# Run with memory checking
./scripts/test.sh --memcheck

# Verbose output
./scripts/test.sh --verbose
```

### Code Quality

Format code:
```bash
# Check formatting
./scripts/format.sh --check

# Apply formatting
./scripts/format.sh --fix
```

Run static analysis:
```bash
# Analyze code
./scripts/lint.sh

# Analyze and fix issues
./scripts/lint.sh --fix
```

### Docker Support

Build and run with Docker:

```bash
# Build production image
docker build --target production -t cpp-template .

# Run the application
docker run --rm cpp-template

# Build and run tests
docker build --target testing -t cpp-template-test .

# Generate documentation
docker build --target docs -t cpp-template-docs .
docker run -p 8080:80 cpp-template-docs
```

### VS Code DevContainer

For the best development experience, use the provided DevContainer:

```bash
# Prerequisites: VS Code + Dev Containers extension + Docker
# 1. Open project in VS Code
# 2. Press Ctrl+Shift+P
# 3. Type "Dev Containers: Reopen in Container"
# 4. Wait for container to build

# Once inside the container:
build          # Build the project
test           # Run tests
format         # Format code
lint           # Run static analysis
```

The DevContainer provides:
- **Complete C++ environment** with GCC 11, Clang 15, CMake, Ninja
- **Pre-configured VS Code** with C++ extensions and settings
- **Debugging support** for all applications
- **Code quality tools** (clang-format, clang-tidy, pre-commit hooks)
- **Package managers** (Conan 2.0, vcpkg)

See [.devcontainer/README.md](.devcontainer/README.md) for detailed information.

### Manual Build

If you prefer manual building:

```bash
# Install dependencies
conan install . --output-folder=build --build=missing

# Configure
cmake -B build -DCMAKE_TOOLCHAIN_FILE=build/conan_toolchain.cmake

# Build
cmake --build build --parallel

# Test
cd build && ctest --output-on-failure
```

## Dependencies

This template uses the following libraries:

- **[fmt](https://github.com/fmtlib/fmt)** - Modern formatting library
- **[spdlog](https://github.com/gabime/spdlog)** - Fast logging library
- **[Google Test](https://github.com/google/googletest)** - Testing framework

## Configuration

### CMake Options

- `BUILD_TESTS` (ON/OFF) - Build unit tests
- `BUILD_DOCS` (ON/OFF) - Build documentation
- `ENABLE_CLANG_TIDY` (ON/OFF) - Enable clang-tidy
- `ENABLE_SANITIZERS` (ON/OFF) - Enable sanitizers

### Conan Options

- `shared` (True/False) - Build shared libraries
- `fPIC` (True/False) - Position independent code
- `with_tests` (True/False) - Include test dependencies

## Documentation

Generate documentation with Doxygen:

```bash
./scripts/build.sh --docs
```

Open `build/docs/doxygen/html/index.html` in your browser.

## Contributing

Please read [CONTRIBUTING.md](CONTRIBUTING.md) for details on our code of conduct and the process for submitting pull requests.

1. Fork the repository
2. Create a feature branch: `git checkout -b feature-name`
3. Make your changes
4. Format code: `./scripts/format.sh --fix`
5. Run tests: `./scripts/test.sh`
6. Run static analysis: `./scripts/lint.sh`
7. Commit changes: `git commit -am 'Add feature'`
8. Push to branch: `git push origin feature-name`
9. Create a Pull Request

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Features Showcase

### Example Output

```bash
$ ./build/bin/cpp-template
[2024-01-15 10:30:45.123] [CppTemplate] [info] Application started
[2024-01-15 10:30:45.124] [CppTemplate] [info] Performing calculations with a=10.5, b=3.2
[2024-01-15 10:30:45.124] [CppTemplate] [info] Addition: 10.5 + 3.2 = 13.7
[2024-01-15 10:30:45.124] [CppTemplate] [info] Subtraction: 10.5 - 3.2 = 7.3
[2024-01-15 10:30:45.124] [CppTemplate] [info] Multiplication: 10.5 * 3.2 = 33.6
[2024-01-15 10:30:45.124] [CppTemplate] [info] Division: 10.5 / 3.2 = 3.28125
[2024-01-15 10:30:45.124] [CppTemplate] [info] Original string: '  Hello, World!  '
[2024-01-15 10:30:45.124] [CppTemplate] [info] Trimmed string: 'Hello, World!'
[2024-01-15 10:30:45.124] [CppTemplate] [info] Uppercase string: '  HELLO, WORLD!  '
[2024-01-15 10:30:45.124] [CppTemplate] [info] Lowercase string: '  hello, world!  '
[2024-01-15 10:30:45.124] [CppTemplate] [info] Split 'apple,banana,cherry,date' into 4 parts:
[2024-01-15 10:30:45.124] [CppTemplate] [info]   [0]: 'apple'
[2024-01-15 10:30:45.125] [CppTemplate] [info]   [1]: 'banana'
[2024-01-15 10:30:45.125] [CppTemplate] [info]   [2]: 'cherry'
[2024-01-15 10:30:45.125] [CppTemplate] [info]   [3]: 'date'
[2024-01-15 10:30:45.125] [CppTemplate] [info] Application completed successfully
```

### Test Results

```bash
$ ./scripts/test.sh
========================================
Running CppTemplate Tests
========================================
Build directory: build
Build type: Release
Test executable: build/bin/CppTemplate_tests
Repeat count: 1
========================================
Test project /workspace/build
    Start 1: CppTemplate_tests
1/1 Test #1: CppTemplate_tests ................   Passed    0.01 sec

100% tests passed, 0 tests failed out of 1 total tests

✅ All tests completed successfully!

Test executable location: build/bin/CppTemplate_tests
Manual run example: build/bin/CppTemplate_tests --gtest_help
```

## Advanced Features

### Continuous Integration

The project includes comprehensive GitHub Actions workflows:

- **Multi-platform builds** (Linux, Windows, macOS)
- **Multiple compilers** (GCC, Clang, MSVC)
- **Code quality checks** (formatting, static analysis)
- **Memory testing** with Valgrind
- **Coverage reporting** with Codecov

### Static Analysis

Comprehensive static analysis with clang-tidy:

- **Core Guidelines** compliance
- **Modern C++** best practices
- **Performance** optimizations
- **Security** checks
- **Readability** improvements

### Memory Safety

Multiple layers of memory safety:

- **RAII** throughout the codebase
- **Smart pointers** where appropriate
- **Sanitizers** for runtime checking
- **Valgrind** for deep memory analysis

## Customization

To adapt this template for your project:

1. **Rename the project** in `CMakeLists.txt`
2. **Update dependencies** in `conanfile.txt`
3. **Modify namespace** from `cpp_template` to your project name
4. **Update documentation** and README
5. **Customize CI/CD** workflows as needed

## Troubleshooting

### Common Issues

**Conan dependencies not found:**
```bash
conan profile detect --force
conan install . --output-folder=build --build=missing
```

**CMake configuration fails:**
```bash
# Make sure you have the toolchain file
cmake -B build -DCMAKE_TOOLCHAIN_FILE=build/conan_toolchain.cmake
```

**Tests fail to build:**
```bash
# Ensure GTest is available
conan install . --output-folder=build --build=missing -o with_tests=True
```

For more issues, check the [GitHub Issues](https://github.com/yourusername/cpp-template/issues) page.

---

**Happy coding!** 🚀