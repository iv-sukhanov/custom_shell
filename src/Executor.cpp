#include "Executor.hpp"

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <iostream>

Executor::Executor() = default;

void Executor::execute(Command& cmd) const {
  pid_t pid = fork();

  if (pid == 0) {
    std::cout << pid << " child" << '\n';
  } else if (pid > 0) {
    int status;
    waitpid(pid, &status, 0);
    std::cout << pid << " parent, wait status: " << status;
  } else {
    std::cerr << "fork failed";
  }
}
