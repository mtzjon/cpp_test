# Multi-stage Dockerfile for CppTemplate
FROM ubuntu:22.04 AS base

# Install system dependencies
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    git \
    python3 \
    python3-pip \
    clang \
    clang-format \
    clang-tidy \
    valgrind \
    lcov \
    doxygen \
    graphviz \
    && rm -rf /var/lib/apt/lists/*

# Install Conan
RUN pip3 install "conan>=2.0"

# Create a non-root user
RUN useradd -m -s /bin/bash developer
USER developer
WORKDIR /home/developer

# Setup Conan profile
RUN conan profile detect --force

# Development stage
FROM base AS development

# Copy source code
COPY --chown=developer:developer . /home/developer/cpp-template
WORKDIR /home/developer/cpp-template

# Install dependencies
RUN conan install . --output-folder=build --build=missing -s build_type=Release

# Configure project
RUN cmake -B build \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_TOOLCHAIN_FILE=build/conan_toolchain.cmake \
    -DBUILD_TESTS=ON

# Build stage
FROM development AS build

# Build the project
RUN cmake --build build --config Release --parallel $(nproc)

# Run tests
RUN cd build && ctest --build-config Release --output-on-failure --parallel $(nproc)

# Production stage
FROM ubuntu:22.04 AS production

# Install minimal runtime dependencies
RUN apt-get update && apt-get install -y \
    libstdc++6 \
    && rm -rf /var/lib/apt/lists/*

# Create app user
RUN useradd -m -s /bin/bash app
USER app
WORKDIR /home/app

# Copy the built executable
COPY --from=build --chown=app:app /home/developer/cpp-template/build/bin/cpp-template /usr/local/bin/

# Create logs directory
RUN mkdir -p logs

# Set the entrypoint
ENTRYPOINT ["cpp-template"]

# Testing stage
FROM development AS testing

# Install additional testing tools
USER root
RUN apt-get update && apt-get install -y \
    gdb \
    strace \
    && rm -rf /var/lib/apt/lists/*

USER developer

# Build with debug info and sanitizers
RUN conan install . --output-folder=build-debug --build=missing -s build_type=Debug

RUN cmake -B build-debug \
    -DCMAKE_BUILD_TYPE=Debug \
    -DCMAKE_TOOLCHAIN_FILE=build-debug/conan_toolchain.cmake \
    -DBUILD_TESTS=ON \
    -DENABLE_SANITIZERS=ON

RUN cmake --build build-debug --config Debug --parallel $(nproc)

# Run tests with sanitizers
RUN cd build-debug && ctest --build-config Debug --output-on-failure --parallel $(nproc)

# Documentation stage
FROM development AS documentation

# Build documentation
RUN cmake -B build-docs \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_TOOLCHAIN_FILE=build/conan_toolchain.cmake \
    -DBUILD_DOCS=ON

RUN cmake --build build-docs --target docs

# Copy generated documentation
RUN mkdir -p /tmp/docs && cp -r build-docs/docs/doxygen/html/* /tmp/docs/

# Final documentation image
FROM nginx:alpine AS docs

COPY --from=documentation /tmp/docs /usr/share/nginx/html

EXPOSE 80

# Health check for production image
FROM production AS final

HEALTHCHECK --interval=30s --timeout=3s --start-period=5s --retries=3 \
    CMD cpp-template --version || exit 1