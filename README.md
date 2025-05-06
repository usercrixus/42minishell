# 42minishell

A simple Unix shell implementation as part of the 42 school curriculum. This project replicates fundamental shell behavior including parsing, executing built-in and external commands, handling pipes, redirections, and more.

## Features

- Execution of simple and piped commands
- Built-in commands: `cd`, `echo`, `pwd`, `export`, `unset`, `env`, `exit`
- Redirections: `<`, `>`, `>>`, `<<` (heredoc)
- Environment variable management
- Signal handling (`Ctrl+C`, `Ctrl+\`)
- Exit status propagation
- Quote handling (single `'` and double `"`)

## Build Instructions

```bash
make
```

To clean build files:

```bash
make clean      # Removes object files
make fclean     # Removes all binaries and object files
make re         # Full rebuild
```

Run the Shell
```bash
./minishell
```

Run with the suppression file:
```
valgrind --leak-check=full --show-leak-kinds=all --suppressions=valgrind.supp ./minishell
```
