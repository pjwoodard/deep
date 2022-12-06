#pragma once

#include "events/event_dispatcher.h"
#include "events/event_t.h"
#include "events/events.h"
#include "logger/logger.h"
#include "types/deep_types.h"

#include <GLFW/glfw3.h>

#include <functional>
#include <memory>
#include <string_view>

namespace deep
{
class GlfwWindow
{
  public:
    GlfwWindow(std::string_view title, types::Width width, types::Height height);

    [[nodiscard]] int32_t width() const noexcept
    {
        int32_t width{ 0 };
        int32_t height{ 0 };
        glfwGetWindowSize(self_raw_.get(), &width, &height);

        return width;
    };

    [[nodiscard]] int32_t height() const noexcept
    {
        int32_t width{ 0 };
        int32_t height{ 0 };
        glfwGetWindowSize(self_raw_.get(), &width, &height);

        return height;
    };

    static void set_vsync(bool enable);
    [[nodiscard]] bool is_vsync() const noexcept { return is_vsync_; };
    void set_as_current_context() const;
    void on_update();

  private:
    struct GlfwWindowDeleter
    {
        void operator()(GLFWwindow* raw_window) const { glfwDestroyWindow(raw_window); }
    };

    static void key_pressed(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void mouse_button_pressed(GLFWwindow* window, int button, int action, int mods);
    static void framebuffer_size_callback(GLFWwindow* /*window*/, int32_t width, int32_t height);
    void processInput(GLFWwindow* window);

    int32_t width_{};
    int32_t height_{};
    bool is_vsync_{ false };
    bool glfw_initialized_{ false };

    std::unique_ptr<GLFWwindow, GlfwWindowDeleter> self_raw_;
    inline static deep::events::EventDispatcher event_dispatcher_;
};

} // namespace deep
