add_library(deep src/deep.cpp)
add_library(deep::deep ALIAS deep)

target_include_directories(deep
        PUBLIC
            include/)

target_link_libraries(deep
        PUBLIC
            myproject_warnings
            myproject_options
            deep::window
            deep::types
            deep::events
            deep::logger
            deep::layer
        PRIVATE
            fmt::fmt-header-only
            )