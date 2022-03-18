#include <typeindex>
#include <unordered_map>
#include <functional>

#include "types/deep_concepts.h"

namespace deep {
class WindowResizedEvent
{};

class EventDispatcher
{
  public:
    void publish();

    template<typename SubscriberType, deep::concepts::Event EventLike>
    void subscribe()
    {

    }

private:
    //  Event map is shared amongst all EventDispatchers
  // TODO: Thread Safety
  // TODO: Faster flatter map
  static std::unordered_map<std::type_index, std::function<int(int)>> event_map_;
};
}