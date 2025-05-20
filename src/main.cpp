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
    // Shell shell;
    // shell.run();
    //
    // Executor exec;
    // Command test("ls", std::vector<std::string>{"-a"});
    // exec.execute(test);

    Parser parser;
    std::string line = "ls  -la ./temp  	 >  \n  ./somewhere";
    auto commands = parser.parse(line);
    auto firstCommand = (*commands.front()).getArgs();

    return 0;
}
