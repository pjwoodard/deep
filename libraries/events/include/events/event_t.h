#pragma once

#include <memory>
#include <string_view>

#include "events.h"
#include "events/event_t.h"
#include "logger/logger.h"

namespace deep::events {
struct Event_t
{
    template<typename T>
    explicit Event_t(T t) noexcept
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

    EventType get_event_type() const { return self->get_event_type(); }

  private:
    struct Interface_t
    {
        virtual ~Interface_t() = default;
        virtual EventType get_event_type() const = 0;
    };

    template<typename T>
    struct Implementation_t : public Interface_t
    {
        explicit Implementation_t(T s) noexcept
          : self{ std::move(s) }
        {
        }

        EventType get_event_type() const override { return self.get_event_type(); }

      private:
        T self;
    };

    std::unique_ptr<Interface_t> self;
};
}
