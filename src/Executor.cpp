/**
 * @file Executor.cpp
 * @brief File implemets Executor class
 *
 * Executor is responsible for executing a command. The main funciton is execute() which then does all the
 * work. It decides if the command is built-in or external. In case of built-in, the corresponding member
 * function is called, otherwise an external executable is called by a child process.
 *
 * @author Sukhanov Ivan
 * @date 25/5/2025
 * @version 1.0
 */
#include "Executor.hpp"

#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <algorithm>
#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <stdexcept>
#include <utility>
#include <vector>

#include "Command.hpp"

/// @brief Constructs an Executor and registers the SIGCHLD signal handler to reap exited children.
Executor::Executor() {
    registerSignalHangler();
}

/**
 * @brief Executes a command, dispatching to either a builtin or external handler.
 * @param cmd The command to execute.
 */
void Executor::execute(Command& cmd) {
    if (isBuiltin(cmd)) {
        executeBuiltin(cmd);
    } else {
        executeExternal(cmd);
    }
}

/**
 * @brief Checks if a command is a builtin command.
 * @param cmd The command to check.
 * @return true if the command is builtin, false otherwise.
 */
bool Executor::isBuiltin(const Command& cmd) {
    return builtinCommands.find(cmd.getName()) != end(builtinCommands);
}

/**
 * @brief Executes a builtin command.
 * @param cmd The builtin command to execute.
 * @throws std::invalid_argument if the command is not a known builtin.
 */
void Executor::executeBuiltin(const Command& cmd) {
    auto builtin = builtinCommands.find(cmd.getName());
    if (builtin != end(builtinCommands)) {
        BuiltinFunction function = builtin->second;
        const std::vector<std::string>& args = cmd.getArgs();
        (this->*function)(args);
    } else {
        throw std::invalid_argument("unknown builtin command");
    }
}

/**
 * @brief Executes an external command by forking and exec'ing.
 * @param cmd The external command to execute.
 * @throws std::runtime_error if fork fails.
 */
void Executor::executeExternal(const Command& cmd) {
    using namespace std;

    pid_t pid = fork();

    if (pid == 0) {
        // child actions

        // transforming args to c-like style (char**)
        string executableName = lookupPath(cmd.getName());
        vector<string> commandArgs(cmd.getArgs());

        vector<char*> executableArgs;
        executableArgs.reserve(commandArgs.size() + 2);

        executableArgs.push_back(const_cast<char*>(executableName.c_str()));
        for (const string& arg : commandArgs) {
            executableArgs.push_back(const_cast<char*>(arg.c_str()));
        }
        executableArgs.push_back(nullptr);  // null terminator

        // handling redirect
        handleRedirect(cmd);

        // executing the command
        execv(executableName.c_str(), executableArgs.data());

        // if this code was reached, exec failed -> error
        std::perror("error executing the command");
        _exit(1);
    } else if (pid > 0) {
        // parent actions

        // we do not wait for child if the process is run in background
        if (cmd.isParallel()) {
            std::cout << "[" << cmd.getName() << "]"
                      << "[" << pid << "]"
                      << " pushed to background" << endl;
            return;
        }

        // otherwise wait
        waitpid(pid, nullptr, 0);

    } else {
        // if fork did not succeed
        throw runtime_error("fork: "s + strerror(errno));
    }
}

/**
 * @brief Handles output redirection for a command.
 * @param cmd The command whose output should be redirected.
 */
void Executor::handleRedirect(const Command& cmd) {
    if (const std::string& file = cmd.getOutputRedirect().value_or(""); !file.empty()) {
        const int permissions = 0644;
        const int fileDescriptior = open(file.c_str(), O_WRONLY | O_CREAT | O_TRUNC, permissions);

        if (fileDescriptior == -1 || dup2(fileDescriptior, STDOUT_FILENO) == -1 ||
            dup2(fileDescriptior, STDERR_FILENO) == -1) {
            perror("file redirection failed");
        } else {
            close(fileDescriptior);
        }
    }
}

/**
 * @brief Registers the SIGCHLD signal handler to reap child processes.
 */
void Executor::registerSignalHangler() {
    struct sigaction signalAction {};
    signalAction.sa_handler = reapChildren;
    sigemptyset(&signalAction.sa_mask);
    signalAction.sa_flags = SA_RESTART | SA_NOCLDSTOP;

    if (sigaction(SIGCHLD, &signalAction, nullptr) == -1) {
        perror("sigactoi");
    }
}

/**
 * @brief Signal handler to reap terminated child processes.
 * @param signum The signal number (unused).
 */
void Executor::reapChildren(int signum) {
    pid_t currPid;
    while ((currPid = waitpid(-1, nullptr, WNOHANG)) > 0) {
        std::string str = "Reaped chiled with pid: " + std::to_string(currPid) + "\n";
        str.shrink_to_fit();
        char* buf = str.data();
        size_t length = str.length();
        write(STDOUT_FILENO, buf, length * sizeof(char));
    }
}

/**
 * @brief Map of builtin command names to their corresponding member function pointers.
 */
const std::unordered_map<std::string_view, Executor::BuiltinFunction> Executor::builtinCommands = {
    {"cd", &Executor::cd},
    {"exit", &Executor::exit},
    {"path", &Executor::path},
};

/**
 * @brief Changes the current working directory.
 * @param cmd Arguments for the cd command (expects exactly one argument).
 */
void Executor::cd(const Args& cmd) {
    if (cmd.size() != 1) {
        std::cerr << "cd: wrong number of arguments\n";
        return;
    }

    if (chdir(cmd[0].c_str()) != 0) {
        std::perror("cd");
    }
}

/**
 * @brief Sets the executable search path.
 * @param cmd Arguments for the path command (list of absolute paths).
 */
void Executor::path(const Args& cmd) {
    if (cmd.empty()) {
        searchPath.clear();
        return;
    }

    for (int i = 0; i < cmd.size(); i++) {
        const std::string& path = cmd[i];

        if (path.empty() || path.front() != '/' || path.back() == '/') {
            std::cerr << "path: invalid path at " << i << " position (ignored)\n";
            continue;
        }

        searchPath.push_back(path);
    }
}

/**
 * @brief Exits the shell.
 * @param cmd Arguments for the exit command (expects none), is needed only to satisfy the function pointer in
 * the map.
 */
void Executor::exit(const Args& cmd) {
    if (!cmd.empty()) {
        std::cerr << "exit: wrong number of arguments\n";
        return;
    }

    std::cout << "Exiting...\n" << std::flush;
    std::exit(0);
}

/**
 * @brief Looks up the full path of an executable in the search path.
 * @param cmd The command name to look up.
 * @return The full path to the executable if found, otherwise returns the command name.
 */
std::string Executor::lookupPath(const std::string& cmd) const {
    for (const auto& path : searchPath) {
        std::string fullPath = path + "/" + cmd;
        if (access(fullPath.c_str(), X_OK) == 0) {
            return fullPath;
        }
    }
    return cmd;
}
