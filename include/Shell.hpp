#pragma once

#include <memory>
#include <string>
#include <vector>

#include "Executor.hpp"
#include "Parser.hpp"

class Shell {
   public:
    Shell();
    void run();
    void run(const std::string& filename);

   private:
    static const char* PROMPT_TITLE;

    void handleInputLine(const std::string& line);

    static std::string readInput();
    static void displayPrompt();

    std::unique_ptr<Parser> parser;
    std::unique_ptr<Executor> executor;
};
