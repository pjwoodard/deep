add_library(math src/vector.cpp)
add_library(deep::math ALIAS math)

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    if (CMAKE_CXX_COMPILER_FRONTEND_VARIANT STREQUAL "MSVC")
        set(COMPILE_OPTIONS /Oi /fp:fast /Gv)
    elseif (CMAKE_CXX_COMPILER_FRONTEND_VARIANT STREQUAL "GNU")
        set(COMPILE_OPTIONS -march=native -msse2)
    endif()
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(COMPILE_OPTIONS -march=native -msse2)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(COMPILE_OPTIONS /Oi /fp:fast /Gv)
endif()

target_compile_options(math
    PRIVATE
        ${COMPILE_OPTIONS}
)

target_include_directories(math
    PUBLIC
        include
)

target_link_libraries(math
    PUBLIC
        deep::types
        project_warnings
)
