#include <iostream>

#include <catch2/catch.hpp>

#include "events/event_dispatcher.h"
#include "events/events.h"

class TestEvent
{
  public:
    void get_event_type() {}
};


TEST_CASE("Events are called", "[event]")
{
    deep::EventDispatcher dispatcher;

    dispatcher.subscribe<deep::WindowResizedEvent>([](){
                  std::cout << "Ooooooh boyo\n";
              });

    dispatcher.subscribe<deep::WindowResizedEvent>([](){
      std::cout << "Ooooooh boyo 2 tho lmao eeeeey\n";
    });

    dispatcher.subscribe<TestEvent>([](){
                  std::cout << "Uh oh, spaghettio\n";
              });

    dispatcher.publish(TestEvent{});
    dispatcher.publish(deep::WindowResizedEvent{});
}
