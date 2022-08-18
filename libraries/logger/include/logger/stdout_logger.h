#pragma once

#include <iostream>

class StdoutLogger
{
  public:
    explicit StdoutLogger(std::string_view name) : name_{name} {};

    void debug(std::string_view message) const;
    void info(std::string_view message) const;
    void warn(std::string_view message) const;
    void error(std::string_view message) const;
    void critical(std::string_view message) const;

  private:
    std::string name_;
};