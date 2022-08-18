#include "deep/deep.h"
#include "logger/logger.h"
#include "window/glfw_window.h"

using namespace std::literals;

static constexpr deep::types::Width deep_width{800};
static constexpr deep::types::Height deep_height{600};

int main()
{
    deep::Logger::info_core("Starting Deep!");
    deep::Logger::debug_core("Launching Window!");

    deep::Deep app;

    deep::GlfwWindow window("Title", deep_width, deep_height);
    window.display();

    return 0;
}

