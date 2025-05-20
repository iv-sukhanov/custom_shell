#include "Executor.hpp"

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <iostream>
#include <vector>

#include "Command.hpp"

Executor::Executor() = default;

void Executor::execute(Command &cmd) const {
    using namespace std;

    pid_t pid = fork();
    if (pid == 0) {
        string commandName = cmd.getName();
        vector<string> commandArgs(cmd.getArgs());

        vector<char *> execArgs;
        execArgs.reserve(commandArgs.size() + 2);

        execArgs.push_back(const_cast<char *>(commandName.c_str()));
        for (const string &arg : commandArgs) {
            execArgs.push_back(const_cast<char *>(arg.c_str()));
        }
        execArgs.push_back(nullptr);

        cout << "executing " << commandName << " with args: ";
        for (int i = 1; i < execArgs.size() - 1; i++) {
            cout << execArgs.at(i) << " ";
        }
        cout << '\n';
        execvp(cmd.getName().c_str(), execArgs.data());

        // TODO handle error
    } else if (pid > 0) {
        int status;
        waitpid(pid, &status, 0);
        // TODO handle statuses
        std::cout << pid << " parent, wait status: " << status << "\n";
    } else {
        std::cerr << "fork failed";
    }
}
