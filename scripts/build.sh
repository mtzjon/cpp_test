#!/bin/bash

set -e

# Default values
BUILD_TYPE="Release"
BUILD_DIR="build"
ENABLE_TESTS="ON"
ENABLE_DOCS="OFF"
ENABLE_SANITIZERS="OFF"
ENABLE_CLANG_TIDY="OFF"
CLEAN_BUILD="false"
INSTALL="false"
JOBS=$(nproc)
BUILD_SHARED_LIBS="OFF"
BUILD_CORE_LIB="ON"
BUILD_MATH_LIB="ON"
BUILD_UTILS_LIB="ON"
BUILD_NETWORK_LIB="ON"
BUILD_MAIN_APP="ON"
BUILD_CLI_APP="ON"
BUILD_SERVER_APP="ON"

# Function to show usage
show_help() {
    cat << EOF
Usage: $0 [OPTIONS]

Build script for CppTemplate project

OPTIONS:
    -h, --help              Show this help message
    -t, --build-type TYPE   Build type: Debug, Release, RelWithDebInfo, MinSizeRel (default: Release)
    -d, --build-dir DIR     Build directory (default: build)
    -j, --jobs NUM          Number of parallel jobs (default: number of CPU cores)
    --tests                 Enable tests (default: ON)
    --no-tests             Disable tests
    --docs                 Enable documentation generation
    --sanitizers           Enable sanitizers (Debug builds only)
    --clang-tidy           Enable clang-tidy
    --clean                Clean build directory before building
    --install              Install after building
    --verbose              Verbose output
    --shared               Build shared libraries
    --static               Build static libraries (default)
    --disable-core         Disable core library
    --disable-math         Disable math library
    --disable-utils        Disable utils library
    --disable-network      Disable network library
    --disable-main         Disable main application
    --disable-cli          Disable CLI application
    --disable-server       Disable server application

Examples:
    $0                                  # Release build with tests
    $0 -t Debug --sanitizers           # Debug build with sanitizers
    $0 --clean --docs --install        # Clean build with docs and install
    $0 -t Debug --clang-tidy           # Debug build with clang-tidy
EOF
}

# Parse command line arguments
while [[ $# -gt 0 ]]; do
    case $1 in
        -h|--help)
            show_help
            exit 0
            ;;
        -t|--build-type)
            BUILD_TYPE="$2"
            shift 2
            ;;
        -d|--build-dir)
            BUILD_DIR="$2"
            shift 2
            ;;
        -j|--jobs)
            JOBS="$2"
            shift 2
            ;;
        --tests)
            ENABLE_TESTS="ON"
            shift
            ;;
        --no-tests)
            ENABLE_TESTS="OFF"
            shift
            ;;
        --docs)
            ENABLE_DOCS="ON"
            shift
            ;;
        --sanitizers)
            ENABLE_SANITIZERS="ON"
            shift
            ;;
        --clang-tidy)
            ENABLE_CLANG_TIDY="ON"
            shift
            ;;
        --clean)
            CLEAN_BUILD="true"
            shift
            ;;
        --install)
            INSTALL="true"
            shift
            ;;
        --verbose)
            set -x
            shift
            ;;
        --shared)
            BUILD_SHARED_LIBS="ON"
            shift
            ;;
        --static)
            BUILD_SHARED_LIBS="OFF"
            shift
            ;;
        --disable-core)
            BUILD_CORE_LIB="OFF"
            shift
            ;;
        --disable-math)
            BUILD_MATH_LIB="OFF"
            shift
            ;;
        --disable-utils)
            BUILD_UTILS_LIB="OFF"
            shift
            ;;
        --disable-network)
            BUILD_NETWORK_LIB="OFF"
            shift
            ;;
        --disable-main)
            BUILD_MAIN_APP="OFF"
            shift
            ;;
        --disable-cli)
            BUILD_CLI_APP="OFF"
            shift
            ;;
        --disable-server)
            BUILD_SERVER_APP="OFF"
            shift
            ;;
        *)
            echo "Unknown option: $1"
            show_help
            exit 1
            ;;
    esac
done

# Validate build type
if [[ ! "$BUILD_TYPE" =~ ^(Debug|Release|RelWithDebInfo|MinSizeRel)$ ]]; then
    echo "Error: Invalid build type '$BUILD_TYPE'"
    echo "Valid options: Debug, Release, RelWithDebInfo, MinSizeRel"
    exit 1
fi

# Clean build directory if requested
if [[ "$CLEAN_BUILD" == "true" ]]; then
    echo "Cleaning build directory: $BUILD_DIR"
    rm -rf "$BUILD_DIR"
fi

# Create build directory
mkdir -p "$BUILD_DIR"

echo "========================================"
echo "Building CppTemplate"
echo "========================================"
echo "Build type: $BUILD_TYPE"
echo "Build directory: $BUILD_DIR"
echo "Tests: $ENABLE_TESTS"
echo "Documentation: $ENABLE_DOCS"
echo "Sanitizers: $ENABLE_SANITIZERS"
echo "Clang-tidy: $ENABLE_CLANG_TIDY"
echo "Jobs: $JOBS"
echo "========================================"

# Install dependencies with Conan
echo "Installing dependencies..."
conan install . --output-folder="$BUILD_DIR" --build=missing -s build_type="$BUILD_TYPE"

# Configure CMake
echo "Configuring CMake..."
cmake -B "$BUILD_DIR" \
    -DCMAKE_BUILD_TYPE="$BUILD_TYPE" \
    -DCMAKE_TOOLCHAIN_FILE="$BUILD_DIR/conan_toolchain.cmake" \
    -DBUILD_TESTS="$ENABLE_TESTS" \
    -DBUILD_DOCS="$ENABLE_DOCS" \
    -DENABLE_SANITIZERS="$ENABLE_SANITIZERS" \
    -DENABLE_CLANG_TIDY="$ENABLE_CLANG_TIDY" \
    -DBUILD_SHARED_LIBS="$BUILD_SHARED_LIBS" \
    -DBUILD_CORE_LIB="$BUILD_CORE_LIB" \
    -DBUILD_MATH_LIB="$BUILD_MATH_LIB" \
    -DBUILD_UTILS_LIB="$BUILD_UTILS_LIB" \
    -DBUILD_NETWORK_LIB="$BUILD_NETWORK_LIB" \
    -DBUILD_MAIN_APP="$BUILD_MAIN_APP" \
    -DBUILD_CLI_APP="$BUILD_CLI_APP" \
    -DBUILD_SERVER_APP="$BUILD_SERVER_APP"

# Build
echo "Building..."
cmake --build "$BUILD_DIR" --config "$BUILD_TYPE" --parallel "$JOBS"

# Run tests if enabled
if [[ "$ENABLE_TESTS" == "ON" ]]; then
    echo "Running tests..."
    cd "$BUILD_DIR"
    ctest --build-config "$BUILD_TYPE" --output-on-failure --parallel "$JOBS"
    cd ..
fi

# Install if requested
if [[ "$INSTALL" == "true" ]]; then
    echo "Installing..."
    cmake --install "$BUILD_DIR" --config "$BUILD_TYPE"
fi

echo "========================================"
echo "Build completed successfully!"
echo "========================================"

# Show executable locations
echo "Built applications:"
for app in cpp_template_main cpp_template_cli cpp_template_server; do
    if [[ -f "$BUILD_DIR/bin/$app" ]]; then
        echo "  $app: $BUILD_DIR/bin/$app"
    elif [[ -f "$BUILD_DIR/bin/$app.exe" ]]; then
        echo "  $app: $BUILD_DIR/bin/$app.exe"
    fi
done

if [[ "$ENABLE_DOCS" == "ON" ]] && [[ -f "$BUILD_DIR/docs/doxygen/html/index.html" ]]; then
    echo "Documentation: $BUILD_DIR/docs/doxygen/html/index.html"
fi