#include <string_view>

#include <glad/glad.h>

#include "math/matrix.h"
#include "program/opengl_program.h"
#include "shaders/hello_triangle.h"
#include "window/glfw_window.h"
#include "texture/opengl_texture.h"
#include "context/glfw_context.h"
#include "logger/logger.h"
#include "events/event.h"

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
    OpenGLProgram opengl_program{ vertex_shaders::hello_triangle, fragment_shaders::hello_triangle };

    constexpr auto vec3_size{ 3 };
    constexpr auto data_stride{ 8 * sizeof(float) };
    constexpr auto color_offset{ 3 * sizeof(float) };
    constexpr auto texture_offset{ 6 * sizeof(float) };
    constexpr auto position_attribute{ 0 };
    constexpr auto color_attribute{ 1 };
    constexpr auto texture_attribute { 2 };

    constexpr Matrix<float, 4, 8> vertices {
      {0.5F,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // NOLINT
      0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // NOLINT
      -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // NOLINT
      -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f}    // NOLINT
    };

    OpenGLTexture texture{};

    uint32_t vertex_buffer_id = 0;
    uint32_t vertex_array_id = 0;
    glGenVertexArrays(1, &vertex_array_id);
    glGenBuffers(1, &vertex_buffer_id);

    glBindVertexArray(vertex_array_id);

    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_id);
    glBufferData(
      GL_ARRAY_BUFFER, sizeof(vertices), vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(position_attribute,
                          vec3_size,
                          deep::concepts::to_integral(OpenGLDataType::FLOAT),
                          GL_FALSE,
                          data_stride,
                          nullptr);

    glEnableVertexAttribArray(position_attribute);

    glVertexAttribPointer(
      color_attribute,
      vec3_size,
      concepts::to_integral(OpenGLDataType::FLOAT),
      GL_FALSE,
      data_stride,
      reinterpret_cast<const void*>(color_offset)); // NOLINT

    glEnableVertexAttribArray(color_attribute);

    glVertexAttribPointer(
      texture_attribute,
      2,
      concepts::to_integral(OpenGLDataType::FLOAT),
      GL_FALSE,
      data_stride,
      reinterpret_cast<const void*>(texture_offset)); //NOLINT

    glEnableVertexAttribArray(texture_attribute);

    //    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    opengl_program.set_as_current_program();

    while (glfwWindowShouldClose(self_raw_.get()) == 0) {
        processInput(self_raw_.get());

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f ); //NOLINT
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //NOLINT

        glBindTexture(GL_TEXTURE_2D, texture.id());
        glBindVertexArray(vertex_array_id);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(self_raw_.get());
        glfwPollEvents();
    }

    glDeleteBuffers(1, &vertex_buffer_id);
    glDeleteVertexArrays(1, &vertex_array_id);
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
