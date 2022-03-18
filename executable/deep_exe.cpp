#include <fmt/format.h>

#include "window/glfw_window.h"
#include "logger/logger.h"

using namespace std::literals;

static constexpr deep::types::Width width{800};
static constexpr deep::types::Height height{600};

int main()
{
    deep::Logger::info_core("Starting Deep!");
    deep::Logger::debug_core("Launching Window!");

    deep::GlfwWindow window("Title", width, height);

    return 0;
}

