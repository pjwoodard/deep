#include <spdlog/spdlog.h>

#include "logger/spd_logger.h"
#include "spdlog/sinks/stdout_color_sinks.h"


SpdLogger::SpdLogger(std::string_view name) : log_impl_{ spdlog::stdout_color_mt(name.data()) }
{
    spdlog::set_pattern("%^[%T] %n: %v%$");

    log_impl_->set_level(spdlog::level::trace);
}

void SpdLogger::debug(std::string_view message) const { log_impl_->debug(message); }

void SpdLogger::info(std::string_view message) const { log_impl_->info(message); }

void SpdLogger::warn(std::string_view message) const { log_impl_->warn(message); }

void SpdLogger::error(std::string_view message) const { log_impl_->error(message); }

void SpdLogger::critical(std::string_view message) const { log_impl_->critical(message); }
