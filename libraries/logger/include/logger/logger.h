#pragma once

#include <string_view>

#include "types/deep_concepts.h"
#include "logger/spd_logger.h"

namespace deep
{
class Logger 
{
public:
    static void debug_core(std::string_view debug_msg) {core_logger_.debug(debug_msg);}
    static void info_core(std::string_view info_msg) {core_logger_.info(info_msg);}
    static void warn_core(std::string_view warn_msg) {core_logger_.warn(warn_msg);}
    static void error_core(std::string_view error_msg) {core_logger_.error(error_msg);}
    static void critical_core(std::string_view critical_msg) {core_logger_.critical(critical_msg);}

private:
    // Have a client logger and a core logger
    inline static SpdLogger core_logger_{"Core"};
    inline static SpdLogger client_logger_{"Client"};
};
};