add_library(deep src/deep.cpp)
add_library(deep::deep ALIAS deep)

target_include_directories(deep
        PUBLIC
            include/)

target_link_libraries(deep
        PRIVATE
            deep::types
            deep::events)