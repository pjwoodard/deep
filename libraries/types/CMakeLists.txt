add_library(types INTERFACE)
add_library(deep::types ALIAS types)

target_include_directories(types
        INTERFACE
            include/)

target_sources(types
        INTERFACE
            include/types/deep_concepts.h
            include/types/deep_types.h)

target_link_libraries(types
        INTERFACE
            project_options
            project_warnings
            namedtype::namedtype)