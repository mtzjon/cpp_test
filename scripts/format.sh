#!/bin/bash

set -e

# Default values
FIX="false"
CHECK_ONLY="false"

# Function to show usage
show_help() {
    cat << EOF
Usage: $0 [OPTIONS]

Format C++ source code using clang-format

OPTIONS:
    -h, --help          Show this help message
    -f, --fix           Apply formatting changes
    -c, --check         Check formatting without making changes (returns non-zero if changes needed)

Examples:
    $0 --check          # Check if code is properly formatted
    $0 --fix            # Format all C++ files
EOF
}

# Parse command line arguments
while [[ $# -gt 0 ]]; do
    case $1 in
        -h|--help)
            show_help
            exit 0
            ;;
        -f|--fix)
            FIX="true"
            shift
            ;;
        -c|--check)
            CHECK_ONLY="true"
            shift
            ;;
        *)
            echo "Unknown option: $1"
            show_help
            exit 1
            ;;
    esac
done

# Check if clang-format is available
if ! command -v clang-format &> /dev/null; then
    echo "Error: clang-format is not installed or not in PATH"
    exit 1
fi

# Find all C++ source files
echo "Finding C++ source files..."
FILES=$(find src tests -name '*.cpp' -o -name '*.hpp' -o -name '*.h' 2>/dev/null || true)

if [[ -z "$FILES" ]]; then
    echo "No C++ source files found"
    exit 0
fi

echo "Found files:"
echo "$FILES" | sed 's/^/  /'

if [[ "$CHECK_ONLY" == "true" ]]; then
    echo ""
    echo "Checking code formatting..."
    
    # Check if any files need formatting
    NEEDS_FORMATTING=false
    for file in $FILES; do
        if ! clang-format --dry-run --Werror "$file" &>/dev/null; then
            echo "  ❌ $file needs formatting"
            NEEDS_FORMATTING=true
        else
            echo "  ✅ $file is properly formatted"
        fi
    done
    
    if [[ "$NEEDS_FORMATTING" == "true" ]]; then
        echo ""
        echo "❌ Some files need formatting. Run with --fix to apply changes."
        exit 1
    else
        echo ""
        echo "✅ All files are properly formatted."
        exit 0
    fi
elif [[ "$FIX" == "true" ]]; then
    echo ""
    echo "Formatting files..."
    
    for file in $FILES; do
        echo "  Formatting $file..."
        clang-format -i "$file"
    done
    
    echo ""
    echo "✅ All files have been formatted."
else
    echo ""
    echo "No action specified. Use --check to verify formatting or --fix to apply formatting."
    show_help
    exit 1
fi