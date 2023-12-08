#pragma once

#include <any>
#include <concepts>
#include <memory>
#include <string_view>

#include "logger/logger.h"

namespace deep
{

struct Layer_t
{
    template<typename T>
    explicit Layer_t(T &&t) noexcept : self{ std::make_unique<Implementation_t<T>>(std::forward<T>(t)) }
    {
    }// cppcheck-suppress noExplicitConstructor

    ~Layer_t() = default;
    Layer_t(const Layer_t &other) = delete;
    Layer_t &operator=(const Layer_t &other) = delete;

    Layer_t(Layer_t &&other) noexcept : self(std::move(other.self))
    {
        deep::Logger::debug_core("Move Constructor Called");
    }

    Layer_t &operator=(Layer_t &&other) noexcept
    {
        deep::Logger::debug_core("Move Assignment Operator Called");

        self = std::move(other.self);

        return *this;
    }

    void on_attach() { self->on_attach(); }
    void on_detach() { self->on_detach(); }
    void on_update() { self->on_update(); }

  private:
    struct Interface_t
    {
        virtual ~Interface_t() = default;
        virtual void on_attach() = 0;
        virtual void on_detach() = 0;
        virtual void on_update() = 0;
    };

    template<typename T> struct Implementation_t : Interface_t
    {
        explicit Implementation_t(T s) noexcept : self_(std::move(s)) {}

        void on_attach() override { self_.on_attach(); }
        void on_detach() override { self_.on_detach(); }
        void on_update() override { self_.on_update(); }

      private:
        T self_;
    };

    std::unique_ptr<Interface_t> self;
};

}// namespace deep