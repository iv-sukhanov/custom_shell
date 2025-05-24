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

Shell::Shell() {
    this->parser = std::make_unique<Parser>();
    this->executor = std::make_unique<Executor>();
};

const char* Shell::PROMPT_TITLE = "ishell";

void Shell::run() {
    using namespace std;

    while (true) {
        displayPrompt();
        const string& line = readInput();

        if (line.empty()) {
            continue;
        }

        handleInputLine(line);
    }
}

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
        cout << "1" << line << "1" << '\n';
        handleInputLine(line);
    }
}

void Shell::handleInputLine(const std::string& line) {
    using namespace std;

    vector<unique_ptr<Command>> commands;
    try {
        commands = parser->parse(line);
    } catch (exception& e) {
        cerr << "error: " << e.what();
        return;
    } catch (...) {
        cerr << "unknown exception";
        return;
    }

    for (const auto& command : commands) {
        try {
            executor->execute(*command);
        } catch (exception& e) {
            cerr << "error: " << e.what();
            continue;
        } catch (...) {
            cerr << "unknown exception";
            continue;
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
