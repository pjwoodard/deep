#include "deep/deep.h"
#include "events/window_resized_event.h"
#include "fmt/format.h"
#include "logger/logger.h"

using namespace deep;

Deep::Deep()
{
    event_dispatcher_.subscribe<deep::WindowResizedEvent>([]() { deep::Logger::debug_core(fmt::format("Uh oh, here we go")); });
}
