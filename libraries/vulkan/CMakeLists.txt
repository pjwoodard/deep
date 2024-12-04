add_library(vulkan src/vulkan.cpp)
add_library(vulkan::vulkan ALIAS vulkan)

target_include_directories(vulkan
        PUBLIC
            include/)

target_link_libraries(vulkan
        PUBLIC
            myproject_warnings
            myproject_options
        PRIVATE
            fmt::fmt-header-only
            )