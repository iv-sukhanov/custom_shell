#ifndef COMMAND
#define COMMAND

#include <optional>
#include <string>
#include <vector>

class Command {
 public:
  Command(std::string name, std::vector<std::string> args);

 private:
  std::string name;
  std::vector<std::string> args;
  std::optional<std::string> inputFile;
  std::optional<std::string> outputFile;
};

#endif  // !COMMAND
