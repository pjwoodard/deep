#pragma once

#include <string_view>

#include "logger/spd_logger.h"
#include "types/deep_concepts.h"

namespace deep {
struct LoggerType
{
    template<typename T>
    LoggerType(T t) noexcept
      : self{ std::make_unique<Implementation_t<T>>(std::move(t)) }
    {
    }

    ~LoggerType() = default;
    LoggerType(const LoggerType& other) = delete;
    LoggerType& operator=(const LoggerType& other) = delete;

    LoggerType(LoggerType&& other) noexcept
      : self(std::move(other.self))
    {
        debug("Move Constructor Called");
    }

    LoggerType& operator=(LoggerType&& other) noexcept
    {
        debug("Move Assignment Operator Called");

        self = std::move(other.self);

        return *this;
    }

    void debug(std::string_view msg) { self->debug(msg); }

    void info(std::string_view msg) { self->info(msg); }

    void warn(std::string_view msg) { self->warn(msg); }

    void error(std::string_view msg) { self->error(msg); }

    void critical(std::string_view msg) { self->critical(msg); }

  private:
    struct Interface_t
    {
        virtual ~Interface_t() = default;
        virtual void debug(std::string_view msg) = 0;
        virtual void info(std::string_view msg) = 0;
        virtual void warn(std::string_view msg) = 0;
        virtual void error(std::string_view msg) = 0;
        virtual void critical(std::string_view msg) = 0;
    };

    template<typename T>
    struct Implementation_t : Interface_t
    {
        explicit Implementation_t(T s) noexcept
          : self{ std::move(s) }
        {
        }
        void debug(std::string_view msg) override { self.debug(msg); }
        void info(std::string_view msg) override { self.info(msg); }
        void warn(std::string_view msg) override { self.warn(msg); }
        void error(std::string_view msg) override { self.error(msg); }
        void critical(std::string_view msg) override { self.critical(msg); }

      private:
        T self;
    };

    std::unique_ptr<Interface_t> self;
};

class Logger
{
  public:
    static void register_logger(LoggerType logger) { logger_ = std::move(logger); }

    static void debug_core(std::string_view debug_msg) { logger_.debug(debug_msg); }
    static void info_core(std::string_view info_msg) { logger_.info(info_msg); }
    static void warn_core(std::string_view warn_msg) { logger_.warn(warn_msg); }
    static void error_core(std::string_view error_msg) { logger_.error(error_msg); }
    static void critical_core(std::string_view critical_msg) { logger_.critical(critical_msg); }

    static void debug_client(std::string_view debug_msg) { logger_.debug(debug_msg); }
    static void info_client(std::string_view info_msg) { logger_.info(info_msg); }
    static void warn_client(std::string_view warn_msg) { logger_.warn(warn_msg); }
    static void error_client(std::string_view error_msg) { logger_.error(error_msg); }
    static void critical_client(std::string_view critical_msg) { logger_.critical(critical_msg); }

  private:
    // We default to spdlog for our logger
    inline static LoggerType logger_{ SpdLogger("Core Logger") };
};
};