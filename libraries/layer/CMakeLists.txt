add_library(layer INTERFACE)
add_library(deep::layer ALIAS layer)

target_include_directories(
        layer
        INTERFACE 
            include)


target_link_libraries(
        layer
        INTERFACE 
            myproject_warnings
            myproject_options
            deep::events
            deep::logger
            fmt::fmt-header-only
)

if(WIN32)
    target_compile_definitions(
        layer 
        INTERFACE 
            _SILENCE_ALL_MS_EXT_DEPRECATION_WARNINGS)
endif()