# Contributing to CppTemplate

Thank you for your interest in contributing to CppTemplate! This document provides guidelines and information for contributors.

## Table of Contents

- [Code of Conduct](#code-of-conduct)
- [Getting Started](#getting-started)
- [Development Process](#development-process)
- [Coding Standards](#coding-standards)
- [Testing](#testing)
- [Documentation](#documentation)
- [Pull Request Process](#pull-request-process)
- [Issue Reporting](#issue-reporting)

## Code of Conduct

This project adheres to a code of conduct that ensures a welcoming environment for all contributors. By participating, you are expected to uphold this code.

## Getting Started

### Prerequisites

- C++20 capable compiler (GCC 11+, Clang 15+, MSVC 2019+)
- CMake 3.20+
- Python 3.8+ (for Conan)
- Git

### Setting up the Development Environment

1. **Fork and clone the repository:**
   ```bash
   git clone https://github.com/yourusername/cpp-template.git
   cd cpp-template
   ```

2. **Install dependencies:**
   ```bash
   pip install "conan>=2.0"
   conan profile detect --force
   ```

3. **Build the project:**
   ```bash
   ./scripts/build.sh -t Debug
   ```

4. **Run tests to ensure everything works:**
   ```bash
   ./scripts/test.sh
   ```

## Development Process

### Branching Strategy

- `main` - Stable release branch
- `develop` - Development branch for integration
- `feature/*` - Feature development branches
- `bugfix/*` - Bug fix branches
- `hotfix/*` - Critical bug fixes for main

### Workflow

1. Create a feature branch from `develop`
2. Make your changes
3. Ensure all tests pass
4. Submit a pull request

## Coding Standards

### C++ Standards

- Use **C++20** features where appropriate
- Follow **Core Guidelines** principles
- Use **RAII** for resource management
- Prefer **smart pointers** over raw pointers
- Use **const** wherever possible

### Code Style

We use `clang-format` for automatic code formatting. The configuration is in `.clang-format`.

**Format your code before committing:**
```bash
./scripts/format.sh --fix
```

### Naming Conventions

- **Classes/Structs**: `PascalCase`
- **Functions/Variables**: `snake_case`
- **Constants**: `PascalCase`
- **Namespaces**: `snake_case`
- **Files**: `snake_case.hpp/cpp`
- **Private members**: trailing underscore `member_`

### Example:

```cpp
namespace cpp_template::utils {

class StringProcessor {
public:
    StringProcessor() = default;
    
    [[nodiscard]] std::string process_text(std::string_view input) const;
    
private:
    std::string buffer_;
    bool is_initialized_ = false;
};

constexpr int MaxBufferSize = 1024;

} // namespace cpp_template::utils
```

### Include Guidelines

- Use `#pragma once` for header guards
- Include standard headers first, then third-party, then project headers
- Use forward declarations when possible
- Group includes logically and separate with blank lines

```cpp
#pragma once

#include <memory>
#include <string>
#include <vector>

#include <fmt/format.h>
#include <spdlog/spdlog.h>

#include "core/calculator.hpp"
#include "utils/string_utils.hpp"
```

## Testing

### Unit Tests

- Write tests for all new functionality
- Use Google Test framework
- Aim for high code coverage
- Test edge cases and error conditions

### Running Tests

```bash
# Run all tests
./scripts/test.sh

# Run specific test suite
./scripts/test.sh --filter "*Calculator*"

# Run with memory checking
./scripts/test.sh --memcheck

# Run with coverage
./scripts/build.sh -t Debug --coverage
```

### Test Structure

```cpp
#include <gtest/gtest.h>
#include "core/calculator.hpp"

class CalculatorTest : public ::testing::Test {
protected:
    void SetUp() override {
        calculator = std::make_unique<Calculator>();
    }
    
    std::unique_ptr<Calculator> calculator;
};

TEST_F(CalculatorTest, AddTwoPositiveNumbers) {
    EXPECT_DOUBLE_EQ(calculator->add(2.0, 3.0), 5.0);
}
```

## Documentation

### Code Documentation

- Use Doxygen-style comments for public APIs
- Document complex algorithms and design decisions
- Include examples in documentation when helpful

```cpp
/**
 * @brief Calculate the factorial of a number
 * 
 * This function computes the factorial using an iterative approach
 * for better performance and stack safety.
 * 
 * @param n The number to compute factorial for (must be non-negative)
 * @return The factorial of n
 * @throws std::invalid_argument if n is negative
 * 
 * @example
 * ```cpp
 * auto result = factorial(5); // Returns 120
 * ```
 */
[[nodiscard]] uint64_t factorial(int n);
```

### Generate Documentation

```bash
./scripts/build.sh --docs
```

## Pull Request Process

### Before Submitting

1. **Ensure your code builds and tests pass:**
   ```bash
   ./scripts/build.sh -t Debug
   ./scripts/test.sh
   ```

2. **Format your code:**
   ```bash
   ./scripts/format.sh --fix
   ```

3. **Run static analysis:**
   ```bash
   ./scripts/lint.sh
   ```

4. **Update documentation if needed**

5. **Write/update tests for new functionality**

### PR Requirements

- **Clear description** of changes and motivation
- **Tests** for new functionality
- **Documentation** updates if applicable
- **No breaking changes** without discussion
- **Clean commit history** (squash if necessary)

### PR Template

```markdown
## Description
Brief description of changes

## Type of Change
- [ ] Bug fix
- [ ] New feature
- [ ] Breaking change
- [ ] Documentation update

## Testing
- [ ] Unit tests pass
- [ ] Integration tests pass
- [ ] Manual testing completed

## Checklist
- [ ] Code follows style guidelines
- [ ] Self-review completed
- [ ] Documentation updated
- [ ] Tests added/updated
```

## Issue Reporting

### Bug Reports

When reporting bugs, please include:

- **Clear description** of the issue
- **Steps to reproduce** the problem
- **Expected vs actual behavior**
- **Environment details** (OS, compiler, versions)
- **Minimal code example** if applicable

### Feature Requests

For feature requests, please include:

- **Clear description** of the proposed feature
- **Use case** and motivation
- **Possible implementation** approach
- **Breaking changes** if any

### Issue Labels

- `bug` - Something isn't working
- `enhancement` - New feature or improvement
- `documentation` - Documentation improvements
- `good first issue` - Good for newcomers
- `help wanted` - Extra attention needed

## Static Analysis

We use `clang-tidy` for static analysis. The configuration is in `.clang-tidy`.

**Run static analysis:**
```bash
./scripts/lint.sh
```

**Common issues to avoid:**
- Memory leaks
- Uninitialized variables
- Unused variables/functions
- Performance anti-patterns
- Security vulnerabilities

## Continuous Integration

All pull requests are automatically tested with:

- **Multiple compilers** (GCC, Clang, MSVC)
- **Multiple platforms** (Linux, Windows, macOS)
- **Different build types** (Debug, Release)
- **Static analysis** (clang-tidy)
- **Code formatting** checks
- **Memory testing** (Valgrind)
- **Coverage analysis**

## Performance Considerations

- **Profile before optimizing**
- **Prefer standard library algorithms**
- **Use appropriate data structures**
- **Avoid premature optimization**
- **Consider memory locality**
- **Use move semantics where appropriate**

## Security Guidelines

- **Validate all inputs**
- **Use safe string operations**
- **Avoid buffer overflows**
- **Handle errors gracefully**
- **Use secure random numbers**
- **Follow OWASP guidelines**

## Questions and Support

- **Documentation**: Check the README and inline documentation
- **Issues**: Search existing issues before creating new ones
- **Discussions**: Use GitHub Discussions for questions
- **Email**: Contact maintainers for sensitive issues

## Recognition

Contributors will be recognized in:
- README.md acknowledgments
- Release notes
- Contributor graphs

Thank you for contributing to CppTemplate! 🚀