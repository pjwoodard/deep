#include <format>
#include <iostream>

#include "logger/stdout_logger.h"

 void StdoutLogger::debug(std::string_view message)
{
    std::cout << std::format("DEBUG: {}", message) << '\n';
}

void StdoutLogger::info(std::string_view message)
{
    debug(message);
}

void StdoutLogger::warn(std::string_view message)
{
    debug(message);
}

void StdoutLogger::error(std::string_view message)
{
    debug(message);
}

void StdoutLogger::critical(std::string_view message)
{
    debug(message);
}
