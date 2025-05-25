cmake_minimum_required(VERSION 3.16)

project(custom_shell LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(EXECUTABLE_NAME "ishell" CACHE STRING "Name of the executable")

include_directories(include include/utils)

add_executable(
	${EXECUTABLE_NAME}
    src/main.cpp
    src/Shell.cpp
    src/Parser.cpp
    src/Command.cpp
    src/Executor.cpp
	src/utils/StringUtils.cpp
)


