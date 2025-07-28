#!/bin/bash

# Post-create script for DevContainer
set -e

echo "🚀 Running post-create setup..."

# Function to print colored output
print_info() {
    echo -e "\033[1;34m[INFO]\033[0m $1"
}

print_success() {
    echo -e "\033[1;32m[SUCCESS]\033[0m $1"
}

print_error() {
    echo -e "\033[1;31m[ERROR]\033[0m $1"
}

# Update Conan profile if needed
print_info "Setting up Conan environment..."
conan profile detect --force

# Install Conan dependencies and configure project
if [ -f "conanfile.txt" ] || [ -f "conanfile.py" ]; then
    print_info "Installing Conan dependencies..."
    conan install . --output-folder=build --build=missing -s build_type=Debug || {
        print_error "Failed to install Conan dependencies"
        exit 1
    }
    
    print_info "Configuring CMake project..."
    cmake -B build \
        -DCMAKE_BUILD_TYPE=Debug \
        -DCMAKE_TOOLCHAIN_FILE=build/conan_toolchain.cmake \
        -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
        -DBUILD_TESTS=ON || {
        print_error "Failed to configure CMake project"
        exit 1
    }
    
    print_success "Project configured successfully!"
else
    print_info "No Conan files found, skipping dependency installation"
fi

# Set up pre-commit hooks if .pre-commit-config.yaml exists
if [ -f ".pre-commit-config.yaml" ]; then
    print_info "Installing pre-commit hooks..."
    pre-commit install || print_error "Failed to install pre-commit hooks"
fi

# Create helpful aliases file
cat > ~/.bash_aliases << 'EOF'
# Project aliases
alias build='./scripts/build.sh'
alias test='./scripts/test.sh'
alias format='./scripts/format.sh'
alias lint='./scripts/lint.sh'
alias clean='rm -rf build/ && echo "Build directory cleaned"'
alias rebuild='clean && build'

# CMake aliases
alias cmake-debug='cmake -B build -DCMAKE_BUILD_TYPE=Debug -DCMAKE_TOOLCHAIN_FILE=build/conan_toolchain.cmake'
alias cmake-release='cmake -B build -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE=build/conan_toolchain.cmake'
alias cmake-build='cmake --build build --parallel $(nproc)'

# Git aliases
alias gs='git status'
alias ga='git add'
alias gc='git commit'
alias gp='git push'
alias gl='git log --oneline -10'
alias gd='git diff'

# Utility aliases
alias ll='ls -alF'
alias la='ls -A'
alias l='ls -CF'
alias ..='cd ..'
alias ...='cd ../..'
alias tree='tree -I "__pycache__|*.pyc|build|.git"'
EOF

# Source the aliases
echo "source ~/.bash_aliases" >> ~/.bashrc

# Create a welcome message
cat > ~/.welcome_message << 'EOF'
🎉 Welcome to the C++ Development Environment!

Quick commands:
  build          - Build the project
  test           - Run tests
  format         - Format code
  lint           - Run static analysis
  clean          - Clean build directory
  rebuild        - Clean and rebuild

Tools available:
  • CMake with Ninja generator
  • Conan package manager
  • GCC 11 and Clang 15 compilers
  • clang-format and clang-tidy
  • Valgrind and GDB for debugging
  • Doxygen for documentation
  • Coverage tools (lcov, gcovr)

Happy coding! 🚀
EOF

# Display welcome message on shell startup
echo "cat ~/.welcome_message" >> ~/.bashrc

print_success "Post-create setup completed!"
echo "🎯 Ready to develop! Open a terminal and start coding."