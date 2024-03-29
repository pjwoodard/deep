#include <cstdint>

#include "deep/deep.h"
#include "events/events.h"
#include "fmt/core.h"
#include "logger/logger.h"

using namespace deep;

Deep::Deep()
{
    on_window_resized_.subscribe(deep::events::EventType::WindowResizedEvent,
      [](int32_t width, int32_t height)
      { deep::Logger::debug_core(fmt::format("Width: {}, Height: {}", width, height)); });
}

void Deep::run()
{
    while (true)
    {
        for (auto &layer : layers_) { layer.on_update(); }
    }
}
