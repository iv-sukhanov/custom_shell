#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

#include "Command.hpp"
#include "Executor.hpp"
#include "Parser.hpp"
#include "Shell.hpp"

int main(int argc, char** argv) {
    Shell shell;

    if (argc == 1) {
        shell.run();
    } else if (argc == 2) {
        shell.run(argv[1]);
    } else {
        std::cout
            << "Incorrect usage.\n\tcorrect usage:\n\t'ishell' for interactive mode or 'ishell <filepath>' "
               "for batch mode";
    }

    return 0;
}
