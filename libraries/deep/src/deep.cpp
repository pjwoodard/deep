#include <bit>

#include "deep/deep.h"
#include "fmt/format.h"
#include "logger/logger.h"

using namespace deep;

Deep::Deep()
{
    event_dispatcher_.subscribe(
      deep::events::EventType::WindowResizedEvent,
      [](const deep::events::Event_t& event)
      {
          if (event.get_event_type() == deep::events::EventType::WindowResizedEvent)
          {
              deep::Logger::debug_core(fmt::format("Uh oh, here we go"));
              const auto window_resized_event = static_cast<const deep::events::WindowResizedEvent&>(event);

          }
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
        window_.on_update();
    }
}