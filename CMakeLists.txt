cmake_minimum_required(VERSION 3.16...3.23)

# Not ideal to use this global variable, but necessary to make sure
# that tooling and projects use the same version
if (NOT DEFINED CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 20)
endif()

# strongly encouraged to enable this globally to avoid conflicts between
# -Wpedantic being enabled and -std=c++20 and -std=gnu++20 for example
# when compiling with PCH enabled
set(CMAKE_CXX_EXTENSIONS OFF)

# We always want to generate compile commands
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

# Set the project name and language
project(
  deep
  VERSION 0.0.1
  DESCRIPTION ""
  HOMEPAGE_URL "%%myurl%%"
  LANGUAGES CXX C)

include(project_options.cmake)

myproject_setup_options()
myproject_local_options()

target_compile_features(myproject_options INTERFACE cxx_std_${CMAKE_CXX_STANDARD})

add_library(myproject::myproject_options ALIAS myproject_options)
add_library(myproject::myproject_warnings ALIAS myproject_warnings)

# Packages are project-wide
find_package(fmt)
find_package(spdlog)
find_package(docopt)
find_package(glfw3)
find_package(glad)
find_package(namedtype)
find_package(stb)
find_package(imgui)

# Adding the src:
add_subdirectory(executable)
add_subdirectory(external)
add_subdirectory(libraries)

# Adding the tests:
option(ENABLE_TESTING "Enable the tests" ${PROJECT_IS_TOP_LEVEL})
if(ENABLE_TESTING)
  message(AUTHOR_WARNING "Building Tests. Be sure to check out test/constexpr_tests.cpp for constexpr testing")
  add_subdirectory(test)
endif()

option(ENABLE_FUZZING "Enable the fuzz tests" OFF)
if(ENABLE_FUZZING)
  message(AUTHOR_WARNING "Building Fuzz Tests, using fuzzing sanitizer https://www.llvm.org/docs/LibFuzzer.html")
  add_subdirectory(fuzz_test)
endif()

# set the startup project for the "play" button in MSVC
set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT deep_exe)
