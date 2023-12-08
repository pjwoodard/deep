#pragma once

#include <named_type.hpp>
#include <optional>

namespace deep::types
{
// Strongly typed width and height typedefs
using Width = fluent::NamedType<int32_t, struct WidthTag>;
using Height = fluent::NamedType<int32_t, struct HeightTag>;
using VertexShaderSource = fluent::NamedType<std::string_view, struct VertexShaderTag>;
using FragmentShaderSource = fluent::NamedType<std::string_view, struct FragmentShaderTag>;
using GeometryShaderSource = fluent::NamedType<std::string_view, struct GeometryShaderTag>;
}// namespace deep::types
