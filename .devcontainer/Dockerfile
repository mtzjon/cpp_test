# DevContainer Dockerfile for C++ Development
FROM ubuntu:22.04

# Prevent interactive prompts during package installation
ENV DEBIAN_FRONTEND=noninteractive

# Set locale
ENV LANG=C.UTF-8
ENV LC_ALL=C.UTF-8

# Install system dependencies
RUN apt-get update && apt-get install -y \
    # Build essentials
    build-essential \
    cmake \
    ninja-build \
    make \
    \
    # Compilers
    gcc-11 \
    g++-11 \
    clang-15 \
    clang++-15 \
    \
    # Code quality tools
    clang-format-15 \
    clang-tidy-15 \
    cppcheck \
    \
    # Debugging tools
    gdb \
    valgrind \
    strace \
    \
    # Version control
    git \
    git-lfs \
    \
    # Documentation
    doxygen \
    graphviz \
    \
    # Coverage tools
    lcov \
    gcovr \
    \
    # Utilities
    curl \
    wget \
    unzip \
    zip \
    tree \
    htop \
    vim \
    nano \
    jq \
    \
    # Python for Conan and scripts
    python3 \
    python3-pip \
    python3-venv \
    \
    # Networking tools
    netcat \
    telnet \
    \
    # SSL/TLS
    ca-certificates \
    \
    # Additional libraries
    libssl-dev \
    libcurl4-openssl-dev \
    \
    && rm -rf /var/lib/apt/lists/*

# Set up alternatives for compilers
RUN update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-11 110 \
    && update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-11 110 \
    && update-alternatives --install /usr/bin/clang clang /usr/bin/clang-15 150 \
    && update-alternatives --install /usr/bin/clang++ clang++ /usr/bin/clang++-15 150 \
    && update-alternatives --install /usr/bin/clang-format clang-format /usr/bin/clang-format-15 150 \
    && update-alternatives --install /usr/bin/clang-tidy clang-tidy /usr/bin/clang-tidy-15 150

# Install Python packages
RUN pip3 install --no-cache-dir \
    conan>=2.0 \
    cmake \
    pre-commit \
    black \
    flake8 \
    pytest \
    jinja2

# Create a non-root user
ARG USERNAME=developer
ARG USER_UID=1000
ARG USER_GID=${USER_UID}

RUN groupadd --gid ${USER_GID} ${USERNAME} \
    && useradd --uid ${USER_UID} --gid ${USER_GID} -m ${USERNAME} \
    && apt-get update \
    && apt-get install -y sudo \
    && echo ${USERNAME} ALL=\(root\) NOPASSWD:ALL > /etc/sudoers.d/${USERNAME} \
    && chmod 0440 /etc/sudoers.d/${USERNAME} \
    && rm -rf /var/lib/apt/lists/*

# Switch to non-root user
USER ${USERNAME}
WORKDIR /home/${USERNAME}

# Set up Conan
RUN conan profile detect --force

# Create workspace directory
RUN sudo mkdir -p /workspace && sudo chown ${USERNAME}:${USERNAME} /workspace

# Set up shell environment
RUN echo 'export PATH="/home/${USERNAME}/.local/bin:$PATH"' >> ~/.bashrc \
    && echo 'export CMAKE_GENERATOR=Ninja' >> ~/.bashrc \
    && echo 'export CMAKE_BUILD_PARALLEL_LEVEL=$(nproc)' >> ~/.bashrc \
    && echo 'alias ll="ls -alF"' >> ~/.bashrc \
    && echo 'alias la="ls -A"' >> ~/.bashrc \
    && echo 'alias l="ls -CF"' >> ~/.bashrc \
    && echo 'alias build="./scripts/build.sh"' >> ~/.bashrc \
    && echo 'alias test="./scripts/test.sh"' >> ~/.bashrc \
    && echo 'alias format="./scripts/format.sh"' >> ~/.bashrc \
    && echo 'alias lint="./scripts/lint.sh"' >> ~/.bashrc

# Install additional development tools
RUN curl -fsSL https://github.com/microsoft/vscode-cpptools/releases/download/v1.17.5/cpptools-linux.vsix -o /tmp/cpptools.vsix \
    && rm -f /tmp/cpptools.vsix

# Set working directory
WORKDIR /workspace

# Set up Git configuration (will be overridden by user's git config)
RUN git config --global init.defaultBranch main \
    && git config --global core.editor "code --wait" \
    && git config --global merge.tool "vscode" \
    && git config --global mergetool.vscode.cmd 'code --wait $MERGED' \
    && git config --global diff.tool "vscode" \
    && git config --global difftool.vscode.cmd 'code --wait --diff $LOCAL $REMOTE'

# Install vcpkg (alternative to Conan)
RUN git clone https://github.com/Microsoft/vcpkg.git /home/${USERNAME}/vcpkg \
    && /home/${USERNAME}/vcpkg/bootstrap-vcpkg.sh \
    && echo 'export VCPKG_ROOT="/home/${USERNAME}/vcpkg"' >> ~/.bashrc \
    && echo 'export PATH="$VCPKG_ROOT:$PATH"' >> ~/.bashrc

# Create directories for caching
RUN mkdir -p /home/${USERNAME}/.conan2 \
    && mkdir -p /home/${USERNAME}/.cache/pip \
    && mkdir -p /home/${USERNAME}/.cache/cmake

# Set environment variables
ENV CMAKE_GENERATOR=Ninja
ENV CMAKE_BUILD_PARALLEL_LEVEL=4
ENV CONAN_USER_HOME=/home/${USERNAME}
ENV VCPKG_ROOT=/home/${USERNAME}/vcpkg

# Expose common development ports
EXPOSE 8080 3000 8000 9000

# Set up entrypoint
COPY .devcontainer/entrypoint.sh /usr/local/bin/entrypoint.sh
RUN sudo chmod +x /usr/local/bin/entrypoint.sh

ENTRYPOINT ["/usr/local/bin/entrypoint.sh"]
CMD ["bash"]