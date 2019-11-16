from conans import ConanFile, CMake

class GodotTgPlugin(ConanFile):
    name = "godot-ia-plugin"
    version = "0.1"

    generators = "cmake_find_package"

    def requirements(self):
        self.requires("godot-cpp/[~=3.1.0-0]")
        self.requires("tgbot/89ec4e3")

    def _configure_cmake(self):
        cmake = CMake(self)
        cmake.configure()
        return cmake

    def build(self):
        cmake = self._configure_cmake()
        cmake.build()

    def package(self):
        cmake = self._configure_cmake()
        cmake.install()
