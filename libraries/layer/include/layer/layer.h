#pragma once

#include "layer_t.h"

namespace deep
{

class Layer
{
  public:
    // TODO: unmake static when they are no longer static
    static void on_attach() {}
    static void on_detach() {}
    static void on_update() {}
};

}// namespace deep
