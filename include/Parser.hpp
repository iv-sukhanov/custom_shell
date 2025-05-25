/**
 * @file Parser.hpp
 * @brief Contains a Parser class
 * @author Sukhanov Ivan
 * @date 25/05/2025
 * @version 1.0
 */

#pragma once

#include <regex>
#include <string>
#include <vector>

#include "Command.hpp"

/**
 * @class Parser
 * @brief The class parses a string into instances of class Command
 *
 * The main purpose of the class is to get a line and parse it, dealing with parallel symbols (&), redirection
 * symbols (>), executable name and args, respecting quotes (both ' and "), and escape sequences (like \")
 *
 * @author Sukhanov Ivan
 * @date 25/05/2025
 */
class Parser {
   public:
    /// @brief Constructs a Parser object.
    Parser();

    /**
     * @brief Parses the input string and returns a vector of Command objects.
     * @param input The command line string to parse.
     * @return std::vector<std::unique_ptr<Command>> Parsed commands.
     */
    std::vector<std::unique_ptr<Command>> parse(const std::string&);

   private:
    /**
     * @brief Composes a Command object from the given job string.
     * @param job The job string to parse.
     * @param redirect Indicates if output redirection is present.
     * @param parallel Indicates if the command should be run in parallel.
     * @return std::unique_ptr<Command> The composed Command object.
     */
    std::unique_ptr<Command> composeCommand(const std::string& job, bool redirect, bool parallel);

    /// @brief Regular expression for detecting parallel execution symbols.
    static std::regex parallelSymb;

    /// @brief Regular expression for detecting output redirection symbols.
    static std::regex redirectSymb;

    /// @brief String containing whitespace and space-like symbols for parsing.
    static std::string spaceSymbols;
};
