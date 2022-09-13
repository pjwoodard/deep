add_library(imgui_impl_opengl3 imgui_impl_opengl3.cpp)
add_library(external::imgui_impl_opengl3 ALIAS imgui_impl_opengl3)

target_include_directories(
        imgui_impl_opengl3
        PUBLIC
            .)

target_link_libraries(
        imgui_impl_opengl3
        PRIVATE
            project_options
            project_warnings
            imgui::imgui
)
