#include <bit>

#include "deep/deep.h"
#include "fmt/format.h"
#include "logger/logger.h"

using namespace deep;

Deep::Deep()
{
    on_window_resized_.subscribe(
      deep::events::EventType::WindowResizedEvent,
      [](int32_t width, int32_t height)
      {
          deep::Logger::debug_core(fmt::format("Width: {}, Height: {}", width, height));
      });
}

void Deep::push_layer(deep::Layer_t layer)
{
    layer.on_attach();
    layers_.push_back(std::move(layer));
};

void Deep::run()
{
    running_ = true;

    while(running_)
    {
        for(auto& layer : layers_)
        {
            layer.on_update();
        }
    }
}