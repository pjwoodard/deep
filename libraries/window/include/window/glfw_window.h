#pragma once

#include "events/event_dispatcher.h"
#include "events/window_resized_event.h"
#include "events/event_t.h"
#include "logger/logger.h"
#include "types/deep_types.h"

#include <GLFW/glfw3.h>

#include <memory>
#include <string_view>
#include <functional>

namespace deep
{

class GlfwWindow
{
  public:
    GlfwWindow(std::string_view title, types::Width width, types::Height height);

    void display() const;

    [[nodiscard]] int32_t width() const noexcept
    {
        int32_t width{0};
        int32_t height{0};
        glfwGetWindowSize(self_raw_.get(), &width, &height);

        return width;
    };

    [[nodiscard]] int32_t height() const noexcept
    {
        int32_t width{0};
        int32_t height{0};
        glfwGetWindowSize(self_raw_.get(), &width, &height);

        return height;
    };

    static void set_vsync(bool enable);
    [[nodiscard]] bool is_vsync() const noexcept {return is_vsync_;};
    
    // TODO: Ideally should never have to "get" the raw window
    GLFWwindow *get() { return self_raw_.get(); }

  private:
    void set_as_current_context() const;

    enum class OpenGLDataType : GLenum {
        FLOAT = GL_FLOAT
    };

    static void framebuffer_size_callback(GLFWwindow * /*window*/, int32_t width, int32_t height)
    {
        deep::Logger::debug_core(fmt::format("Calling {}", __FUNCTION__));
        event_dispatcher_.publish(deep::WindowResizedEvent());
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
    bool is_current_context_window{false};

    std::unique_ptr<GLFWwindow, GlfwWindowDeleter> self_raw_;
    inline static deep::EventDispatcher event_dispatcher_;
};

}// namespace deep
