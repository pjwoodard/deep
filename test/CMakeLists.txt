cmake_minimum_required(VERSION 3.15...3.23)

project(deep_tests LANGUAGES CXX)

enable_testing()

find_package(Catch2 3 REQUIRED)

add_executable(
  deep_tests 
    test_stack_allocator.cpp)

target_link_libraries(
 deep_tests 
    PRIVATE
    deep::memory
    myproject::myproject_warnings
    myproject::myproject_options
    Catch2::Catch2WithMain)

include(CTest)
include(Catch)

catch_discover_tests(deep_tests 
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    EXTRA_ARGS "--test-dir ${CMAKE_CURRENT_BINARY_DIR}"
)
