#pragma once

#include <string_view>

#include "logger/logger_t.h"
#include "logger/spd_logger.h"
#include "types/deep_concepts.h"

namespace deep
{

class Logger
{
  public:
    static void register_logger(Logger_t logger) { logger_ = std::move(logger); }

    static void debug_core(std::string_view debug_msg) { logger_.debug(debug_msg); }
    static void info_core(std::string_view info_msg) { logger_.info(info_msg); }
    static void warn_core(std::string_view warn_msg) { logger_.warn(warn_msg); }
    static void error_core(std::string_view error_msg) { logger_.error(error_msg); }
    static void critical_core(std::string_view critical_msg) { logger_.critical(critical_msg); }

    static void assert_and_log(std::string_view assert_msg, bool predicate)
    {
        if (!predicate)
        {
            logger_.critical(assert_msg);
        }

        assert(predicate);
    }

    //    TODO - Maybe implement multiple loggers / ability to reference any arbitrary logger by name and use it to log
  private:
    // We default to spdlog for our logger
    inline static Logger_t logger_{ SpdLogger("Core Logger") };
};
}; // namespace deep