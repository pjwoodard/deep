#pragma once

#include <iostream>

class StdoutLogger
{
  public:
    explicit StdoutLogger(std::string_view name) : name_{ name } {}

    static void debug(std::string_view message);
    static void info(std::string_view message);
    static void warn(std::string_view message);
    static void error(std::string_view message);
    static void critical(std::string_view message);

  private:
    std::string name_;
};