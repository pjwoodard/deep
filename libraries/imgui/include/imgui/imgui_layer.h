#pragma once

#include <imgui.h>

#include "events/signal.h"

struct GLFWwindow;

namespace deep
{
class ImGuiLayer {
   public:
    ImGuiLayer()
    {
        on_key_pressed_.subscribe(
          deep::events::EventType::KeyPressedEvent,
          [](int32_t keynum, int32_t scancode, int32_t action, int32_t mods)
          {
              deep::Logger::debug_core(fmt::format("Key Pressed. Key Number: {}, Scan Code: {}, Action: {}, Mods: {}", keynum, scancode, action, mods));
              ImGuiIO& io = ImGui::GetIO();

              io.KeysDown[keynum] = true;
          });
    }

    void on_attach();
    void on_detach(){};
    void on_update();

   private:
    deep::events::Signal<int32_t, int32_t, int32_t, int32_t> on_key_pressed_;
    deep::events::Signal<int32_t> on_mouse_button_pressed_;

    // Our state
    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
};
}
