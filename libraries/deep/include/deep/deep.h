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
    explicit Deep(const deep::concepts::Window auto &window);

  private:
    [[maybe_unused]] int width_;
    [[maybe_unused]] int height_;
    [[maybe_unused]] DeepState state_;
};

