#include "Shell.hpp"

#include <iostream>
#include <string>

Shell::Shell() = default;

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

    cout << line << '\n';
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
