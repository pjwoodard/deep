#pragma once

#include <memory>
#include <string_view>

#include "logger/logger.h"
#include "events/event_t.h"

namespace deep {
struct Event_t
{
    template<typename T>
    Event_t(T t) noexcept
      : self{ std::make_unique<Implementation_t<T>>(std::move(t)) }
    {
    }

    ~Event_t() = default;
    Event_t(const Event_t& other) = delete;
    Event_t& operator=(const Event_t& other) = delete;

    Event_t(Event_t&& other) noexcept
      : self(std::move(other.self))
    {
        deep::Logger::debug_core("Move Constructor Called");
    }

    Event_t& operator=(Event_t&& other) noexcept
    {
        deep::Logger::debug_core("Move Assignment Operator Called");

        self = std::move(other.self);

        return *this;
    }

    void get_event_type() { self->get_event_type(); }

  private:
    struct Interface_t
    {
        virtual ~Interface_t() = default;
        virtual void get_event_type() = 0;
    };

    template<typename T>
    struct Implementation_t : Interface_t
    {
        explicit Implementation_t(T s) noexcept
          : self{ std::move(s) }
        {
        }
        void get_event_type() override { self.get_event_type(); }

      private:
        T self;
    };

    std::unique_ptr<Interface_t> self;
};
}
