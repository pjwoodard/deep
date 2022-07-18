add_library(events INTERFACE)
add_library(deep::events ALIAS events)

target_include_directories(events
        INTERFACE 
            include/)

target_sources(types
        INTERFACE
            include/events/event.h)

target_link_libraries(events
        INTERFACE
            project_warnings
            deep::types)