# Custom Shell

A mimal UNIX-like shell implementation. Can be executed and used like a regular shell,
in interactive mode, or in a batch mode, runing commands from it.

For kernel interaction unix syscalls are used (fork(), exec(), chdir(), etc.).

## Features

- Execute external commands (`ls`, `echo`, etc.)
- Input/output redirection using `>` and `<`
- Background process execution with `&`
- Built-in commands (e.g., `cd`, `exit`)
- Zombie process reaping via signal handling (`SIGCHLD`)
- Prompt customization
- Command parsing with support for quotes

## How to build/run

Being in the source folder, run:

```sh
make build
```

To build the project

```sh
make run
```

To run the shell in interactive mode

```sh
make run-batch
```

To run the shell in batch mode. Defautl name for the file is `batch.txt`

To specify different namme run:

```sh
make run-batch BATCH_FILE=filename
```

Additionally, you can cusomize the executable name and shell prompt:

```sh
make run EXECUTABLE_NAME=executable_name
```
