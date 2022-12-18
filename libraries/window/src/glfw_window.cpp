// Third party includes
#include <glad/glad.h>

// std library includes
#include <string_view>

// self include
#include "window/glfw_window.h"

// private includes
#include "context/glfw_context.h"
#include "logger/logger.h"
#include "math/matrix.h"

using namespace std::literals;
using namespace deep;
using namespace std::placeholders;

GlfwWindow::GlfwWindow(std::string_view title, types::Width width, types::Height height)
  : glfw_initialized_{ GlfwContext::init_glfw() }
  , width_{ width.get() }
  , height_{ height.get() }
  , self_raw_{ glfwCreateWindow(width_, height_, title.data(), nullptr, nullptr) }
{
    deep::Logger::assert_and_log("GLFW failed to initialize", glfw_initialized_);
    deep::Logger::assert_and_log("glfwCreateWindow returned null"sv.data(), !self_raw_ == false);

    // Set GLFW callbacks
    glfwSetFramebufferSizeCallback(self_raw_.get(), &GlfwWindow::framebuffer_size_callback);
    glfwSetKeyCallback(self_raw_.get(), &GlfwWindow::key_pressed);
    glfwSetMouseButtonCallback(self_raw_.get(), &GlfwWindow::mouse_button_pressed);

    set_as_current_context();

    glfwSwapInterval(swap_interval_);
}

void GlfwWindow::on_update()
{
    glfwPollEvents();

    glfwSwapBuffers(self_raw_.get());
}

void GlfwWindow::set_vsync(bool enable)
{
    glfwSwapInterval(static_cast<int32_t>(enable));
}

void GlfwWindow::set_as_current_context() const
{
    glfwMakeContextCurrent(self_raw_.get());

    // TODO: Find a better place for this, reinterpret_cast is necessary here
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
    if (gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)) == 0)
    {
        deep::Logger::error_core("Failed to initialize GLAD"sv.data());
    }
}

void GlfwWindow::mouse_button_pressed(GLFWwindow* window, int /*button*/, int /*action*/, int /*mods*/)
{
    if (window == nullptr)
    {
        deep::Logger::critical_core(fmt::format("Window is null in function {}", __FUNCTION__));
    }

//    event_dispatcher_.publish(deep::events::MouseButtonPressedEvent{});
}

void GlfwWindow::key_pressed(GLFWwindow* window, int32_t key, int scancode, int action, int mods)
{
    if (window == nullptr)
    {
        deep::Logger::critical_core(fmt::format("Window is null"));
    }

    on_key_pressed_.publish(deep::events::EventType::KeyPressedEvent, key, scancode, action, mods);
}

void GlfwWindow::framebuffer_size_callback(GLFWwindow* /*window*/, int32_t width, int32_t height)
{
    deep::Logger::debug_core(fmt::format("Calling {}", __FUNCTION__));

    on_window_resized_.publish(deep::events::EventType::WindowResizedEvent, width, height);

    glViewport(0, 0, width, height);
}

void GlfwWindow::processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, 1);
    }
}
