#include "shader/opengl_shader.h"

#include <array>

#include <fmt/format.h>

// TODO: Guard against calling glCreateShader before GLFW init has finished
OpenGLShader::OpenGLShader(const GLShaderType &type, std::string_view data)
  : id_{ glCreateShader(static_cast<std::underlying_type_t<GLShaderType>>(type)) }
{
    compile(data);
}

uint32_t OpenGLShader::id() const { return id_; }

void OpenGLShader::compile(std::string_view shader_program_str) const
{
    // We ignore reinterpret cast here as it is a safe cast between constant types
    // Both data and pointer are left unmodified
    const std::array<const GLchar *, 1> shaders = { shader_program_str.data() };

    glShaderSource(id_, 1, shaders.data(), nullptr);
    glCompileShader(id_);

    if (!shader_compilation_successful())
    {
        // TODO: Clean this up, figure out error handling method
        constexpr int32_t info_log_buff_size{ 512 };
        std::array<GLchar, info_log_buff_size> info_log{};
        glGetShaderInfoLog(id_, static_cast<GLsizei>(info_log.size()), nullptr, info_log.data());
        puts(fmt::format("ERROR::SHADER::VERTEX::COMPILATION_FAILED: {}\n", info_log.data()).c_str());
    }
}

int32_t OpenGLShader::get_shader_status(const GLShaderStatus &shader_status_to_query) const
{
    int32_t status{ 0 };
    glGetShaderiv(id_, static_cast<GLenum>(shader_status_to_query), &status);
    return status;
}

bool OpenGLShader::shader_compilation_successful() const
{
    return get_shader_status(GLShaderStatus::CompileStatus) != 0;
}
