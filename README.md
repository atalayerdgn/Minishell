# Minishell

Minishell is a simple, interactive shell implementation that replicates essential functionality of Bash. It supports common shell features, built-in commands, signal handling, and input/output redirection.

---

## Features

### General Features
- **Prompt**: Displays a customizable prompt while waiting for user input.
- **History**: Maintains a history of executed commands.
- **Executable Search**: Locates executables using the `PATH` environment variable or via relative and absolute paths.
- **Signal Handling**: Uses a single global variable to indicate received signals, without providing additional data access.

### Input Parsing
- **Quotes**:
  - Single quotes (`'`): Prevent interpretation of metacharacters within the quoted sequence.
  - Double quotes (`"`): Prevent interpretation of metacharacters except for the dollar sign (`$`).
- **Special Characters**:
  - Unclosed quotes and unsupported characters (e.g., `\` and `;`) are ignored.

### Redirections
- `<`: Redirects input.
- `>`: Redirects output (overwrites the file).
- `>>`: Redirects output in append mode.
- `<<`: Reads input until a line containing a specified delimiter is encountered (does not update history).

### Pipes
- Supports pipelines using the `|` character. The output of each command is connected to the input of the next.

### Environment Variables
- Expands variables prefixed with `$` (e.g., `$HOME`).
- Supports `\$?` to expand to the exit status of the last executed command.

### Built-in Commands
- **echo**: Prints text to the standard output, with support for the `-n` option to omit the trailing newline.
- **cd**: Changes the current directory to a relative or absolute path.
- **pwd**: Prints the current working directory.
- **export**: Sets environment variables.
- **unset**: Unsets environment variables.
- **env**: Displays the current environment variables.
- **exit**: Exits the shell.

### Signal Handling
- **Ctrl-C**: Interrupts the current command and displays a new prompt.
- **Ctrl-D**: Exits the shell.
- **Ctrl-\**: Does nothing in interactive mode.

---

## Interactive Mode
- Provides a responsive command line interface.
- Handles signals as follows:
  - `Ctrl-C`: Clears the current input and displays a new prompt.
  - `Ctrl-D`: Exits the shell.
  - `Ctrl-\`: Ignored.

---

## Requirements
- Avoids the use of more than one global variable for signal handling.
- Prohibits the use of "norm" type structures in the global scope.

---

## Compilation
To compile Minishell, run the following command in the project directory:

```bash
make
```

This will generate the `minishell` executable.

---

## Usage
Start Minishell by running:

```bash
./minishell
```

The shell will display a prompt where you can execute commands.

---

## Examples
### Executing Commands
```bash
ls -l
```

### Using Pipes
```bash
ls -l | grep minishell
```

### Redirecting Output
```bash
echo "Hello, World!" > output.txt
```

### Environment Variables
```bash
echo $HOME
```

### Built-in Commands
```bash
pwd
cd /path/to/directory
echo "Minishell is awesome!"
exit
```

---
