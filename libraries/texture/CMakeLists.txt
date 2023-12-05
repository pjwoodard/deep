add_library(texture src/opengl_texture.cpp)
add_library(deep::texture ALIAS texture)

target_include_directories(texture
        PUBLIC
            include/)

target_link_libraries(texture
        PRIVATE
            myproject_warnings
            myproject_options
            glfw
            glad::glad
            stb::stb
        )
