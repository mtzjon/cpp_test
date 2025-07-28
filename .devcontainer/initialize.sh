#!/bin/bash

# Initialize script for DevContainer (runs on host before container creation)
set -e

echo "🔧 Initializing DevContainer setup..."

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

# Create directories that will be mounted
print_info "Creating mount directories..."
mkdir -p .devcontainer/conan
mkdir -p build

# Create .devcontainer/conan directory for Conan cache persistence
if [ ! -d ".devcontainer/conan" ]; then
    mkdir -p .devcontainer/conan
    print_info "Created Conan cache directory"
fi

# Check if Docker is running
if ! docker info >/dev/null 2>&1; then
    print_warning "Docker is not running. Please start Docker before opening the DevContainer."
    exit 1
fi

# Check available disk space
available_space=$(df . | awk 'NR==2 {print $4}')
if [ "$available_space" -lt 2097152 ]; then  # Less than 2GB
    print_warning "Low disk space detected. DevContainer requires at least 2GB of free space."
fi

print_success "DevContainer initialization completed!"
echo "You can now open the project in VS Code and reopen in container."