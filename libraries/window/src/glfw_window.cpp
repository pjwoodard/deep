#include <array>
#include <string_view>

#include <glad/glad.h>

#include "math/matrix.h"
#include "window/glfw_window.h"
#include "shader/opengl_program.h"
#include "shader/opengl_shader.h"
#include "shaders/hello_triangle.h"

using namespace std::literals;
using namespace deep;

GlfwWindow::GlfwWindow(std::string_view title,
                       types::Width width,
                       types::Height height)
  : width_{ width.get() }
  , height_{ height.get() }
  , self_raw_(glfwCreateWindow(width_, height_, title.data(), nullptr, nullptr))
{
    if (!self_raw_) {
        throw std::runtime_error("glfwCreateWindow returned null"sv.data());
    }

    glfwSetFramebufferSizeCallback(self_raw_.get(), framebuffer_size_callback);
}
void GlfwWindow::display() const
{
    std::vector<OpenGLShader> shaders;
    shaders.reserve(2);
    shaders.emplace_back(GLShaderType::VertexShader,
                         vertex_shaders::hello_triangle);
    shaders.emplace_back(GLShaderType::FragmentShader,
                         fragment_shaders::hello_triangle);

    OpenGLProgram opengl_program{ shaders };

    constexpr auto vec3_size{ 3 };
    constexpr auto data_stride{ 6 * sizeof(float) };
    constexpr auto color_offset{ 3 * sizeof(float) };
    constexpr auto position_attribute{ 0 };
    constexpr auto color_attribute{ 1 };

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    constexpr Matrix<float, 6, 3> vertices{
        {
          0.5F, 0.5F, 0.0F, 1.0F, 0.0F, 0.0F, // bottom right
          -0.5F, 0.5F, 0.0F, 0.0F, 1.0F, 0.0F, // bottom left
          0.0F, -0.5F, 0.0F, 0.0F, 0.0F, 1.0F
        }
    };

//    constexpr Matrix<float, 3, 2> texture_coordinates {
//        {
//          0.0F, 0.0F,
//          1.0F, 0.0F,
//          0.5F, 1.0F
//        }
//    };

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
                          types::to_integral(types::OpenGLDataType::FLOAT),
                          GL_FALSE,
                          data_stride,
                          nullptr);

    glEnableVertexAttribArray(position_attribute);

    glVertexAttribPointer(
      color_attribute,
      vec3_size,
      types::to_integral(types::OpenGLDataType::FLOAT),
      GL_FALSE,
      data_stride,
      reinterpret_cast<const void*>(color_offset)); // NOLINT

    glEnableVertexAttribArray(color_attribute);

    //    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glUseProgram(opengl_program.id());

    float current_offset{-0.5F}; //NOLINT

    while (glfwWindowShouldClose(self_raw_.get()) == 0) {
        processInput(self_raw_.get());

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f ); //NOLINT
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //NOLINT

        opengl_program.setUniform("horizontalOffset"sv, current_offset);

        if (current_offset >= 0.5F) //NOLINT
        {
            current_offset = -0.5F; //NOLINT
        }

        current_offset += 0.001F; //NOLINT

        glBindVertexArray(vertex_array_id);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(self_raw_.get());
        glfwPollEvents();
    }

    glDeleteBuffers(1, &vertex_buffer_id);
    glDeleteVertexArrays(1, &vertex_array_id);
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
