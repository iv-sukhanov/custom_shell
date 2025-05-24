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
    static std::regex parallelSymb;
    static std::regex redirectSymb;
    static std::string spaceSymbols;
};
