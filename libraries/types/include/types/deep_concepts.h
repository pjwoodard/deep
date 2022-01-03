#pragma once

#include <type_traits>
#include <concepts>

namespace deep::concepts {
template<class T>
concept scoped_enum_type = std::is_scoped_enum_v<T>;

template<typename T>
concept Numeric = std::floating_point<T> || std::integral<T>;

template<typename T>
concept OpenGLUniform = Numeric<T> || std::same_as<bool, T>;

template<typename T>
concept Window = requires(T a)
{
    a.display();
    a.width();
    a.height();
};

constexpr auto to_integral(const scoped_enum_type auto e) -> std::underlying_type_t<decltype(e)>
{
    return static_cast<std::underlying_type_t<decltype(e)>>(e);
}

}
