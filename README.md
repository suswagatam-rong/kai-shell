
# Kai Shell

Kai Shell is a simple Unix shell implementation in C, offering basic command-line functionalities similar to popular Unix shells like Bash. It supports executing commands, built-in commands like `cd`, `help`, `exit`, and additional custom commands `hello` and `date`.

## Features

- **Basic Command Execution**: Run commands like in a typical shell.
- **Built-in Commands**: Includes `cd` (change directory), `help` (display help message), `exit` (terminate the shell), `hello` (custom greeting), and `date` (display current date and time).
- **Command Line Editing**: Basic line editing capabilities such as reading and splitting input into tokens.
- **Process Management**: Launch external programs and wait for them to terminate using `fork`, `execvp`, and `waitpid`.

## Acknowledgment

This project is based on the tutorial by Stephen Brennan on how to write a shell in C. The initial structure and concepts were adapted from the [LSH (Libstephen SHell) repository](https://github.com/brenns10/lsh) and the accompanying tutorial "[Write a Shell in C](https://brennan.io/2015/01/16/write-a-shell-in-c/)" by Stephen Brennan. Thank you, Stephen Brennan, for providing such a comprehensive resource!

## Getting Started

### Prerequisites

- GCC (GNU Compiler Collection) or another C compiler that supports C11.
- Linux or macOS environment (though it should work on other Unix-like systems as well).

### Building

1. Clone the repository:

   ```bash
   git clone https://github.com/suswagatam-rong/kai-shell.git
   cd kai-shell
   ```

2. Compile the project:

   ```bash
   gcc -o kai-shell main.c kai_shell.c
   ```

### Running the Shell

To start the Kai Shell, simply execute the compiled binary:

```bash
./kai-shell
```

You should see the shell prompt (`kai-shell>`), where you can enter commands and interact with the shell.

### Usage

#### Basic Commands

- **Executing Commands**: Enter any system command (e.g., `ls`, `pwd`).
- **Built-in Commands**:
  - `cd [directory]`: Change current directory.
  - `help`: Display list of available commands.
  - `exit`: Exit the shell.
  - `hello`: Print a welcome message.
  - `date`: Display current date and time.

#### Example

```
kai-shell> hello
Hello! Welcome to Kai's Custom Shell!

kai-shell> date
Current date and time: Mon Jun 17 12:34:56 2024

kai-shell> ls
Desktop  Documents  Downloads  Music  Pictures  Videos

kai-shell> cd Documents

kai-shell> pwd
/home/user/Documents
```

### Contributing

Contributions are welcome! Feel free to open issues for bugs, feature requests, or submit pull requests with improvements.

### License

This project is licensed under the Unlicense. See the [UNLICENSE](UNLICENSE) file for more details.

---