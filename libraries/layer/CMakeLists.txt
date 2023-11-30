add_library(layer
        src/layer.cpp
        src/layer_stack.cpp)

add_library(deep::layer ALIAS layer)

target_include_directories(
        layer
        PUBLIC
            include)


target_link_libraries(
        layer
        PUBLIC
            deep::events
            deep::logger
        PRIVATE
            project_warnings
            project_options
            fmt::fmt-header-only
)

if(WIN32)
    target_compile_definitions(
        layer 
        PUBLIC 
            _SILENCE_ALL_MS_EXT_DEPRECATION_WARNINGS)
endif()