cmake_minimum_required(VERSION 3.16)

project(custom_shell LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(include)

add_executable(cshell
    src/main.cpp
    src/dummy.cpp
    src/Shell.cpp
    # src/Parser.cpp
    # src/Command.cpp
    src/Executor.cpp
)

# (Optional) Add test files
# add_executable(test_shell tests/test_shell.cpp)

