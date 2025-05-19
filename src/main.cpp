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
  Command test("ls", std::vector<std::string>{"-a"});
  exec.execute(test);

  return 0;
}
