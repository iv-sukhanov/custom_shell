#include "Executor.hpp"

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <cstdio>
#include <iostream>
#include <vector>

#include "Command.hpp"

Executor::Executor() = default;

void Executor::execute(Command &cmd) {
    if (isBuiltin(cmd)) {
        executeBuiltin(cmd);
    } else {
        executeExternal(cmd);
    }
}

bool Executor::isBuiltin(const Command &cmd) const {
    return builtinCommands.find(cmd.getName()) != end(builtinCommands);
}

void Executor::executeBuiltin(const Command &cmd) {
    auto builtin = builtinCommands.find(cmd.getName());
    if (builtin != end(builtinCommands)) {
        auto function = builtin->second;
        const auto args = cmd.getArgs();
        (this->*function)(args);
    } else {
        std::cerr << "Unknown builtin command: " << cmd.getName() << '\n';
    }
}

void Executor::executeExternal(const Command &cmd) const {
    using namespace std;

    pid_t pid = fork();
    if (pid == 0) {
        const string commandName = cmd.getName();
        vector<string> commandArgs(cmd.getArgs());

        vector<char *> execArgs;
        execArgs.reserve(commandArgs.size() + 2);

        execArgs.push_back(const_cast<char *>(commandName.c_str()));
        for (const string &arg : commandArgs) {
            execArgs.push_back(const_cast<char *>(arg.c_str()));
        }
        execArgs.push_back(nullptr);

        // debug
        cout << "executing " << commandName << " with args: ";
        for (int i = 1; i < execArgs.size() - 1; i++) {
            cout << execArgs.at(i) << " ";
        }
        cout << '\n';
        execv(cmd.getName().c_str(), execArgs.data());

        std::perror("error executing the command: ");
        _exit(1);
    } else if (pid > 0) {
        int status;
        waitpid(pid, &status, 0);
        // TODO handle statuses
        std::cout << pid << " parent, wait status: " << status << "\n";
    } else {
        std::perror("error creating a child process:");
    }
}

const std::unordered_map<std::string_view, Executor::BuiltinFunction> Executor::builtinCommands = {
    {"cd", &Executor::cd},
    {"exit", &Executor::exit},
    {"path", &Executor::path},
};

void Executor::cd(const Args &cmd) {
    if (cmd.size() != 1) {
        std::cerr << "cd: wrong number of arguments\n";
        return;
    }

    if (chdir(cmd[0].c_str()) != 0) {
        std::perror("cd");
    }
}

void Executor::exit(const Args &cmd) {
    if (!cmd.empty()) {
        std::cerr << "exit: wrong number of arguments\n";
        return;
    }

    std::cout << "Exiting...\n" << std::flush;
    std::exit(0);
}

void Executor::path(const Args &cmd) {
    // TODO
}
