#include "math/matrix.h"
#include "program/opengl_program.h"
#include "window/glfw_window.h"
#include "context/glfw_context.h"
#include "logger/logger.h"

#include <string_view>

using namespace std::literals;
using namespace deep;

GlfwWindow::GlfwWindow(std::string_view title,
                       types::Width width,
                       types::Height height)
  : width_{ width.get() }
  , height_{ height.get() }
{
    if(!glfw_initialized_)
    {
        GlfwContext::init_glfw();
    }

    self_raw_.reset(glfwCreateWindow(width_, height_, title.data(), nullptr, nullptr));

    // TODO: Use asserts here to log message and drop into platform specific breakpoint function 
    if (!self_raw_) {
        deep::Logger::critical_core("glfwCreateWindow returned null"sv.data());
    }

    glfwSetFramebufferSizeCallback(self_raw_.get(), framebuffer_size_callback);

    set_as_current_context();
}

void GlfwWindow::on_update()
{
    processInput(self_raw_.get());

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f ); //NOLINT
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //NOLINT

    glfwSwapBuffers(self_raw_.get());
    glfwPollEvents();
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
    if (gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)) == 0) {
        deep::Logger::error_core("Failed to initialize GLAD"sv.data());
    }
}
