#pragma once

#include <cstdint>

class OpenGLTexture
{
  public:
    OpenGLTexture();
    [[nodiscard]] constexpr auto id() const noexcept { return texture_id_; }
  private:
    GLuint texture_id_{};
};