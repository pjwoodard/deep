#include <GLFW/glfw3.h>            // for glfwTerminate
#include <chrono>                  // for literals
#include <string_view>             // for operator""sv
#include "types/deep_types.h"      // for Height, Width
#include "context/glfw_context.h"
#include "window/glfw_window.h"

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

