---

# Simple Shell

This project is a custom implementation of a simple Unix shell. The shell is designed to interpret and execute command lines both in interactive and non-interactive modes. It aims to replicate the behavior of the standard Unix shell, `/bin/sh`, with some basic functionality.

## Features

- **Interactive Mode**: The shell displays a prompt, waits for the user to enter a command, executes the command, and then displays the prompt again.
- **Non-Interactive Mode**: The shell reads and executes commands from standard input without displaying a prompt.
- **Built-in Commands**:
  - `exit`: Exits the shell.
  - `env`: Prints the current environment variables.
- **Handling of Simple Commands**: Executes simple commands like `/bin/ls` with or without arguments.
- **PATH Resolution**: Commands are searched in the directories listed in the `PATH` environment variable.
- **Error Handling**: Displays appropriate error messages if a command cannot be executed.

## Project Requirements

- **Compilation**: The shell is compiled using the following command:
  ```sh
  gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
  ```
- **Allowed Functions**:
  - `access`, `chdir`, `close`, `closedir`, `execve`, `exit`, `_exit`, `fflush`, `fork`, `free`, `getcwd`, `getline`, `getpid`, `isatty`, `kill`, `malloc`, `open`, `opendir`, `perror`, `read`, `readdir`, `signal`, `stat`, `lstat`, `fstat`, `strtok`, `wait`, `waitpid`, `wait3`, `wait4`, `write`
- **Memory Management**: The shell is designed to prevent memory leaks and ensures proper memory management.

## File Structure

- **`main.c`**: Entry point of the shell.
- **`shell.c`**: Contains the core logic for executing commands.
- **`builtins.c`**: Implements built-in shell commands like `exit` and `env`.
- **`path.c`**: Handles command path resolution using the `PATH` environment variable.
- **`error.c`**: Manages error handling and messaging.
- **`utils.c`**: Includes helper functions used across the shell.

## Usage

### Interactive Mode

Run the shell in interactive mode by simply executing the compiled binary:

```sh
./hsh
```

The shell will display a prompt (`$`), waiting for user input:

```sh
$ /bin/ls
file1  file2  file3
$
```

### Non-Interactive Mode

The shell can also execute commands from a file or input stream:

```sh
echo "/bin/ls" | ./hsh
```

### Exit the Shell

To exit the shell, use the `exit` command:

```sh
$ exit
```

## Environment

The shell handles the environment using the `env` built-in command:

```sh
$ env
PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin
HOME=/home/user
LOGNAME=user
```

