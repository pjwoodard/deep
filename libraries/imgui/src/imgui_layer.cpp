#include "imgui/imgui_layer.h"

#include "deep/deep.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui.h"
#include "logger/logger.h"
#include "memory/memory_distributor.h"
#include "fmt/format.h"

using namespace deep;

namespace
{
void glfw_error_callback(int error, const char *description)
{
    deep::Logger::error_core(fmt::format("Glfw Error {}: {}", error, description));
}
}// namespace

void ImGuiLayer::on_attach()
{
    glfwSetErrorCallback(glfw_error_callback);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &imgui_io = ImGui::GetIO();
    imgui_io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;// Enable Keyboard Controls
    imgui_io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;// Enable Gamepad Controls

    ImGui::StyleColorsDark();

    auto *window = deep::Deep::GetWindow().get_raw_window();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();
}

void ImGuiLayer::on_update()
{
    auto *window = deep::Deep::GetWindow().get_raw_window();

    glfwPollEvents();

    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    {
        // Grab our data to display
        ImGuiIO &io = ImGui::GetIO();
        const deep::memory::MemoryDistributor::HeapStats heap_stats = deep::memory::MemoryDistributor::GetHeapStats();

        // Create a window and display our data
        ImGui::Begin("Deep Metrics");
        ImGui::Text("%s", fmt::format("Application average {} ms/frame ({} FPS)", 1000.0F / io.Framerate, io.Framerate).c_str());
        ImGui::Text("%s", fmt::format("Total memory allocated: {} bytes", heap_stats.total_allocated).c_str());
        ImGui::Text("%s", fmt::format("Total memory deallocated: {} bytes", heap_stats.total_deallocated).c_str());
        ImGui::Text("%s", fmt::format("Current memory allocated: {} bytes", heap_stats.current_allocated).c_str());
        ImGui::End();
    }

    // Rendering
    ImGui::Render();
    int32_t display_w{ 0 };
    int32_t display_h{ 0 };
    glfwGetFramebufferSize(window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    glClearColor(
      clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(window);
}
