#include "imgui/imgui_layer.h"

#include "deep/deep.h"
#include "imgui_impl_opengl3.h"
#include "events/event_dispatcher.h"

using namespace deep;

void ImGuiLayer::on_attach() {
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    ImGuiIO& imgui_io = ImGui::GetIO();
    imgui_io.BackendFlags |= static_cast<uint32_t>(ImGuiBackendFlags_HasMouseCursors);
    imgui_io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

    ImGui_ImplOpenGL3_Init();
}

void ImGuiLayer::on_update() {
    ImGuiIO& imgui_io = ImGui::GetIO();
    imgui_io.DisplaySize = ImVec2(static_cast<float>(deep::Deep::GetWindow().width()), static_cast<float>(deep::Deep::GetWindow().height()));

    auto time = static_cast<float>(glfwGetTime());
    imgui_io.DeltaTime = time_ > 0.0F ? (time - time_) : (1.0F / 60.0F);
    time_ = time;

    ImGui_ImplOpenGL3_NewFrame();
    ImGui::NewFrame();

    static bool show = true;
    ImGui::ShowDemoWindow(&show);

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ImGuiLayer::on_event(const deep::Event_t& event)
{
    event_dispatcher_.subscribe<event.get_event_type()>()
}
