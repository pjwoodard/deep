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
}

void GlfwWindow::display() const
{
    set_as_current_context();

    while (glfwWindowShouldClose(self_raw_.get()) == 0) {
        processInput(self_raw_.get());

        // glClearColor(0.0f, 0.0f, 0.0f, 1.0f ); //NOLINT
        // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //NOLINT

        // glBindTexture(GL_TEXTURE_2D, texture.id());
        // glBindVertexArray(vertex_array_id);
        // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(self_raw_.get());
        glfwPollEvents();
    }
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
        std::cout << "Failed to initialize GLAD" << std::endl;
    }
}
