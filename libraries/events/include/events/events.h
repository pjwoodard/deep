#pragma once

#include "events/event_t.h"

namespace deep::events
{

enum class EventType
{
    WindowResizedEvent,
    MouseButtonPressedEvent,
    KeyPressedEvent
};

struct WindowResizedEvent
{
  public:
    EventType get_event_type() const { return EventType::WindowResizedEvent; };
//    int32_t width_{0};
//    int32_t height_{0};
};

struct MouseButtonPressedEvent
{
  public:
    void get_event_type(){};
};

struct KeyPressedEvent
{
  public:
    void get_event_type(){};
};

}