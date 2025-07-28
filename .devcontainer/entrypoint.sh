#!/bin/bash

# DevContainer entrypoint script
set -e

# Function to print colored output
print_info() {
    echo -e "\033[1;34m[INFO]\033[0m $1"
}

print_success() {
    echo -e "\033[1;32m[SUCCESS]\033[0m $1"
}

print_warning() {
    echo -e "\033[1;33m[WARNING]\033[0m $1"
}

# Create logs directory if it doesn't exist
if [ ! -d "/workspace/logs" ]; then
    mkdir -p /workspace/logs
    print_info "Created logs directory"
fi

# Ensure proper ownership of workspace
if [ "$(stat -c %u /workspace)" != "$(id -u)" ]; then
    print_info "Fixing workspace ownership..."
    sudo chown -R $(id -u):$(id -g) /workspace 2>/dev/null || true
fi

# Set up Git safe directory
git config --global --add safe.directory /workspace 2>/dev/null || true

# Check if Conan profile exists, create if not
if [ ! -f "${CONAN_USER_HOME}/.conan2/profiles/default" ]; then
    print_info "Setting up Conan profile..."
    conan profile detect --force
fi

# Display environment information
print_info "Development Environment Ready!"
echo "────────────────────────────────────────"
echo "🏠 Workspace: /workspace"
echo "🔧 CMake: $(cmake --version | head -n1)"
echo "🏗️  Ninja: $(ninja --version)"
echo "📦 Conan: $(conan --version)"
echo "🔨 GCC: $(gcc --version | head -n1)"
echo "🔨 Clang: $(clang --version | head -n1)"
echo "🧹 clang-format: $(clang-format --version)"
echo "🔍 clang-tidy: $(clang-tidy --version | head -n1)"
echo "────────────────────────────────────────"
print_success "Environment initialized successfully!"

# Execute the main command
exec "$@"