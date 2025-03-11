add_library(bitset src/bitset.cpp)
add_library(deep::bitset ALIAS bitset)

target_include_directories(bitset
    PUBLIC
        include
)

target_link_libraries(bitset
    PUBLIC
        myproject_warnings
        myproject_options
)
