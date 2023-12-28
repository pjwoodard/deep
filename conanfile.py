import os

from conan import ConanFile


class DeepRecipe(ConanFile):
    build_policy = "missing"
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeToolchain", "CMakeDeps"

    default_options = {
        "glad/0.1.34:shared": False,
        "glad/0.1.34:no_loader": False,
        "glad/0.1.34:spec": "gl",
        "glad/0.1.34:gl_profile": "core",
        "glad/0.1.34:gl_version": 4.6,
        "fmt/10.1.1:header_only": True,
        "spdlog/1.12.0:header_only": True
    }

    def requirements(self):
        self.requires("catch2/3.4.0")
        self.requires("docopt.cpp/0.6.2")
        self.requires("fmt/10.1.1")
        self.requires("spdlog/1.12.0")
        self.requires("glfw/3.3.6")
        self.requires("glad/0.1.34")
        self.requires("namedtype/20190324")
        self.requires("stb/cci.20210713")
        self.requires("imgui/cci.20220621+1.88.docking")
        self.requires("magic_enum/0.9.5")

