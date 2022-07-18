add_library(context INTERFACE)
add_library(deep::context ALIAS context)

target_include_directories(context INTERFACE include/)
target_sources(context INTERFACE
        include/context/glfw_context.h)

target_link_libraries(context
        INTERFACE
            project_warnings
            glfw)