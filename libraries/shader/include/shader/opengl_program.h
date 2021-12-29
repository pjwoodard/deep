#pragma once

#include <vector>

#include "opengl_shader.h"

class OpenGLProgram
{
  public:
    explicit OpenGLProgram(const std::vector<OpenGLShader>& shaders);

    OpenGLProgram(OpenGLProgram&& program) noexcept = default;
    OpenGLProgram& operator=(OpenGLProgram&& program) noexcept = default;
    OpenGLProgram(const OpenGLProgram& program) = delete;
    OpenGLProgram& operator=(const OpenGLProgram& program) = delete;

    ~OpenGLProgram() noexcept { glDeleteProgram(gl_program_id_); }

    [[nodiscard]] constexpr auto id() const noexcept { return gl_program_id_; };

    void setUniform(const std::string_view name, const deep::concepts::OpenGLUniform auto uniform)
    {
        if constexpr (std::is_floating_point_v<decltype(uniform)>) {
            glUniform1f(glGetUniformLocation(gl_program_id_, name.data()), uniform);
        } else {
            glUniform1i(glGetUniformLocation(gl_program_id_, name.data()), static_cast<int>(uniform));
        }
    }

  private:
    uint32_t gl_program_id_;
};
