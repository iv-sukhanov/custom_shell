/**
 * @file Shell.cpp
 * @brief File implemets Shell class
 *
 * The Shell class can be run interactively or with commands from a file.
 * In interactive mode, runs a loop that ends when the user inputs "exit". In batch mode,
 * reads commands from a file, executes them, and then exits. Once recieved a line (no matter from file of
 * user), it parses the line into commands and executes them one by one. Parsing and executing are delegated
 * to Parser and Executor classes respectively.
 *
 * @author Sukhanov Ivan
 * @date 25/5/2025
 * @version 1.0
 */

#include "Shell.hpp"

#include <csignal>
#include <exception>
#include <fstream>
#include <iostream>
#include <istream>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include "Parser.hpp"

/**
 * @brief Constructs a new Shell instance, initializing the parser and executor.
 */
Shell::Shell() {
    this->parser = std::make_unique<Parser>();
    this->executor = std::make_unique<Executor>();
};

/**
 * @brief The prompt title displayed to the user.
 */
const char* Shell::PROMPT_TITLE = "ishell";

/**
 * @brief Runs the shell interactively, reading and executing user input in a loop.
 */
void Shell::run() {
    using namespace std;

    while (true) {
        displayPrompt();
        const string& line = readInput();

        if (line.find_first_not_of(Parser::spaceSymbols) == string::npos) {
            continue;  // Skip empty lines
        }

        handleInputLine(line);
    }
}

/**
 * @brief Runs the shell with commands read from a file.
 * @param filename The path to the file containing shell commands.
 */
void Shell::run(const std::string& filename) {
    using namespace std;

    fstream file{filename, std::ios::in};
    if (!file) {
        cerr << "There is no file '" << filename << "'" << '\n';
        return;
    }

    string line;
    vector<unique_ptr<Command>> commands;
    while (getline(file >> ws, line, '\n')) {
        if (line.empty()) {
            continue;
        }
        handleInputLine(line);
    }
}

/**
 * @brief Parses and executes a single line of input.
 * @param line The input line to process.
 */
void Shell::handleInputLine(const std::string& line) {
    using namespace std;

    vector<unique_ptr<Command>> commands;
    try {
        commands = parser->parse(line);
    } catch (exception& e) {
        cerr << "error: " << e.what() << '\n';
        return;
    } catch (...) {
        cerr << "unknown exception" << '\n';
        return;
    }

    for (const auto& command : commands) {
        try {
            executor->execute(*command);
        } catch (exception& e) {
            cerr << "error: " << e.what() << '\n';
            continue;
        } catch (...) {
            cerr << "unknown exception" << '\n';
            continue;
        }
    }
}

/**
 * @brief Reads a line of input from the user.
 * @return The input line as a string.
 */
std::string Shell::readInput() {
    std::string input;
    std::getline(std::cin, input);
    return input;
}

/**
 * @brief Displays the shell prompt to the user.
 */
void Shell::displayPrompt() {
    std::cout << Shell::PROMPT_TITLE << "> " << std::flush;
}
