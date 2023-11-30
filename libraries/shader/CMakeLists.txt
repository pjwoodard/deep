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
            glfw
            glad::glad
            fmt::fmt-header-only
            deep::types
            project_warnings
        )

target_compile_definitions(
    shader
    PUBLIC 
        _SILENCE_ALL_MS_EXT_DEPRECATION_WARNINGS=1)