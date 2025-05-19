#include "Command.hpp"

#include <string>
#include <utility>
#include <vector>

Command::Command(std::string name, std::vector<std::string> args) {
  this->name = std::move(name);
  this->args = std::move(args);
}

std::string Command::getName() const { return this->name; }

std::vector<std::string> Command::getArgs() const { return this->args; }
