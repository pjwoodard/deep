add_library(vulkan src/vulkan_api.cpp)
add_library(deep::vulkan ALIAS vulkan)

target_include_directories(vulkan
        PUBLIC
            include/)

target_link_libraries(vulkan
        PUBLIC
            myproject_warnings
            myproject_options
            Vulkan::Vulkan
        PRIVATE
            fmt::fmt-header-only
            glfw
)

target_compile_features(vulkan PRIVATE cxx_std_23)