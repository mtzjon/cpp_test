#!/bin/bash

set -e

# Default values
BUILD_DIR="build"
BUILD_TYPE="Release"
FILTER=""
VERBOSE="false"
PARALLEL="true"
REPEAT=1
MEMCHECK="false"

# Function to show usage
show_help() {
    cat << EOF
Usage: $0 [OPTIONS]

Run tests for CppTemplate project

OPTIONS:
    -h, --help              Show this help message
    -d, --build-dir DIR     Build directory (default: build)
    -t, --build-type TYPE   Build type: Debug, Release, etc. (default: Release)
    -f, --filter PATTERN   Run only tests matching pattern
    -v, --verbose           Verbose test output
    -s, --serial            Run tests serially (not in parallel)
    -r, --repeat NUM        Repeat tests NUM times (default: 1)
    --memcheck             Run tests with Valgrind memory checking (Linux only)
    --gtest-args ARGS      Additional arguments to pass to Google Test

Examples:
    $0                          # Run all tests
    $0 --verbose               # Run with verbose output
    $0 --filter "*Calculator*" # Run only calculator tests
    $0 --memcheck              # Run with memory checking
    $0 --repeat 10             # Run tests 10 times
EOF
}

# Parse command line arguments
GTEST_ARGS=""
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
        -t|--build-type)
            BUILD_TYPE="$2"
            shift 2
            ;;
        -f|--filter)
            FILTER="$2"
            shift 2
            ;;
        -v|--verbose)
            VERBOSE="true"
            shift
            ;;
        -s|--serial)
            PARALLEL="false"
            shift
            ;;
        -r|--repeat)
            REPEAT="$2"
            shift 2
            ;;
        --memcheck)
            MEMCHECK="true"
            shift
            ;;
        --gtest-args)
            GTEST_ARGS="$2"
            shift 2
            ;;
        *)
            echo "Unknown option: $1"
            show_help
            exit 1
            ;;
    esac
done

# Check if build directory exists
if [[ ! -d "$BUILD_DIR" ]]; then
    echo "Error: Build directory '$BUILD_DIR' does not exist"
    echo "Run the build script first"
    exit 1
fi

# Find test executable
TEST_EXECUTABLE=""
if [[ -f "$BUILD_DIR/bin/CppTemplate_tests" ]]; then
    TEST_EXECUTABLE="$BUILD_DIR/bin/CppTemplate_tests"
elif [[ -f "$BUILD_DIR/bin/CppTemplate_tests.exe" ]]; then
    TEST_EXECUTABLE="$BUILD_DIR/bin/CppTemplate_tests.exe"
elif [[ -f "$BUILD_DIR/CppTemplate_tests" ]]; then
    TEST_EXECUTABLE="$BUILD_DIR/CppTemplate_tests"
else
    echo "Error: Test executable not found"
    echo "Make sure the project is built with tests enabled"
    exit 1
fi

echo "========================================"
echo "Running CppTemplate Tests"
echo "========================================"
echo "Build directory: $BUILD_DIR"
echo "Build type: $BUILD_TYPE"
echo "Test executable: $TEST_EXECUTABLE"

if [[ -n "$FILTER" ]]; then
    echo "Filter: $FILTER"
fi

if [[ "$MEMCHECK" == "true" ]]; then
    echo "Memory checking: enabled"
fi

echo "Repeat count: $REPEAT"
echo "========================================"

# Prepare CTest arguments
CTEST_ARGS=""

if [[ "$VERBOSE" == "true" ]]; then
    CTEST_ARGS="$CTEST_ARGS --verbose"
else
    CTEST_ARGS="$CTEST_ARGS --output-on-failure"
fi

if [[ "$PARALLEL" == "true" ]]; then
    CTEST_ARGS="$CTEST_ARGS --parallel $(nproc)"
fi

if [[ -n "$FILTER" ]]; then
    CTEST_ARGS="$CTEST_ARGS -R '$FILTER'"
fi

CTEST_ARGS="$CTEST_ARGS --build-config $BUILD_TYPE"

# Run tests with CTest
if [[ "$MEMCHECK" == "true" ]]; then
    # Check if Valgrind is available
    if ! command -v valgrind &> /dev/null; then
        echo "Error: Valgrind is not installed"
        exit 1
    fi
    
    echo "Running tests with Valgrind..."
    for ((i=1; i<=REPEAT; i++)); do
        if [[ $REPEAT -gt 1 ]]; then
            echo "Run $i/$REPEAT:"
        fi
        
        cd "$BUILD_DIR"
        valgrind --tool=memcheck --leak-check=full --error-exitcode=1 "$TEST_EXECUTABLE" $GTEST_ARGS
        cd ..
    done
else
    # Regular test run
    for ((i=1; i<=REPEAT; i++)); do
        if [[ $REPEAT -gt 1 ]]; then
            echo "Run $i/$REPEAT:"
        fi
        
        cd "$BUILD_DIR"
        if [[ -n "$FILTER" || -n "$GTEST_ARGS" ]]; then
            # Use direct test executable when we need to pass specific arguments
            DIRECT_ARGS=""
            if [[ -n "$FILTER" ]]; then
                DIRECT_ARGS="$DIRECT_ARGS --gtest_filter=$FILTER"
            fi
            if [[ -n "$GTEST_ARGS" ]]; then
                DIRECT_ARGS="$DIRECT_ARGS $GTEST_ARGS"
            fi
            "$TEST_EXECUTABLE" $DIRECT_ARGS
        else
            # Use CTest for better integration
            eval ctest $CTEST_ARGS
        fi
        cd ..
    done
fi

echo ""
echo "✅ All tests completed successfully!"

# Show test executable location for manual runs
echo ""
echo "Test executable location: $TEST_EXECUTABLE"
echo "Manual run example: $TEST_EXECUTABLE --gtest_help"