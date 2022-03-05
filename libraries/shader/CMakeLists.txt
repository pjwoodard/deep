add_library(shader
        src/opengl_program.cpp
        src/opengl_shader.cpp)

add_library(deep::shader ALIAS shader)

target_include_directories(shader
        PUBLIC
            include/
        PRIVATE
            private/)

target_link_libraries(shader
        PRIVATE
        glfw::glfw
        glad::glad
        fmt::fmt
        deep::types)
