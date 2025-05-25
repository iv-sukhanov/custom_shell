/**
 * @file Shell.hpp
 * @brief Contains a Shell class
 * @author Sukhanov Ivan
 * @date 25/05/2025
 * @version 1.0
 */

#pragma once

#include <memory>
#include <string>
#include <vector>

#include "Executor.hpp"
#include "Parser.hpp"

/**
 * @class Shell
 * @brief The class represents a shell that can execute commands interactively or from a file.
 *
 * The Shell class provides functionality to run commands either interactively through user input or by
 * reading commands from a specified file. It uses a parser to interpret the commands and an executor to run
 * them. It displays a prompt to the user and handles input lines, processing them into commands that can be
 * executed.
 *
 * @author Sukhanov Ivan
 * @date 25/05/2025
 */
class Shell {
   public:
    /// @brief Constructs a new Shell instance.
    Shell();

    /// @brief Runs the shell interactively.
    void run();

    /**
     * @brief Runs the shell with commands from the specified file.
     * @param filename The path to the file containing shell commands.
     */
    void run(const std::string& filename);

   private:
    /// @brief The prompt title displayed to the user.
    static const char* PROMPT_TITLE;

    /**
     * @brief Handles a single line of user input.
     * @param line The input line to process.
     */
    void handleInputLine(const std::string& line);

    /**
     * @brief Reads a line of input from the user.
     * @return The input line as a string.
     */
    static std::string readInput();

    /// @brief Displays the shell prompt to the user.
    static void displayPrompt();

    /// @brief Parser for interpreting user input.
    std::unique_ptr<Parser> parser;

    /// @brief Executor for running parsed commands.
    std::unique_ptr<Executor> executor;
};
