#include "layer/layer_stack.h"

void deep::LayerStack::push_layer(deep::Layer_t layer)
{
    deep::Logger::debug_core("Rvalue push");
    layer_stack_.emplace_back(std::move(layer));
}

deep::Layer_t& deep::LayerStack::pop_layer()
{
    deep::Layer_t& layer_to_return = layer_stack_.back();

    layer_stack_.pop_back();

    return layer_to_return;
}
