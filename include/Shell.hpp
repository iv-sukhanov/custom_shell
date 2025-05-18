#pragma once

#include <memory>

#include "Executor.hpp"
#include "Parser.hpp"

class Shell {
 public:
  Shell();
  void run();

 private:
  std::unique_ptr<Parser> parser;
  std::unique_ptr<Executor> executor;
};
