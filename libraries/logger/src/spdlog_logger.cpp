#include <spdlog/spdlog.h>

#include "logger/spdlog_logger.h"
#include "spdlog/sinks/stdout_color_sinks.h"


SpdlogLogger::SpdlogLogger(std::string_view name) 
    : log_impl_{spdlog::stdout_color_mt(name.data())}
    , name_(name.data())
{
    spdlog::set_pattern("%^[%T] %n: %v%$");

    log_impl_->set_level(spdlog::level::trace);
}

void SpdlogLogger::debug(std::string_view message)
{
    log_impl_->debug(message);
}

void SpdlogLogger::info(std::string_view message)
{
    log_impl_->info(message);
}

void SpdlogLogger::warn(std::string_view message)
{
    log_impl_->warn(message);
}

void SpdlogLogger::error(std::string_view message)
{
    log_impl_->error(message);
}

void SpdlogLogger::critical(std::string_view message)
{
    log_impl_->critical(message);
}
