#pragma once

#include <string_view>

#include "logger/spd_logger.h"
#include "types/deep_concepts.h"

namespace deep {
// This struct is used to hide the template details from the user
// and to contain all of our different system loggers
template<deep::concepts::Logger TLogger>
struct LoggerGroup
{
    // Have a client logger and a core logger, could expand these to be two different LoggerTypes in the future
    TLogger core_logger_{ "Core" };
    TLogger client_logger_{ "Client" };
};

class Logger
{
  public:
    static void debug_core(std::string_view debug_msg) { loggers_.core_logger_.debug(debug_msg); }
    static void info_core(std::string_view info_msg) { loggers_.core_logger_.info(info_msg); }
    static void warn_core(std::string_view warn_msg) { loggers_.core_logger_.warn(warn_msg); }
    static void error_core(std::string_view error_msg) { loggers_.core_logger_.error(error_msg); }
    static void critical_core(std::string_view critical_msg) { loggers_.core_logger_.critical(critical_msg); }

    static void debug_client(std::string_view debug_msg) { loggers_.core_logger_.debug(debug_msg); }
    static void info_client(std::string_view info_msg) { loggers_.core_logger_.info(info_msg); }
    static void warn_client(std::string_view warn_msg) { loggers_.core_logger_.warn(warn_msg); }
    static void error_client(std::string_view error_msg) { loggers_.core_logger_.error(error_msg); }
    static void critical_client(std::string_view critical_msg) { loggers_.core_logger_.critical(critical_msg); }

  private:
    // Change out logger implementation here
    // Warning that is silenced is warning about losing exceptions thrown on statically initialized variables
    // We disable exceptions anyway
    inline static const LoggerGroup<SpdLogger> loggers_; // NOLINT(cert-err58-cpp)
};
};