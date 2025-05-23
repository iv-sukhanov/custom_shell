#include "Command.hpp"

#include <string>
#include <utility>
#include <vector>

Command::Command(std::string name, std::vector<std::string> args) {
    this->name = std::move(name);
    this->args = std::move(args);
}

std::string Command::getName() const {
    return this->name;
}

std::vector<std::string> Command::getArgs() const {
    return this->args;
}

void Command::setOutputRedirect(const std::string &file) {
    this->outputFile = file;
}

std::optional<std::string> Command::getOutputRedirect() const {
    return this->outputFile;
}

std::optional<std::string> Command::getInputRedirect() const {
    return this->inputFile;
}

void Command::setParallel(bool inParallel) {
    this->inParallel = inParallel;
}

bool Command::isParallel() const {
    return this->inParallel;
}
