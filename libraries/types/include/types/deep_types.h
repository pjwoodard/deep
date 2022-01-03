#pragma once

#include <optional>
#include <named_type.hpp>

namespace deep::types
{
    // Strongly typed width and height typedefs
    using Width = fluent::NamedType<int32_t, struct WidthTag>;
    using Height = fluent::NamedType<int32_t, struct HeightTag>;
    using VertexShaderSource = fluent::NamedType<std::string_view, struct VertexShaderTag>;
    using FragmentShaderSource = fluent::NamedType<std::string_view, struct FragmentShaderTag>;
    using GeometryShaderSource = fluent::NamedType<std::string_view, struct GeometryShaderTag>;
}
