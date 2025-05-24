#include "Command.hpp"

#include <string>
#include <utility>
#include <vector>

Command::Command(const std::string& name, const std::vector<std::string>& args) {
    this->name = name;
    this->args = args;
}

std::string Command::getName() const {
    return this->name;
}

std::vector<std::string> Command::getArgs() const {
    return this->args;
}

void Command::setOutputRedirect(const std::string& file) {
    this->outputFile = file;
}

std::optional<std::string> Command::getOutputRedirect() const {
    return this->outputFile;
}

void Command::setParallel(bool inParallel) {
    this->inParallel = inParallel;
}

bool Command::isParallel() const {
    return this->inParallel;
}
