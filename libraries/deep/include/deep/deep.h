#pragma once

#include "events/signal.h"
#include "layer/layer_stack.h"
#include "types/deep_concepts.h"
#include "window/glfw_window.h"
#include "window/window_t.h"

using namespace deep::concepts;

namespace deep {

class Deep {
   public:
    explicit Deep();

    [[nodiscard]] static auto& GetWindow() { return window_; };

    void emplace_layer(Layer_t &&layer);
    void run();

   private:
    deep::events::Signal<int32_t, int32_t> on_window_resized_;
    std::vector<Layer_t> layers_;

    inline static const deep::GlfwWindow window_{"deep Main Application Window", types::Width(800), types::Height(600)};
};
}  // namespace deep
