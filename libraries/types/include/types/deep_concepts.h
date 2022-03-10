#pragma once

#include <type_traits>
#include <concepts>
#include <string_view>

namespace deep::concepts {
template<class T>
concept scoped_enum_type = std::is_scoped_enum_v<T>;

template<typename T>
concept Numeric = std::floating_point<T> || std::integral<T>;

template<typename T>
concept OpenGLUniform = Numeric<T> || std::same_as<bool, T>;

template<typename T>
concept Window = requires(T a, bool boolean)
{
    a.width();
    a.height();
    a.set_vsync(boolean);
    {a.is_vsync()} -> std::same_as<bool>;
};

template<typename T>
concept LoggerType = requires(T a, std::string_view str)
{
    a.debug(str);
    a.info(str);
    a.warn(str);
    a.error(str);
    a.critical(str);
};

constexpr auto to_integral(const scoped_enum_type auto e) -> std::underlying_type_t<decltype(e)>
{
    return static_cast<std::underlying_type_t<decltype(e)>>(e);
}

}
