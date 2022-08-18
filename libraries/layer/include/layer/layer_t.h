#pragma once

#include <memory>
#include <string_view>

#include "events/event.h"
#include "logger/logger.h"

struct Layer_t
{
    template<typename T>
    Layer_t(T t) noexcept
      : self{ std::make_unique<Implementation_t<T>>(std::move(t)) }
    {
    }

    ~Layer_t() = default;
    Layer_t(const Layer_t& other) = delete;
    Layer_t& operator=(const Layer_t& other) = delete;

    Layer_t(Layer_t&& other) noexcept
      : self(std::move(other.self))
    {
        deep::Logger::debug_core("Move Constructor Called");
    }

    Layer_t& operator=(Layer_t&& other) noexcept
    {
        deep::Logger::debug_core("Move Assignment Operator Called");

        self = std::move(other.self);

        return *this;
    }

    void on_attach() { self->on_attach(); }

    void on_detach() { self->on_detach(); }

    void on_update() { self->on_update(); }

    void on_event() { self->on_event(); }

  private:
    struct Interface_t
    {
        virtual ~Interface_t() = default;
        virtual void on_attach() = 0;
        virtual void on_detach() = 0;
        virtual void on_update() = 0;
        virtual void on_event() = 0;
    };

    template<typename T>
    struct Implementation_t : Interface_t
    {
        explicit Implementation_t(T s) noexcept
          : self{ std::move(s) }
        {
        }
        void on_attach() override { self.on_attach(); }
        void on_detach() override { self.on_detach(); }
        void on_update() override { self.on_update(); }
        void on_event() override { self.on_event(); }

      private:
        T self;
    };

    std::unique_ptr<Interface_t> self;
};

