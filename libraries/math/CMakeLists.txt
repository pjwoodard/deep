add_library(math INTERFACE)
add_library(deep::math ALIAS math)

target_include_directories(math INTERFACE include/)
target_sources(math INTERFACE include/math/matrix.h)

target_link_libraries(math
        INTERFACE
            deep::types
            project_warnings
        )
