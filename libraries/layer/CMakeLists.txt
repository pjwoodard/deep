add_library(layer
        src/layer.cpp)

add_library(deep::layer ALIAS layer)

target_include_directories(
        layer
        PUBLIC
            include/)


target_link_libraries(
        layer
        PRIVATE
            project_warnings
            project_options
            fmt::fmt
)
