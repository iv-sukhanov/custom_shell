#include <iostream>
#include <string>
#include <vector>

#include "Command.hpp"
#include "Executor.hpp"
#include "Shell.hpp"

int main() {
  Shell shell;
  shell.run();

  Executor exec;
  Command test("test", std::vector<std::string>{});
  exec.execute(test);

  return 0;
}
