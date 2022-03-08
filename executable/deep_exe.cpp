#include <GLFW/glfw3.h>            // for glfwTerminate
#include <chrono>                  // for literals
#include <string_view>             // for operator""sv

#include "window/glfw_window.h"
#include "logger/logger.h"
#include "logger/spd_logger.h"
#include "deep/deep.h"

using namespace std::literals;

static constexpr deep::types::Width width{800};
static constexpr deep::types::Height height{600};

int main()
{
    deep::Logger::info_core("Starting Deep!");
    deep::Logger::debug_core("Launching Window!");

    deep::GlfwWindow window("TItle", width, height);
 
    return 0;
}

