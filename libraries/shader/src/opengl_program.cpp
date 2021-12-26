#include <array>
#include <cassert>

#include "shader/opengl_program.h"

OpenGLProgram::OpenGLProgram(const std::vector<OpenGLShader> &shaders)
: gl_program_id_{ glCreateProgram() }
{
    for (const auto &shader : shaders)
    {
        glAttachShader(gl_program_id_, shader.id());
    }

    glLinkProgram(gl_program_id_);

    // TODO: Clean this up, figure out error handling method
    int success{ 0 };
    glGetProgramiv(gl_program_id_, GL_LINK_STATUS, &success);
    constexpr int32_t info_log_buff_size{ 512 };
    std::array<GLchar, info_log_buff_size> info_log{};
    if (success == 0)
    {
        glGetProgramInfoLog(gl_program_id_, info_log_buff_size, nullptr, info_log.data());
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
                  << info_log.data() << std::endl;
    }
}
