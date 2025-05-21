#pragma once

#include <string_view>
#include <unordered_map>

#include "Command.hpp"

class Executor {
   public:
    Executor();
    void execute(Command& cmd);

   private:
    static bool isBuiltin(const Command& cmd);
    void executeBuiltin(const Command& cmd);
    void executeExternal(const Command& cmd) const;

    using Args = std::vector<std::string>;
    using BuiltinFunction = void (Executor::*)(const Args&);
    static const std::unordered_map<std::string_view, BuiltinFunction> builtinCommands;

    std::vector<std::string> searchPath;
    std::string getAbsolutePath(const std::string& cmd) const;

    void cd(const Args& cmd);
    void exit(const Args& cmd);
    void path(const Args& cmd);
};
