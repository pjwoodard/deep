#pragma once

#include <imgui.h>

#include "events/event_t.h"
#include "events/event_dispatcher.h"

namespace deep
{
class ImGuiLayer {
   public:
    void on_attach();
    void on_detach(){};
    void on_update();
    void on_event(const deep::Event_t& event);

   private:
    float time_{0.0};
    deep::events::EventDispatcher event_dispatcher_;
};
}
