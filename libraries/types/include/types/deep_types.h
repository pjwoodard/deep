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

    template<class T>
    concept scoped_enum_type = std::is_scoped_enum_v<T>;

    template <typename T>
    concept Numeric = std::floating_point<T> || std::integral<T>;

    template<typename T>
    concept OpenGLUniform = Numeric<T> || std::same_as<bool, T>;

    constexpr auto to_integral(const scoped_enum_type auto e) -> std::underlying_type_t<decltype(e)>
    {
        return static_cast<std::underlying_type_t<decltype(e)>>(e);
    }
}
