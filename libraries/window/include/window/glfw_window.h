#pragma once

#include <memory>
#include <string_view>
#include <functional>

#include <GLFW/glfw3.h>

#include "types/deep_types.h"
#include "logger/logger.h"

namespace deep
{

class GlfwWindow
{
  public:
    GlfwWindow(std::string_view title, types::Width width, types::Height height);

    void display() const;

    [[nodiscard]] int32_t width() const noexcept { return width_; };
    [[nodiscard]] int32_t height() const noexcept {return height_;};
    static void set_vsync(bool enable);
    [[nodiscard]] bool is_vsync() const noexcept {return is_vsync_;};
    
    // TODO: Ideally should never have to "get" the raw window
    GLFWwindow *get() { return self_raw_.get(); }

    void set_as_current_context() const;

  private:
    enum class OpenGLDataType : GLenum {
        FLOAT = GL_FLOAT
    };

    static void framebuffer_size_callback(GLFWwindow * /*window*/, int32_t width, int32_t height)
    {
        glViewport(0, 0, width, height);
    }

    static void processInput(GLFWwindow *window)
    {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(window, 1);
        }
    }

    struct GlfwWindowDeleter
    {
        void operator()(GLFWwindow *raw_window) const
        {
            glfwDestroyWindow(raw_window);
        }
    };

    int32_t width_{};
    int32_t height_{};
    bool is_vsync_{false};

    inline static bool glfw_initialized_{false};

    std::unique_ptr<GLFWwindow, GlfwWindowDeleter> self_raw_;
};

}// namespace ace
