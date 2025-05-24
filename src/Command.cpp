/**
 * @file Command.cpp
 * @brief File implemets Command class methods
 *
 * Most of the functions are getters/setters, everything should be clear.
 *
 * @author Sukhanov Ivan
 * @date 25/5/2025
 * @version 1.0
 */

#include "Command.hpp"

#include <string>
#include <utility>
#include <vector>

/**
 * @brief Constructs a Command object with the given name and arguments.
 *
 * @param name The name of the command.
 * @param args The arguments for the command.
 */
Command::Command(const std::string& name, const std::vector<std::string>& args) {
    this->name = name;
    this->args = args;
}

/**
 * @brief Gets the name of the command.
 * @return The command name as a string.
 */
std::string Command::getName() const {
    return this->name;
}

/**
 * @brief Gets the arguments for the command.
 * @return A vector of argument strings.
 */
std::vector<std::string> Command::getArgs() const {
    return this->args;
}

/**
 * @brief Sets the file to which the command's output should be redirected.
 * @param file The output file path.
 */
void Command::setOutputRedirect(const std::string& file) {
    this->outputFile = file;
}

/**
 * @brief Gets the output redirection file, if set.
 * @return An optional string containing the output file path.
 */
std::optional<std::string> Command::getOutputRedirect() const {
    return this->outputFile;
}

/**
 * @brief Sets whether the command should run in parallel.
 * @param inParallel True if the command should run in parallel, false otherwise.
 */
void Command::setParallel(bool inParallel) {
    this->inParallel = inParallel;
}

/**
 * @brief Checks if the command is set to run in parallel.
 * @return True if the command runs in parallel, false otherwise.
 */
bool Command::isParallel() const {
    return this->inParallel;
}
