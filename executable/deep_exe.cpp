#include <fmt/format.h>

#include "window/glfw_window.h"
#include "logger/logger.h"
#include "deep/deep.h"

using namespace std::literals;

int main()
{
    constexpr deep::types::Width width{800};
    constexpr deep::types::Height height{600};

    deep::Logger::info_core("Starting Deep!");
    deep::Logger::debug_core("Launching Window!");

    deep::Deep app;

    deep::GlfwWindow window("Title", width, height);
    window.display();

    return 0;
}

