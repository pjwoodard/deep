#pragma once

#include <concepts>
#include <string_view>
#include <type_traits>

namespace deep::concepts
{
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
    {
        a.is_vsync()
        } -> std::same_as<bool>;
};

template<typename LoggerType>
concept Logger = requires(LoggerType logger, std::string_view str)
{
    logger.debug(str);
    logger.info(str);
    logger.warn(str);
    logger.error(str);
    logger.critical(str);
};
}// namespace deep::concepts
