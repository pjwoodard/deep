add_library(events INTERFACE)
add_library(deep::events ALIAS events)

target_include_directories(
        events
        INTERFACE 
            include/)

target_sources(
        types
        INTERFACE
            include/events/event_t.h
        include/events/signal.h
        include/events/events.h)

target_link_libraries(
        events
        INTERFACE
            project_warnings
            deep::types
            deep::logger)