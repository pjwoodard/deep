#include <catch2/catch.hpp>

#include "layer/layer.h"
#include "layer/layer_stack.h"

TEST_CASE("Push one item", "[layer_stack]")
{
    deep::LayerStack stack_of_layers;

    // Push a layer on, make sure our stack isn't empty
    stack_of_layers.push_layer(deep::Layer{});
    REQUIRE(stack_of_layers.empty() == false);
    REQUIRE(stack_of_layers.size() == 1);

    // Take a layer off, make sure our stack is empty
    stack_of_layers.pop_layer();

    deep::Layer_t layer{deep::Layer{}};

    REQUIRE(stack_of_layers.empty());
}
