#pragma once

#include "layer_t.h"

namespace deep {

class Layer
{
  public:
    void on_attach() {}
    void on_detach() {}
    void on_update() {}
    void on_event(const deep::Event_t &/*event*/) {}
};

} // deep
