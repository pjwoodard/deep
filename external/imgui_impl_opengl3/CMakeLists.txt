add_library(imgui_impl_opengl3 imgui_impl_opengl3.cpp)
add_library(external::imgui_impl_opengl3 ALIAS imgui_impl_opengl3)

target_include_directories(
        imgui_impl_opengl3
        PUBLIC
            .)

target_link_libraries(
        imgui_impl_opengl3
        PUBLIC
            project_options
            project_warnings
            imgui::imgui
            glad::glad
)

target_compile_definitions(imgui_impl_opengl3 PUBLIC IMGUI_IMPL_OPENGL_LOADER_CUSTOM)

