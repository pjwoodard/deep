cmake_minimum_required(VERSION 3.15...3.23)

project(CmakeConfigPackageTests LANGUAGES CXX)

# ---- Dependencies ----
find_package(Catch2 3 REQUIRED)

add_executable(tests tests.cpp)
target_link_libraries(tests
    PRIVATE
        Catch2::Catch2WithMain
        deep::math
)

target_compile_definitions(tests
        PRIVATE 
          _DISABLE_VECTOR_ANNOTATION=1
          _DISABLE_STRING_ANNOTATION=1)
