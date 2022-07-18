#pragma once

#include <functional>
#include <typeindex>
#include <unordered_map>

#include "types/deep_concepts.h"

#include <string_view>

namespace deep {

class WindowResizedEvent
{
  public:
    void get_event_type() {}
};

class EventDispatcher
{
  public:
    void publish(const deep::concepts::Event auto &event)
    {
        const auto functions_to_call = event_map_.at(typeid(decltype(event)));
        for (const auto &func : functions_to_call)
        {
            func();
        }
    }

    template<deep::concepts::Event EventLike, typename FunctionType>
    void subscribe(FunctionType func)
    {
        const std::type_index event_id = typeid(EventLike);

        // If we have the thing in the map already, add the function to the vector
        if (event_map_.contains(event_id))
        {
            auto &functions_to_call = event_map_.at(event_id);
            functions_to_call.push_back(func);;
        }
        else
        {
            // Otherwise, create a vector with the function in it, and add it to the map
            event_map_.emplace(typeid(EventLike), std::vector<std::function<void(void)>>{func});
        }
    }

  private:
    //  Event map is shared amongst all EventDispatchers
    // TODO: Thread Safety
    // TODO: Faster flatter map
    // TODO: Probably don't use typeid, this is a good first go though :)
    inline static std::unordered_map<std::type_index, std::vector<std::function<void(void)>>> event_map_;
};
}