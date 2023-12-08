#pragma once

#include <cstdint>
#include <string_view>

#include <glad/glad.h>

#include "types/deep_concepts.h"

enum class GLShaderStatus : GLenum
{
    CompileStatus = GL_COMPILE_STATUS
};

enum class GLShaderType : GLenum
{
    VertexShader = GL_VERTEX_SHADER,
    FragmentShader = GL_FRAGMENT_SHADER,
    //    GeometryShader = GL_GEOMETRY_SHADER
};

class OpenGLShader
{
  public:
    OpenGLShader(const GLShaderType &type, std::string_view data);

    OpenGLShader(OpenGLShader &&shader) noexcept = default;
    OpenGLShader &operator=(OpenGLShader &&shader) noexcept = default;
    OpenGLShader(const OpenGLShader &shader) = delete;
    OpenGLShader &operator=(const OpenGLShader &shader) = delete;

    ~OpenGLShader() noexcept { glDeleteShader(id_); }

    [[nodiscard]] uint32_t id() const;

  private:
    uint32_t id_;

    void compile(std::string_view shader_program_str) const;
    [[nodiscard]] int32_t get_shader_status(const GLShaderStatus &shader_status_to_query) const;
    [[nodiscard]] bool shader_compilation_successful() const;
};
