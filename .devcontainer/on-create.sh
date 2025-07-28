#!/bin/bash

# On-create script for DevContainer
set -e

echo "🔧 Running on-create setup..."

# Function to print colored output
print_info() {
    echo -e "\033[1;34m[INFO]\033[0m $1"
}

print_success() {
    echo -e "\033[1;32m[SUCCESS]\033[0m $1"
}

# Create necessary directories
print_info "Creating project directories..."
mkdir -p logs build .vscode

# Set up basic VS Code settings if they don't exist
if [ ! -f ".vscode/settings.json" ]; then
    print_info "Creating VS Code settings..."
    cat > .vscode/settings.json << 'EOF'
{
    "cmake.buildDirectory": "${workspaceFolder}/build",
    "cmake.generator": "Ninja",
    "cmake.configureOnOpen": true,
    "files.associations": {
        "*.hpp": "cpp",
        "*.tpp": "cpp"
    },
    "C_Cpp.default.configurationProvider": "ms-vscode.cmake-tools",
    "C_Cpp.default.cppStandard": "c++20",
    "C_Cpp.default.intelliSenseMode": "linux-gcc-x64",
    "editor.formatOnSave": true,
    "clang-format.executable": "/usr/bin/clang-format",
    "clang-tidy.executable": "/usr/bin/clang-tidy"
}
EOF
fi

# Set up basic launch configuration for debugging
if [ ! -f ".vscode/launch.json" ]; then
    print_info "Creating VS Code launch configuration..."
    cat > .vscode/launch.json << 'EOF'
{
    "version": "0.2.0",
    "configurations": [
        {
            "name": "Debug Main App",
            "type": "cppdbg",
            "request": "launch",
            "program": "${workspaceFolder}/build/bin/cpp_template_main",
            "args": [],
            "stopAtEntry": false,
            "cwd": "${workspaceFolder}",
            "environment": [],
            "externalConsole": false,
            "MIMode": "gdb",
            "setupCommands": [
                {
                    "description": "Enable pretty-printing for gdb",
                    "text": "-enable-pretty-printing",
                    "ignoreFailures": true
                }
            ],
            "preLaunchTask": "build"
        },
        {
            "name": "Debug CLI App",
            "type": "cppdbg",
            "request": "launch",
            "program": "${workspaceFolder}/build/bin/cpp_template_cli",
            "args": [],
            "stopAtEntry": false,
            "cwd": "${workspaceFolder}",
            "environment": [],
            "externalConsole": false,
            "MIMode": "gdb",
            "setupCommands": [
                {
                    "description": "Enable pretty-printing for gdb",
                    "text": "-enable-pretty-printing",
                    "ignoreFailures": true
                }
            ],
            "preLaunchTask": "build"
        },
        {
            "name": "Debug Server App",
            "type": "cppdbg",
            "request": "launch",
            "program": "${workspaceFolder}/build/bin/cpp_template_server",
            "args": [],
            "stopAtEntry": false,
            "cwd": "${workspaceFolder}",
            "environment": [],
            "externalConsole": false,
            "MIMode": "gdb",
            "setupCommands": [
                {
                    "description": "Enable pretty-printing for gdb",
                    "text": "-enable-pretty-printing",
                    "ignoreFailures": true
                }
            ],
            "preLaunchTask": "build"
        }
    ]
}
EOF
fi

# Set up tasks for building and testing
if [ ! -f ".vscode/tasks.json" ]; then
    print_info "Creating VS Code tasks..."
    cat > .vscode/tasks.json << 'EOF'
{
    "version": "2.0.0",
    "tasks": [
        {
            "label": "build",
            "type": "shell",
            "command": "./scripts/build.sh",
            "group": {
                "kind": "build",
                "isDefault": true
            },
            "presentation": {
                "echo": true,
                "reveal": "always",
                "focus": false,
                "panel": "shared"
            },
            "problemMatcher": ["$gcc"]
        },
        {
            "label": "build-debug",
            "type": "shell",
            "command": "./scripts/build.sh",
            "args": ["-t", "Debug"],
            "group": "build",
            "presentation": {
                "echo": true,
                "reveal": "always",
                "focus": false,
                "panel": "shared"
            },
            "problemMatcher": ["$gcc"]
        },
        {
            "label": "test",
            "type": "shell",
            "command": "./scripts/test.sh",
            "group": "test",
            "presentation": {
                "echo": true,
                "reveal": "always",
                "focus": false,
                "panel": "shared"
            },
            "dependsOn": "build"
        },
        {
            "label": "format",
            "type": "shell",
            "command": "./scripts/format.sh",
            "args": ["--fix"],
            "group": "build",
            "presentation": {
                "echo": true,
                "reveal": "always",
                "focus": false,
                "panel": "shared"
            }
        },
        {
            "label": "lint",
            "type": "shell",
            "command": "./scripts/lint.sh",
            "group": "build",
            "presentation": {
                "echo": true,
                "reveal": "always",
                "focus": false,
                "panel": "shared"
            }
        },
        {
            "label": "clean",
            "type": "shell",
            "command": "rm",
            "args": ["-rf", "build/"],
            "group": "build",
            "presentation": {
                "echo": true,
                "reveal": "always",
                "focus": false,
                "panel": "shared"
            }
        }
    ]
}
EOF
fi

print_success "On-create setup completed!"