#include "context/glfw_context.h"
#include "window/glfw_window.h"
#include "shader/opengl_program.h"
#include "math/matrix.h"

constexpr static deep::types::Width window_width{800};
constexpr static deep::types::Height window_height{600};

using namespace std::literals;

int main()
{
    GlfwContext::init_glfw();

    deep::GlfwWindow window("Test window"sv, window_width, window_height);
    window.set_as_current_context();

    window.display();

    glfwTerminate();
    return 0;
}

