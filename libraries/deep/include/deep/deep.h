#pragma once

#include "events/event_dispatcher.h"
#include "layer/layer_stack.h"
#include "types/deep_concepts.h"
#include "window/glfw_window.h"
#include "window/window_t.h"

// TODO: Make a more abstract idea of an application and have this "inherit" from it

#include <stack>

namespace deep {
// Contains
enum class DeepState { GAME_ACTIVE, GAME_MENU, GAME_WIN };

class Deep {
   public:
    explicit Deep();

    static deep::Window_t& GetWindow() { return window_; };

    // TODO: Should "move" version of push layer only accept rvalue references?
    // TODO: emplace_layer vs push_layer
    void push_layer(Layer_t layer) {
        layer.on_attach();
        layers_.push_back(std::move(layer));
    };

    void run()
    {
        while(running_)
        {
            for(auto& layer : layers_)
            {
                layer.on_update();
            }
            window_.on_update();
        }
    }

   private:
    deep::EventDispatcher event_dispatcher_;

    inline static deep::Window_t window_{deep::GlfwWindow{"Deep Main Application Window", types::Width(800), types::Height(600)}};

    bool running_{true};
    std::vector<Layer_t> layers_;
};
}  // namespace deep
