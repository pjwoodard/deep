#pragma once

#include <concepts>
#include <string_view>
#include <type_traits>

namespace deep::concepts
{
template<typename T>
concept RealNumber = std::floating_point<T> || std::integral<T>;

template<typename T>
concept OpenGLUniform = RealNumber<T> || std::same_as<bool, T>;

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

template<typename LayerType>
concept Layer = requires(LayerType layer)
{
    layer.on_attach();
    layer.on_detach();
    layer.on_update();
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

template<typename GraphicsApiType>
concept GraphicsApi = requires(GraphicsApiType api)
{
    api.initialize();
};

}// namespace deep::concepts
