from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMake, cmake_layout, CMakeDeps


class CppTemplateConan(ConanFile):
    name = "cpp-template"
    version = "1.0.0"
    package_type = "application"

    # Optional metadata
    license = "MIT"
    author = "Your Name <your.email@example.com>"
    url = "https://github.com/yourusername/cpp-template"
    description = "A production-quality C++ template"
    topics = ("c++", "template", "cmake")

    # Binary configuration
    settings = "os", "compiler", "build_type", "arch"
    options = {
        "shared": [True, False],
        "fPIC": [True, False],
        "with_tests": [True, False],
    }
    default_options = {
        "shared": False,
        "fPIC": True,
        "with_tests": True,
    }

    # Sources are located in the same place as this recipe, copy them to the recipe
    exports_sources = "CMakeLists.txt", "src/*", "tests/*", "cmake/*", "include/*"

    def config_options(self):
        if self.settings.os == "Windows":
            self.options.rm_safe("fPIC")

    def configure(self):
        if self.options.shared:
            self.options.rm_safe("fPIC")

    def layout(self):
        cmake_layout(self)

    def requirements(self):
        self.requires("fmt/10.2.1")
        self.requires("spdlog/1.12.0")
        if self.options.with_tests:
            self.requires("gtest/1.14.0")

    def build_requirements(self):
        self.tool_requires("cmake/[>=3.20]")

    def generate(self):
        deps = CMakeDeps(self)
        deps.generate()
        tc = CMakeToolchain(self)
        tc.variables["BUILD_TESTS"] = self.options.with_tests
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()

    def package_info(self):
        self.cpp_info.libs = ["cpp-template"]
        self.cpp_info.includedirs = ["include"]