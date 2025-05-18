#pragma once

#include <memory>
#include <string>

#include "Executor.hpp"
#include "Parser.hpp"

class Shell {
 public:
  Shell();
  void run();

 private:
  inline static const char* PROMPT_TITLE = "ishell";

  static std::string readInput();
  static void displayPrompt();

  std::unique_ptr<Parser> parser;
  std::unique_ptr<Executor> executor;
};
