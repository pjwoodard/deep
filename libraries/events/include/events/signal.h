#pragma once

#include <functional>
#include <string_view>
#include <typeindex>
#include <unordered_map>

#include <fmt/format.h>

#include "events.h"
#include "logger/logger.h"
#include "types/deep_concepts.h"

namespace deep::events
{
template<typename... Args> class Signal
{
  public:
    using EventCallback = std::function<void(Args...)>;

    static void publish(const deep::events::EventType &event_type, Args... args)
    {
        if (event_map_.contains(event_type))
        {
            const auto functions_to_call = event_map_.at(event_type);
            for (const auto &func : functions_to_call) { func(args...); }
        }
        else
        {
            deep::Logger::warn_core("Unsubscribed event caught");
        }
    }

    static void subscribe(const deep::events::EventType &event_type, EventCallback func)
    {
        // If we have the thing in the map already, add the function to the vector
        if (event_map_.contains(event_type))
        {
            auto &functions_to_call = event_map_.at(event_type);
            functions_to_call.push_back(func);
        }
        else
        {
            // Otherwise, create a vector with the function in it, and add it to the map
            event_map_.emplace(event_type, std::vector<EventCallback>{ func });
        }
    }

  private:
    //  Event map is shared amongst all EventDispatchers
    // TODO: Thread Safety
    // TODO: Faster flatter map
    inline static std::unordered_map<deep::events::EventType, std::vector<EventCallback>> event_map_;
};
}// namespace deep::events
