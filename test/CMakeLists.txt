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

find_package(Catch2 3 REQUIRED)

add_executable(tests tests.cpp)
target_link_libraries(tests
    PRIVATE
        # myproject::project_warnings
        # myproject::project_options
        Catch2::Catch2WithMain
        deep::math
)

target_compile_definitions(tests
        PRIVATE 
          _DISABLE_VECTOR_ANNOTATION=1
          _DISABLE_STRING_ANNOTATION=1)
