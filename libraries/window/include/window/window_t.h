#pragma once

#include <memory>
#include <string_view>

#include "events/event_t.h"
#include "logger/logger.h"

namespace deep {
struct Window_t
{
    template<typename T>
    Window_t(T t) noexcept
      : self_{ std::make_unique<Implementation_t<T>>(std::move(t)) }
    {
    }

    ~Window_t() = default;
    Window_t(const Window_t& other) = delete;
    Window_t& operator=(const Window_t& other) = delete;

    Window_t(Window_t&& other) noexcept
      : self_(std::move(other.self_))
    {
        deep::Logger::debug_core("Move Constructor Called");
    }

    Window_t& operator=(Window_t&& other) noexcept
    {
        deep::Logger::debug_core("Move Assignment Operator Called");

        self_ = std::move(other.self_);

        return *this;
    }

    int32_t width()
    {
        return self_->width();
    }

    int32_t height()
    {
        return self_->height();
    }

  private:
    struct Interface_t
    {
        virtual ~Interface_t() = default;
        virtual int32_t width() = 0;
        virtual int32_t height() = 0;
    };

    template<typename T>
    struct Implementation_t : Interface_t
    {
        explicit Implementation_t(T s) noexcept
          : self_{ std::move(s) }
        {
        }

        int32_t width() override { return self_.width(); }
        int32_t height() override { return self_.height(); }

      private:
        T self_;
    };

    std::unique_ptr<Interface_t> self_;
};

}