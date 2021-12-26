#pragma once

#include <string_view>
#include <string>

using namespace std::literals;

namespace vertex_shaders
{
constexpr static auto hello_triangle =
    R"(
    #version 330 core
    layout (location = 0) in vec3 aPos;
    layout (location = 1) in vec3 aColor;

    out vec3 ourColor;

    uniform float horizontalOffset;

    void main()
    {
        gl_Position = vec4(aPos.x + horizontalOffset, aPos.y, aPos.z, 1.0);
        ourColor = aColor;
    }
)"sv;
}

namespace fragment_shaders
{
constexpr static auto hello_triangle =
R"(
    #version 330 core
    out vec4 FragColor;
    in vec3 ourColor;
    in vec3 ourPos;

    void main()
    {
        FragColor = vec4(ourColor, 1.0);
    }
)"sv;
}
