add_library(
    memory 
        src/global_memory_overrides.cpp)
        
add_library(deep::memory ALIAS memory)

target_include_directories(memory
    PUBLIC
        include
)

target_link_libraries(memory
    PUBLIC
        myproject_warnings
        myproject_options
        deep::types
        deep::logger
)
