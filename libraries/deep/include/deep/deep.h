#pragma once

#include "types/deep_concepts.h"
#include "events/event.h"

namespace deep
{
// Contains
enum class DeepState
{
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN
};

class Deep
{
  public:
    // Our constructor accepts anything that satisfies the window concept
    explicit Deep();

  private:
    EventDispatcher event_dispatcher_;
};
}
