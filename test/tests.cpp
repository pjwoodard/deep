#include <catch2/catch_test_macros.hpp>

#include "math/vector.h"

TEST_CASE("Anything works", "[vector]")
{
    const Vector vec;
    auto vector_x_coordinate = vec.X();
    CHECK(vector_x_coordinate == 0.0F);
}
