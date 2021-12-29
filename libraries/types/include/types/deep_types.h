#pragma once

#include <type_traits>
#include <named_type.hpp>

namespace deep::types
{
    enum class OpenGLDataType : GLenum {
        FLOAT = GL_FLOAT
    };

    // Strongly typed width and height typedefs
    using Width = fluent::NamedType<int32_t, struct WidthTag>;
    using Height = fluent::NamedType<int32_t, struct HeightTag>;
}
