# DevContainer for C++ Development

This directory contains the configuration for a comprehensive VS Code DevContainer that provides a complete C++ development environment.

## 🚀 Quick Start

1. **Prerequisites:**
   - [VS Code](https://code.visualstudio.com/) installed
   - [Dev Containers extension](https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.remote-containers) installed
   - [Docker](https://www.docker.com/) running on your system

2. **Open in DevContainer:**
   - Open this project in VS Code
   - Press `Ctrl+Shift+P` (or `Cmd+Shift+P` on Mac)
   - Type "Dev Containers: Reopen in Container"
   - Wait for the container to build and start

3. **Start Development:**
   - The environment will be ready with all tools pre-configured
   - Run `build` to build the project
   - Run `test` to execute tests

## 🛠️ What's Included

### Development Tools
- **Compilers:** GCC 11, Clang 15
- **Build Systems:** CMake 3.20+, Ninja
- **Package Managers:** Conan 2.0, vcpkg
- **Debuggers:** GDB, Valgrind
- **Documentation:** Doxygen with Graphviz
- **Code Quality:** clang-format, clang-tidy, cppcheck
- **Coverage:** lcov, gcovr
- **Version Control:** Git with Git LFS

### VS Code Extensions
- **C++ Development:** C/C++ Extension Pack, CMake Tools
- **Code Quality:** clang-format, clang-tidy, clangd
- **Documentation:** Doxygen support
- **Git:** GitLens, GitHub integration
- **Testing:** Test adapters for Google Test
- **Themes:** Material Icon Theme, GitHub Theme

### Pre-configured Settings
- **IntelliSense:** C++20 standard with proper configuration
- **Formatting:** Automatic formatting on save
- **CMake:** Auto-configure with Ninja generator
- **Debugging:** Ready-to-use debug configurations for all apps

## 📁 DevContainer Structure

```
.devcontainer/
├── devcontainer.json       # Main DevContainer configuration
├── Dockerfile             # Container definition
├── entrypoint.sh          # Container startup script
├── post-create.sh         # Post-creation setup
├── on-create.sh          # Initial VS Code setup
├── initialize.sh         # Pre-container initialization
├── .pre-commit-config.yaml # Pre-commit hooks configuration
└── README.md             # This file
```

## ⚙️ Configuration Details

### DevContainer Features
- **Non-root user:** Runs as `developer` user for security
- **Port forwarding:** Common development ports (8080, 3000, 8000)
- **Persistent volumes:** Conan cache and build directory
- **Git integration:** Safe directory configuration
- **Environment variables:** Optimized for C++ development

### VS Code Integration
- **Tasks:** Build, test, format, lint, clean
- **Launch configs:** Debug configurations for all applications
- **Settings:** Optimized for C++ development
- **IntelliSense:** Proper C++20 configuration

### Development Aliases
The environment provides convenient aliases:
```bash
# Project commands
build          # Build the project
test           # Run tests
format         # Format code
lint           # Run static analysis
clean          # Clean build directory
rebuild        # Clean and rebuild

# CMake commands
cmake-debug    # Configure Debug build
cmake-release  # Configure Release build
cmake-build    # Build with CMake

# Git shortcuts
gs             # git status
ga             # git add
gc             # git commit
gp             # git push
gl             # git log --oneline -10
gd             # git diff
```

## 🔧 Customization

### Adding Extensions
Edit `devcontainer.json` and add extension IDs to the `extensions` array:
```json
"extensions": [
    "existing.extension",
    "new.extension.id"
]
```

### Modifying Build Tools
Edit the `Dockerfile` to add or remove development tools:
```dockerfile
RUN apt-get install -y \
    your-new-tool \
    another-tool
```

### Changing Compiler Versions
Update the `Dockerfile` to install different compiler versions:
```dockerfile
# Install different GCC version
gcc-12 \
g++-12 \
```

## 🐳 Container Details

### Base Image
- **Ubuntu 22.04 LTS** - Stable and well-supported
- **Multi-stage build** - Optimized for development

### User Setup
- **Username:** `developer`
- **UID/GID:** 1000 (matches common host user)
- **Sudo access:** Passwordless sudo for package installation

### Environment Variables
```bash
CMAKE_GENERATOR=Ninja
CMAKE_BUILD_PARALLEL_LEVEL=4
CONAN_USER_HOME=/home/developer
VCPKG_ROOT=/home/developer/vcpkg
```

### Mounted Volumes
- **Source code:** `/workspace` (project root)
- **Conan cache:** Persistent across container restarts
- **Build directory:** Shared with host for performance

## 🚀 Performance Tips

### Build Performance
- **Ninja generator:** Faster parallel builds
- **ccache:** Compiler caching (can be added)
- **Shared build directory:** Avoid rebuilding when restarting container

### VS Code Performance
- **clangd:** Better IntelliSense performance than default C++ extension
- **CMake Tools:** Integrated build system support
- **Exclude build artifacts:** From file watcher in VS Code settings

### Container Performance
- **Volume mounts:** Used for build cache persistence
- **Memory limits:** Can be configured in Docker settings
- **CPU allocation:** Automatically uses available cores

## 🔍 Debugging

### Applications
Debug configurations are provided for all applications:
- **Main App:** `cpp_template_main`
- **CLI App:** `cpp_template_cli`
- **Server App:** `cpp_template_server`

### Memory Debugging
```bash
# Run with Valgrind
valgrind --tool=memcheck --leak-check=full ./build/bin/cpp_template_main

# Run tests with memory checking
./scripts/test.sh --memcheck
```

### Static Analysis
```bash
# Run clang-tidy
./scripts/lint.sh

# Run with automatic fixes
./scripts/lint.sh --fix
```

## 🧪 Testing

### Running Tests
```bash
# Run all tests
test

# Run specific tests
./scripts/test.sh --filter "*Calculator*"

# Run with verbose output
./scripts/test.sh --verbose
```

### Coverage Analysis
```bash
# Build with coverage
./scripts/build.sh -t Debug --coverage

# Generate coverage report
lcov --capture --directory build --output-file coverage.info
```

## 📝 Pre-commit Hooks

The environment includes pre-commit hooks for code quality:

```bash
# Install hooks (done automatically)
pre-commit install

# Run hooks manually
pre-commit run --all-files

# Update hooks
pre-commit autoupdate
```

### Included Hooks
- **clang-format:** C++ code formatting
- **clang-tidy:** Static analysis (optional)
- **CMake format:** CMake file formatting
- **Markdown lint:** Documentation formatting
- **Shell check:** Shell script validation
- **General:** Trailing whitespace, file endings, etc.

## 🔧 Troubleshooting

### Container Won't Start
1. **Check Docker:** Ensure Docker is running
2. **Check space:** Ensure sufficient disk space (2GB+)
3. **Rebuild:** Try "Dev Containers: Rebuild Container"

### Build Issues
1. **Clean build:** Run `clean` then `build`
2. **Conan cache:** Clear Conan cache if dependencies fail
3. **Check logs:** Look at build output for specific errors

### VS Code Issues
1. **Reload window:** `Ctrl+Shift+P` → "Developer: Reload Window"
2. **Reset settings:** Delete `.vscode/settings.json` and reopen
3. **Extension conflicts:** Disable conflicting extensions

### Performance Issues
1. **Increase Docker memory:** In Docker Desktop settings
2. **Use SSD:** Ensure project is on fast storage
3. **Close unused applications:** Free up system resources

## 🔄 Updates

### Updating the Container
1. **Edit Dockerfile:** Make necessary changes
2. **Rebuild:** "Dev Containers: Rebuild Container"
3. **Test:** Verify all functionality works

### Updating Dependencies
1. **Conan:** Update `conanfile.txt` or `conanfile.py`
2. **System packages:** Update `Dockerfile`
3. **VS Code extensions:** Update `devcontainer.json`

## 📚 Additional Resources

- [VS Code DevContainers Documentation](https://code.visualstudio.com/docs/remote/containers)
- [Docker Documentation](https://docs.docker.com/)
- [CMake Documentation](https://cmake.org/documentation/)
- [Conan Documentation](https://docs.conan.io/)
- [C++ Core Guidelines](https://isocpp.github.io/CppCoreGuidelines/)

Happy coding! 🚀