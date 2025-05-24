#pragma once

#include <functional>
#include <memory>
#include <regex>
#include <string>
#include <vector>

#include "Command.hpp"

class Parser {
   public:
    Parser();
    std::vector<std::unique_ptr<Command>> parse(const std::string&);

   private:
    std::unique_ptr<Command> composeCommand(const std::string& job, bool redirect, bool parallel);

    static std::regex parallelSymb;
    static std::regex redirectSymb;
    static std::string spaceSymbols;
};
