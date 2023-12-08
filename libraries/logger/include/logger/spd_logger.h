#pragma once

#include <memory>
#include <string_view>

#include <spdlog/spdlog.h>

class SpdLogger
{
  public:
    explicit SpdLogger(std::string_view name);

    void debug(std::string_view message) const;
    void info(std::string_view message) const;
    void warn(std::string_view message) const;
    void error(std::string_view message) const;
    void critical(std::string_view message) const;

  private:
    std::shared_ptr<spdlog::logger> log_impl_{};
};