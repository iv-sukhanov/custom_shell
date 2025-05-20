#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

#include "Command.hpp"
#include "Executor.hpp"
#include "Parser.hpp"
#include "Shell.hpp"

int main() {
    Shell shell;
    shell.run();

    return 0;
}
