#pragma once

#include <optional>
#include <string>
#include <vector>

class Command {
 public:
  Command(std::string name, std::vector<std::string> args);
  std::string getName() const;
  std::vector<std::string> getArgs() const;

 private:
  std::string name;
  std::vector<std::string> args;
  std::optional<std::string> inputFile;
  std::optional<std::string> outputFile;
};
