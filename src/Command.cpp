#include "Command.hpp"

#include <string>
#include <utility>
#include <vector>

Command::Command(std::string name, std::vector<std::string> args) {
  this->name = std::move(name);
  this->args = std::move(args);
}
