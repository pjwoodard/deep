#pragma once

#include <string>
#include <string_view>

using namespace std::literals;

namespace vertex_shaders {
constexpr static deep::types::VertexShaderSource hello_triangle{
    R"(
    #version 330 core
    layout (location = 0) in vec3 aPos;
    layout (location = 1) in vec3 aColor;
    layout (location = 2) in vec2 aTexCoord;

    out vec3 ourColor;
    out vec2 TexCoord;

    void main()
    {
        gl_Position = vec4(aPos, 1.0);
        ourColor = aColor;
        TexCoord = aTexCoord;
    }
)"sv
};
}

namespace fragment_shaders {
constexpr static deep::types::FragmentShaderSource hello_triangle{
    R"(
    #version 330 core
    out vec4 FragColor;

    in vec3 ourColor;
    in vec2 TexCoord;

    uniform sampler2D ourTexture;

    void main()
    {
        FragColor = texture(ourTexture, TexCoord);
    }
)"sv
};
}
