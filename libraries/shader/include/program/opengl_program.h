#pragma once

#include "types/deep_types.h"

#include <glad/glad.h>

#include <optional>
#include <vector>


class OpenGLProgram
{
  public:
    explicit OpenGLProgram(deep::types::VertexShaderSource vertex_source,
      deep::types::FragmentShaderSource fragment_source,
      std::optional<deep::types::GeometryShaderSource> geometry_source = std::nullopt);

    OpenGLProgram(OpenGLProgram &&program) noexcept = default;
    OpenGLProgram &operator=(OpenGLProgram &&program) noexcept = default;
    OpenGLProgram(const OpenGLProgram &program) = delete;
    OpenGLProgram &operator=(const OpenGLProgram &program) = delete;

    ~OpenGLProgram() noexcept { glDeleteProgram(gl_program_id_); }

    [[nodiscard]] constexpr auto id() const noexcept { return gl_program_id_; }

    void set_uniform(const std::string_view name, const deep::concepts::OpenGLUniform auto uniform)
    {
        if constexpr (std::is_floating_point_v<decltype(uniform)>)
        {
            glUniform1f(glGetUniformLocation(gl_program_id_, name.data()), uniform);
        }
        else
        {
            glUniform1i(glGetUniformLocation(gl_program_id_, name.data()), static_cast<int>(uniform));
        }
    }

    void set_as_current_program() const noexcept { glUseProgram(gl_program_id_); }

  private:
    uint32_t gl_program_id_;
};
