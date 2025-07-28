#!/bin/bash

set -e

# Default values
BUILD_DIR="build"
FIX="false"

# Function to show usage
show_help() {
    cat << EOF
Usage: $0 [OPTIONS]

Run clang-tidy static analysis on C++ source code

OPTIONS:
    -h, --help              Show this help message
    -d, --build-dir DIR     Build directory with compile_commands.json (default: build)
    -f, --fix               Apply suggested fixes automatically
    --header-filter REGEX  Regular expression for headers to analyze (default: .*)

Examples:
    $0                      # Run clang-tidy analysis
    $0 --fix               # Run clang-tidy and apply fixes
    $0 -d debug_build      # Use different build directory
EOF
}

# Parse command line arguments
HEADER_FILTER=".*"
while [[ $# -gt 0 ]]; do
    case $1 in
        -h|--help)
            show_help
            exit 0
            ;;
        -d|--build-dir)
            BUILD_DIR="$2"
            shift 2
            ;;
        -f|--fix)
            FIX="true"
            shift
            ;;
        --header-filter)
            HEADER_FILTER="$2"
            shift 2
            ;;
        *)
            echo "Unknown option: $1"
            show_help
            exit 1
            ;;
    esac
done

# Check if clang-tidy is available
if ! command -v clang-tidy &> /dev/null; then
    echo "Error: clang-tidy is not installed or not in PATH"
    exit 1
fi

# Check if build directory exists
if [[ ! -d "$BUILD_DIR" ]]; then
    echo "Error: Build directory '$BUILD_DIR' does not exist"
    echo "Run the build script first to generate compile_commands.json"
    exit 1
fi

# Check if compile_commands.json exists
if [[ ! -f "$BUILD_DIR/compile_commands.json" ]]; then
    echo "Error: compile_commands.json not found in '$BUILD_DIR'"
    echo "Make sure CMAKE_EXPORT_COMPILE_COMMANDS is ON and build the project first"
    exit 1
fi

# Find all C++ source files
echo "Finding C++ source files..."
CPP_FILES=$(find src -name '*.cpp' 2>/dev/null || true)

if [[ -z "$CPP_FILES" ]]; then
    echo "No C++ source files found in src/"
    exit 0
fi

echo "Found files:"
echo "$CPP_FILES" | sed 's/^/  /'

# Prepare clang-tidy arguments
CLANG_TIDY_ARGS="-p $BUILD_DIR --header-filter=$HEADER_FILTER"

if [[ "$FIX" == "true" ]]; then
    CLANG_TIDY_ARGS="$CLANG_TIDY_ARGS --fix --fix-errors"
    echo ""
    echo "Running clang-tidy with automatic fixes..."
else
    echo ""
    echo "Running clang-tidy analysis..."
fi

# Run clang-tidy on each file
EXIT_CODE=0
for file in $CPP_FILES; do
    echo ""
    echo "Analyzing $file..."
    if ! clang-tidy $CLANG_TIDY_ARGS "$file"; then
        EXIT_CODE=1
    fi
done

echo ""
if [[ $EXIT_CODE -eq 0 ]]; then
    echo "✅ clang-tidy analysis completed successfully."
else
    echo "❌ clang-tidy found issues. Please review and fix them."
fi

exit $EXIT_CODE