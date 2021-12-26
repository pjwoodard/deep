add_library(shader
        src/opengl_program.cpp
        src/opengl_shader.cpp)

add_library(deep::shader ALIAS shader)

target_include_directories(shader PUBLIC include/)

target_link_libraries(shader
        PRIVATE
        glfw
        fmt::fmt
        deep::types)
