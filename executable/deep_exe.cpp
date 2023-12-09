#include "deep/deep.h"
#include "imgui/imgui_layer.h"
#include "logger/logger.h"

using namespace std::literals;

int main()
{
    deep::Logger::info_core("Starting Deep by creating application");
    deep::Deep app;
    app.emplace_layer(deep::ImGuiLayer{});
    app.run();

    return 0;
}
