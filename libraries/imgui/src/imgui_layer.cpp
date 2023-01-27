#include "imgui/imgui_layer.h"

#include "deep/deep.h"
#include "events/signal.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

using namespace deep;

//static void glfw_error_callback(int error, const char* description)
//{
//    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
//}

void ImGuiLayer::on_attach()
{
//    glfwSetErrorCallback(glfw_error_callback);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& imgui_io = ImGui::GetIO();
    imgui_io.ConfigFlags |= static_cast<uint32_t>(ImGuiConfigFlags_NavEnableKeyboard); // Enable Keyboard Controls
    imgui_io.ConfigFlags |= static_cast<uint32_t>(ImGuiConfigFlags_NavEnableGamepad);  // Enable Gamepad Controls

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

    // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
    ImGui::ShowDemoWindow(&show_demo_window);

    // Rendering
    ImGui::Render();
    int32_t display_w{0};
    int32_t display_h{0};
    glfwGetFramebufferSize(window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(window);
}
