/**
 * @file Executor.hpp
 * @brief Contains an Executor class
 * @author Sukhanov Ivan
 * @date 25/05/2025
 * @version 1.0
 */

#pragma once

#include <string_view>
#include <unordered_map>
#include <vector>

#include "Command.hpp"

/**
 * @class Executor
 * @brief Execures a given command
 *
 * The main execute() function accepts a command, then decides if the command is built-in or external. In case
 * of built-in, the corresponding member function is called, otherwise an external executable is called by a
 * child process. Depending on Command passed, it can be executed in background, with or without redirection.
 *
 * @author Sukhanov Ivan
 * @date 25/05/2025
 */
class Executor {
   public:
    /// @brief Constructs an Executor object.
    Executor();

    /**
     * @brief Executes the given command.
     * @param cmd The command to execute.
     */
    void execute(Command& cmd);

   private:
    /**
     * @brief Checks if the given command is a built-in command.
     * @param cmd The command to check.
     */
    static bool isBuiltin(const Command& cmd);

    /**
     * @brief Executes a built-in command.
     * @param cmd The built-in command to execute.
     */
    void executeBuiltin(const Command& cmd);

    /**
     * @brief Executes an external command.
     * @param cmd The external command to execute.
     */
    void executeExternal(const Command& cmd);

    /**
     * @brief Handles output redirection for a command.
     * @param cmd The command with possible redirections.
     */
    static void handleRedirect(const Command& cmd);

    using Args = std::vector<std::string>;
    using BuiltinFunction = void (Executor::*)(const Args&);

    /// @brief Map of built-in command names to their corresponding member functions.
    static const std::unordered_map<std::string_view, BuiltinFunction> builtinCommands;

    /**
     * @brief Changes the current working directory.
     * @param cmd Arguments for the cd command.
     */
    void cd(const Args& cmd);

    /**
     * @brief Exits the shell.
     * @param cmd Arguments for the exit command.
     */
    void exit(const Args& cmd);

    /**
     * @brief Modifies the search path.
     * @param cmd Paths to add to search path.
     */
    void path(const Args& cmd);

    /// @brief List of directories to search for executables (PATH).
    std::vector<std::string> searchPath;

    /**
     * @brief Looks up the command path in the search path.
     * @param cmd The command to look up.
     * @return The path to the executable, or the original command if not found.
     */
    std::string lookupPath(const std::string& cmd) const;

    /// @brief Registers the signal handler for zombie process termination.
    void registerSignalHangler();

    /**
     * @brief Signal handler for reaping child processes.
     * @param signal The signal number.
     */
    static void reapChildren(int signal);
};
