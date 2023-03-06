#pragma once

#include <memory>
#include <string_view>

#include "types/deep_concepts.h"

// TODO: Add docs about exactly what something has to be to be a Logger_t
// TODO: Maybe enforce with templates  for better compiler errors ???
struct Logger_t
{
    template<deep::concepts::Logger T>
    explicit Logger_t(T t) noexcept
      : self{ std::make_unique<Implementation_t<T>>(std::move(t)) }
    {
    }

    ~Logger_t() = default;
    Logger_t(const Logger_t& other) = delete;
    Logger_t& operator=(const Logger_t& other) = delete;
    Logger_t(Logger_t&& other) noexcept = default;
    Logger_t& operator=(Logger_t&& other) noexcept = default;

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
