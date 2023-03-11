add_library(math INTERFACE)
add_library(deep::math ALIAS math)

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    if (CMAKE_CXX_COMPILER_FRONTEND_VARIANT STREQUAL "MSVC")
        # using clang with clang-cl front end
    elseif (CMAKE_CXX_COMPILER_FRONTEND_VARIANT STREQUAL "GNU")
        # using clang with regular front end
    endif()
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(COMPILE_OPTIONS --march=native)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Intel")
    # using Intel C++
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    # using Visual Studio C++
endif()

target_compile_options(math
    PRIVATE
        ${COMPILE_OPTIONS}
)

target_include_directories(math
    INTERFACE
        include
)

target_sources(math
    INTERFACE
        include/math/vector.h
)

target_link_libraries(math
    INTERFACE
        deep::types
        project_warnings
)
