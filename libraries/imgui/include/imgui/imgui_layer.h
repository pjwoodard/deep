#pragma once

#include <imgui.h>

#include "events/signal.h"

struct GLFWwindow;

namespace deep
{
class ImGuiLayer
{
  public:
    ImGuiLayer()
    {
        on_key_pressed_.subscribe(deep::events::EventType::KeyPressedEvent,
          [](int32_t keynum, int32_t scancode, int32_t action, int32_t mods)
          {
              deep::Logger::debug_core(fmt::format(
                "Key Pressed. Key Number: {}, Scan Code: {}, Action: {}, Mods: {}", keynum, scancode, action, mods));
          });
    }

    static void on_attach();
    static void on_detach() {}
    void on_update();

  private:
    deep::events::Signal<int32_t, int32_t, int32_t, int32_t> on_key_pressed_;

    // Our state
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
};
}// namespace deep
