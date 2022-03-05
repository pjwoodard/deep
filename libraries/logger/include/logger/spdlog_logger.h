#include <string_view>
#include <memory>

#include <spdlog/spdlog.h>

class SpdlogLogger
{
public:
    SpdlogLogger(std::string_view name);

    void debug(std::string_view message);
    void info(std::string_view message);
    void warn(std::string_view message);
    void error(std::string_view message);
    void critical(std::string_view message);

private:
    std::string name_;
    std::shared_ptr<spdlog::logger> log_impl_;
};