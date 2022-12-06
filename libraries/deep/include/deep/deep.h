#pragma once

#include "events/event_dispatcher.h"
#include "layer/layer_stack.h"
#include "types/deep_concepts.h"
#include "window/glfw_window.h"
#include "window/window_t.h"

// TODO: Make a more abstract idea of an application and have this "inherit" from it

#include <stack>

namespace deep {

class Deep {
   public:
    explicit Deep();

    [[nodiscard]] static deep::Window_t& GetWindow() { return window_; };

    // TODO: Should "move" version of push layer only accept rvalue references?
    // TODO: emplace_layer vs push_layer
    void push_layer(Layer_t layer);
    void run();

   private:
    deep::events::EventDispatcher event_dispatcher_;
    bool running_{false};
    std::vector<Layer_t> layers_;

    inline static deep::Window_t window_{deep::GlfwWindow{"Deep Main Application Window", types::Width(800), types::Height(600)}};
};
}  // namespace deep
