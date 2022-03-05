#pragma once

#include <string_view>

#include "spdlog/spdlog.h"
#include "types/deep_concepts.h"

template<deep::concepts::Logger T>
class DeepLogger 
{
public:
    DeepLogger(){};

    void debug_core(std::string_view debug_msg) {core_logger_.debug(debug_msg);}
    void info_core(std::string_view info_msg) {core_logger_.info(info_msg);}
    void warn_core(std::string_view warn_msg) {core_logger_.warn(warn_msg);}
    void error_core(std::string_view error_msg) {core_logger_.error(error_msg);}
    void critical_core(std::string_view critical_msg) {core_logger_.critical(critical_msg);}

private:
    // Have a client logger and a core logger
    T core_logger_{"Core"};
    T client_logger_{"Client"};
};
