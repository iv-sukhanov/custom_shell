#pragma once

#include <memory>
#include <string>
#include <vector>

#include "Command.hpp"

class Parser {
 public:
  std::vector<std::unique_ptr<Command>> parse(const std::string&);
};
