cmake_minimum_required(VERSION 3.15...3.23)

project(CmakeConfigPackageTests LANGUAGES CXX)

# ---- Test as standalone project the exported config package ----

if(PROJECT_IS_TOP_LEVEL OR TEST_INSTALLED_VERSION)
  enable_testing()

  find_package(myproject CONFIG REQUIRED) # for intro, project_options, ...

  if(NOT TARGET myproject::project_options)
    message(FATAL_ERROR "Requiered config package not found!")
    return() # be strictly paranoid for Template Janitor github action! CK
  endif()
endif()

# ---- Dependencies ----

find_package(Catch2 CONFIG REQUIRED)

include(Catch)

add_library(catch_main OBJECT catch_main.cpp)
target_link_libraries(catch_main PUBLIC Catch2::Catch2)
target_link_libraries(catch_main PRIVATE myproject::project_options)
target_compile_definitions(catch_main
        PRIVATE
        _DISABLE_VECTOR_ANNOTATION)

add_executable(tests tests.cpp)
target_link_libraries(tests
    PRIVATE
        myproject::project_warnings
        myproject::project_options
        catch_main
        deep::math
)

target_compile_definitions(tests
        PRIVATE
          _DISABLE_VECTOR_ANNOTATION)

# automatically discover tests that are defined in catch based test files you can modify the unittests. Set TEST_PREFIX
# to whatever you want, or use different for different binaries
catch_discover_tests(tests
  TEST_PREFIX
    "unittests."
  REPORTER
    xml
  OUTPUT_DIR
    .
  OUTPUT_PREFIX
    "unittests."
  OUTPUT_SUFFIX
    .xml)