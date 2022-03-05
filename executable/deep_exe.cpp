#include <GLFW/glfw3.h>            // for glfwTerminate
#include <chrono>                  // for literals
#include <string_view>             // for operator""sv
#include "logger/logger.h"
#include "logger/spdlog_logger.h"

using namespace std::literals;

int main()
{
    DeepLogger<SpdlogLogger> logger;
    logger.debug_core("What");
    logger.info_core("info");
    logger.warn_core("Please");
    logger.error_core("Kill me");
    logger.critical_core("what");
    return 0;
}

