add_library(deep src/deep.cpp)
add_library(deep::deep ALIAS deep)

target_include_directories(deep
        PUBLIC
            include/)

target_link_libraries(deep
        PUBLIC
            deep::window
            deep::types
            deep::events
            deep::logger
            deep::layer
        PRIVATE
            project_warnings
            fmt::fmt)