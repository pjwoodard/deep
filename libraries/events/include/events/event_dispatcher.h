#pragma once

#include <functional>
#include <typeindex>
#include <unordered_map>
#include <string_view>

#include <fmt/format.h>

#include "event_t.h"
#include "logger/logger.h"
#include "types/deep_concepts.h"

namespace deep::events {
class EventDispatcher
{
  public:
    void publish(const deep::events::Event_t &event)
    {
        if(event_map_.contains(event.get_event_type()))
        {
            const auto functions_to_call = event_map_.at(event.get_event_type());
            for (const auto &func : functions_to_call)
            {
                func(event);
            }
        }
        else
        {
            deep::Logger::warn_core("Unsubscribed event caught");
        }
    }

    template<typename FunctionType>
    void subscribe(const deep::events::EventType &event_type, FunctionType func)
    {
        // If we have the thing in the map already, add the function to the vector
        if (event_map_.contains(event_type))
        {
            auto &functions_to_call = event_map_.at(event_type);
            functions_to_call.push_back(func);;
        }
        else
        {
            // Otherwise, create a vector with the function in it, and add it to the map
            event_map_.emplace(event_type, std::vector<std::function<void(const deep::events::Event_t&)>>{func});
        }
    }

  private:
    //  Event map is shared amongst all EventDispatchers
    // TODO: Thread Safety
    // TODO: Faster flatter map
    inline static std::unordered_map<deep::events::EventType, std::vector<std::function<void(const deep::events::Event_t&)>>> event_map_;
};
}
