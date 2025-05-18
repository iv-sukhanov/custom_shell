#pragma once

#include "Command.hpp"

class Executor {
 public:
  Executor();
  void execute(Command& cmd) const;
};
