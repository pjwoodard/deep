#include <glad/glad.h>

#include "deep/deep.h"
#include "imgui/imgui_layer.h"
#include "logger/logger.h"
#include "window/glfw_window.h"

using namespace std::literals;

static constexpr deep::types::Width deep_width{ 800 };
static constexpr deep::types::Height deep_height{ 600 };

int main()
{
    deep::Logger::info_core("Starting Deep by creating application");
    deep::Deep app;
    app.push_layer(deep::ImGuiLayer{});
    app.run();

    return 0;
}
