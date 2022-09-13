add_library(imgui src/imgui_layer.cpp)
add_library(deep::imgui ALIAS imgui)

target_include_directories(
        imgui
        PUBLIC
            include/)

target_link_libraries(
        imgui
        PUBLIC
            deep::deep
            deep::events
        PRIVATE
            project_options
            project_warnings
            imgui::imgui
            glfw::glfw
            external::imgui_impl_opengl3
)
