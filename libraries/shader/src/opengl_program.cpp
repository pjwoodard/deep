#include <array>
#include <cassert>
#include <string_view>

#include <fmt/format.h>

#include "shader/opengl_shader.h"
#include "program/opengl_program.h"

OpenGLProgram::OpenGLProgram(deep::types::VertexShaderSource vertex_source,
                             deep::types::FragmentShaderSource fragment_source,
                             std::optional<deep::types::GeometryShaderSource> geometry_source)
  : gl_program_id_{ glCreateProgram() }
{
    const OpenGLShader vertex_shader{GLShaderType::VertexShader, vertex_source.get()};
    const OpenGLShader fragment_shader{GLShaderType::FragmentShader, fragment_source.get()};
    std::optional<OpenGLShader> geometry_shader;

    glAttachShader(gl_program_id_, vertex_shader.id());
    glAttachShader(gl_program_id_, fragment_shader.id());

    if(geometry_source)
    {
        geometry_shader.emplace(GLShaderType::VertexShader, geometry_source.value().get());
        glAttachShader(gl_program_id_, geometry_shader.value().id());
    }

    glLinkProgram(gl_program_id_);

    // TODO: Clean this up, figure out error handling method
    int success{ 0 };
    glGetProgramiv(gl_program_id_, GL_LINK_STATUS, &success);
    constexpr int32_t info_log_buff_size{ 512 };
    std::array<GLchar, info_log_buff_size> info_log{};
    if (success == 0) {
        glGetProgramInfoLog(gl_program_id_, info_log_buff_size, nullptr, info_log.data());
        puts(fmt::format("ERROR::SHADER::PROGRAM::LINKING_FAILED\n{}\n", info_log.data()).c_str());
    }

}
