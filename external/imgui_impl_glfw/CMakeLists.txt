add_library(imgui_impl_glfw imgui_impl_glfw.cpp)
add_library(external::imgui_impl_glfw ALIAS imgui_impl_glfw)

target_include_directories(
        imgui_impl_glfw
        PUBLIC
            .)

target_link_libraries(
        imgui_impl_glfw
        PUBLIC
            project_options
            project_warnings
            imgui::imgui
            glfw::glfw
)

