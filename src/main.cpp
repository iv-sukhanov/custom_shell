/**
 * @file main.cpp
 * @brief Main entry point for the shell application
 * @author Sukhanov Ivan
 * @date 25/5/2025
 * @version 1.0
 */

#include <iostream>

#include "Shell.hpp"

/**
 * @brief Main function that initializes and runs the shell.
 * @param argc Argument count.
 * @param argv Argument vector containing command-line arguments.
 * @return int Exit status of the program.
 */
int main(int argc, char** argv) {
    Shell shell;

    if (argc == 1) {
        shell.run();
    } else if (argc == 2) {
        shell.run(argv[1]);
    } else {
        std::cout << "Incorrect usage.\n\tcorrect usage:\n\t'" << argv[0] << "' for interactive mode or '"
                  << argv[0] << " <filepath>' for batch mode" << std::endl;
    }

    return 0;
}
