#include "Shell.hpp"

#include <iostream>
#include <memory>
#include <string>

#include "Parser.hpp"

Shell::Shell() {
    this->parser = std::make_unique<Parser>();
    this->executor = std::make_unique<Executor>();
};

void Shell::run() {
    using namespace std;

    while (true) {
        displayPrompt();
        string line = readInput();

        if (line.empty()) {
            continue;
        }

        if (line == "exit") {
            return;
        }

        auto commands = parser->parse(line);
        for (auto& command : commands) {
            executor->execute(*command);
        }
    }
}

std::string Shell::readInput() {
    std::string input;
    std::getline(std::cin, input);
    return input;
}

void Shell::displayPrompt() {
    std::cout << Shell::PROMPT_TITLE << "> " << std::flush;
}
