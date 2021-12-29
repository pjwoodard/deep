#pragma once

#include "types/deep_concepts.h"

// Contains
enum class DeepState
{
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN
};

class Deep
{
    // Our constructor accepts anything that satisfies the window concept
    Deep(const auto Window &window);
  private:
    DeepState state_;
};

