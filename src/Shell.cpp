#include "Shell.hpp"

#include <iostream>
#include <string>

Shell::Shell() = default;

void Shell::run() {
  using namespace std;

  while (true) {
    cout << "ishell> " << flush;

    string line;
    getline(cin, line);

    if (line.empty()) {
      continue;
    }

    if (line == "exit") {
      return;
    }

    cout << line << '\n';
  }
}
