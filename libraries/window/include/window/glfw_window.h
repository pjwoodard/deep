#pragma once

#include <memory>
#include <string_view>

#include <GLFW/glfw3.h>

#include "types/deep_types.h"

namespace deep
{

class GlfwWindow
{
  public:
    GlfwWindow(std::string_view title, types::Width width, types::Height height);

    void display() const;

    GLFWwindow *get() { return self_raw_.get(); }

    void set_as_current_context() const;

  private:
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
        void operator()(GLFWwindow *raw_window)
        {
            glfwDestroyWindow(raw_window);
        }
    };

    const int32_t width_{};
    const int32_t height_{};

    std::unique_ptr<GLFWwindow, GlfwWindowDeleter> self_raw_;
};

}// namespace ace
