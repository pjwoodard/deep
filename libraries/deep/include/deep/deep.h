#pragma once

#include "events/event_dispatcher.h"
#include "types/deep_concepts.h"
#include "window/window_t.h"
#include "window/glfw_window.h"

namespace deep {
// Contains
enum class DeepState { GAME_ACTIVE, GAME_MENU, GAME_WIN };

class Deep {
   public:
    explicit Deep();

    static deep::Window_t& GetWindow() { return window_; };

   private:
    deep::EventDispatcher event_dispatcher_;

    inline static deep::Window_t window_{
        deep::GlfwWindow{"Deep Main Application Window", types::Width(800), types::Height(600)}
    };
};
}  // namespace deep
