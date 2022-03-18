add_library(events INTERFACE)
add_library(deep::events ALIAS events)

target_include_directories(events
        INTERFACE 
            include/)

target_link_libraries(deep INTERFACE deep::types)