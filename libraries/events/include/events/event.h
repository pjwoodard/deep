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
    void publish(const deep::concepts::Event auto event)
    {
        // Change this to standard algorithm (find_if)
        for (auto [type_id, func] : event_map_) {
            if (typeid(decltype(event)) == type_id) {
                func();
            }
        }
    }

    template<deep::concepts::Event EventLike, typename FunctionType>
    void subscribe(FunctionType func)
    {
        event_map_.emplace(typeid(EventLike), func);
    }

  private:
    //  Event map is shared amongst all EventDispatchers
    // TODO: Thread Safety
    // TODO: Faster flatter map
    inline static std::unordered_map<std::type_index, std::function<void(void)>> event_map_;
};
}