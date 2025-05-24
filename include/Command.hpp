/**
 * @file Command.hpp
 * @brief Contains a Command class
 * @author Sukhanov Ivan
 * @date 25/05/2025
 * @version 1.0
 */

#pragma once

#include <optional>
#include <string>
#include <vector>

/**
 * @class Command
 * @brief The class represents a single command.
 *
 * The class contains all the information about a single command including name, arguments, file of the
 * redirected output, and flag denoting if the command was ment to run in backgroung.
 * All the methods are getters/setters, so its use case is just to passively store the data.
 *
 * @author Sukhanov Ivan
 * @date 25/05/2025
 */
class Command {
   public:
    /**
     * @brief Constructs a Command with a name and arguments.
     * @param name The name of the command.
     * @param args The arguments for the command.
     */
    Command(const std::string& name, const std::vector<std::string>& args);

    /**
     * @brief Gets the name of the command.
     * @return The command name.
     */
    std::string getName() const;

    /**
     * @brief Gets the arguments of the command.
     * @return The command arguments.
     */
    std::vector<std::string> getArgs() const;

    /**
     * @brief Sets the file to which the command's output should be redirected.
     * @param file The output file path.
     */
    void setOutputRedirect(const std::string& file);

    /**
     * @brief Gets the output redirection file, if set.
     * @return The output file path, or std::nullopt if not set.
     */
    std::optional<std::string> getOutputRedirect() const;

    /**
     * @brief Sets whether the command should run in parallel.
     * @param parallel True to run in parallel, false otherwise.
     */
    void setParallel(bool parallel);

    /**
     * @brief Checks if the command is set to run in parallel.
     * @return True if parallel, false otherwise.
     */
    bool isParallel() const;

   private:
    std::string name;
    std::vector<std::string> args;
    std::optional<std::string> outputFile;
    bool inParallel;
};
