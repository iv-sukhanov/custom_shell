#include "Shell.hpp"

#include <csignal>
#include <exception>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include "Parser.hpp"

Shell::Shell() {
    this->parser = std::make_unique<Parser>();
    this->executor = std::make_unique<Executor>();
};

const char* Shell::PROMPT_TITLE = "ishell";

void Shell::run() {
    using namespace std;

    while (true) {
        displayPrompt();
        string line = readInput();

        if (line.empty()) {
            continue;
        }

        vector<unique_ptr<Command>> commands;
        try {
            commands = parser->parse(line);
        } catch (exception& e) {
            cerr << "error: " << e.what();
            continue;
        } catch (...) {
            cerr << "unknown exception";
            continue;
        }

        for (const auto& command : commands) {
            try {
                executor->execute(*command);
                cout << "finished" << endl;
            } catch (exception& e) {
                cerr << "error: " << e.what();
                continue;
            } catch (...) {
                cerr << "unknown exception";
                continue;
            }
        }
    }
}

void Shell::run(const std::string& filename) {
    std::cout << "batchmode called for " << filename;
}

std::string Shell::readInput() {
    std::string input;
    std::getline(std::cin, input);
    return input;
}

void Shell::displayPrompt() {
    std::cout << Shell::PROMPT_TITLE << "> " << std::flush;
}
