#pragma once

#include <memory>
#include <string_view>

#include "events.h"
#include "events/event_t.h"
#include "logger/logger.h"

namespace deep::events
{
struct Event_t
{
    explicit Event_t(deep::events::Event auto &&arg) noexcept
      : self{ std::make_unique<Implementation_t<decltype(arg)>>(std::forward<decltype(arg)>(arg)) }
    {
    }

    ~Event_t() = default;
    Event_t(const Event_t &other) = delete;
    Event_t &operator=(const Event_t &other) = delete;

    Event_t(Event_t &&other) noexcept : self(std::move(other.self))
    {
        deep::Logger::debug_core("Move Constructor Called");
    }

    Event_t &operator=(Event_t &&other) noexcept
    {
        deep::Logger::debug_core("Move Assignment Operator Called");

        self = std::move(other.self);

        return *this;
    }

    [[nodiscard]] EventType get_event_type() const { return self->get_event_type(); }

    template<typename Derived, typename Base> std::unique_ptr<Derived> static_ptr_cast(Event_t base) const noexcept
    {
        auto derived_ptr = static_cast<Derived *>(base.self.release());
        return std::unique_ptr<Derived>(derived_ptr);
    }

  private:
    struct Interface_t
    {
        virtual ~Interface_t() = default;
        virtual EventType get_event_type() const = 0;
    };

    template<typename T> struct Implementation_t : public Interface_t
    {
        explicit Implementation_t(T &&arg) noexcept : self{ std::forward<decltype(arg)>(arg) } {}

        EventType get_event_type() const override { return self.get_event_type(); }

      private:
        std::decay_t<T> self;
    };

    std::unique_ptr<Interface_t> self;
};
}// namespace deep::events
