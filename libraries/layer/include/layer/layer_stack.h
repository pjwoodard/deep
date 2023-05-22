#pragma once

#include "layer/layer_t.h"

namespace deep {
class LayerStack
{

  public:
    void push_layer(deep::Layer_t layer);
    deep::Layer_t& pop_layer();
    [[nodiscard]] bool empty() const { return layer_stack_.empty(); }
    [[nodiscard]] size_t size() const { return layer_stack_.size(); }

  private:
    std::vector<Layer_t> layer_stack_;
};
}