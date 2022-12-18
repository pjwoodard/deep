#pragma once

#include "events/events.h"
#include "events/signal.h"
#include "logger/logger.h"
#include "types/deep_types.h"

#include <GLFW/glfw3.h>

#include <functional>
#include <memory>
#include <string_view>

using namespace deep::events;

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

    [[nodiscard]] auto *get_raw_window() const { return self_raw_.get(); }


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
    static constexpr int32_t swap_interval_{1};

    std::unique_ptr<GLFWwindow, GlfwWindowDeleter> self_raw_;

    inline static deep::events::Signal<int32_t, int32_t> on_window_resized_;
    inline static deep::events::Signal<int32_t> on_mouse_button_pressed_;
    inline static deep::events::Signal<int32_t, int32_t, int32_t, int32_t> on_key_pressed_;
};

} // namespace deep
