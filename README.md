*This project has been created as part of the 42 curriculum by mmittelb, jnieders.*

# minishell -- manushell & minijonas
## Description

minishell is a simplified Unix shell written in C. The goal of the project is to understand and reimplement core shell behaviors: reading and parsing user input, handling quotes, expanding environment variables, managing redirections and pipes, executing builtins and external commands, and reacting to signals like a real interactive shell.The implementation is closely inspired by bash behavior, which was used as the reference where the subject leaves room for interpretation.

**At a high level, minishell provides the following features:**

- Displays an interactive prompt and maintains a command history
- Parses commands and operators (pipes and redirections; optionally &&, ||, parentheses)
- Expands environment variables (including $?)
- Executes builtins in the correct process context (parent vs child) when required
- Launches external programs via PATH lookup
- Implements bash-like interactive signal behavior (ctrl-C, ctrl-D, ctrl-\)
<br>

## Mandatory Features

- Prompt + history (readline)
- PATH resolution + execve
- Quotes: '...' prevents interpretation, "..." allows $ expansion
- Redirections: <, >, >>, << (heredoc)
- Pipes: |
- Environment variables: $VAR and $?
- Signals (interactive behavior like bash)

### Builtins:

- echo (with -n)
- cd
- pwd
- export
- unset
- env
- exit
<br>

## Bonus Features

- && and ||
- Parentheses for priorities (...)
- Wildcards * in the current working directory
<br>

## Memory management (GC)
The project uses a custom garbage collection mechanism to manage dynamic memory allocations.  
All allocations are tracked centrally and freed at well-defined points in the program lifecycle, which simplifies error handling and prevents memory leaks across complex execution paths (parsing, execution, heredocs, and signal handling).  
The environment (env) linked list is intentionally excluded from the GC system, as it must persist across multiple `readline` cycles and remain available for the entire lifetime of the shell.

<br>

## Abstract Syntax Tree (AST) parsing

Parsing is implemented as a recursive AST builder that follows shell operator precedence.  
The input is trimmed and checked for an outer parenthesized expression; in that case a `NODE_GROUP` is created and the inner expression is parsed recursively.

If no single outer group exists, the parser searches operators in precedence order, splitting the line into left/right substrings and building nodes recursively: first `||` / `&&` (`NODE_OR` / `NODE_AND`), then pipelines `|` (`NODE_PIPE`).  
When no operator is found, a `NODE_COMMAND` is created: redirections are extracted first, then the remaining command is split into `argv` while respecting quotes.

We explicitly mention the AST because it is the structural backbone of the project: it turns raw input into an executable representation and enables the separation of parsing and execution across operators, grouping, pipes, and redirections.


<br>

## Instructions

**A Unix-like environment (Linux or macOS) is required to build and run this project.**
- `make`
- A *"C"* compiler (`cc`, `clang`, or `gcc`)
- Readline development headers (depending on your setup)
<br>

### Build
Compile the project with:
```bash
make
```
Optional build targets:
```bash
make clean
make fclean
make re
```

### Run
```bash
./minishell
```

### Usage examples
```bash
minishell$ echo "Hello world"

minishell$ echo "$HOME"

minishell$ export TEST=42

minishell$ echo $TEST

minishell$ cat < infile | grep hello > outfile

minishell$ cat << EOF
heredoc line 1
EOF
```

### Notes on behavior

- **ctrl-D** exits minishell (EOF on input).
- **ctrl-C** interrupts the current input/command and shows a fresh prompt on a new line.
- **ctrl-\\** does nothing in interactive mode (bash-like).
<br>

## Project structure

```text
.
├── Makefile
├── include/
│   ├── minishell.h
│   ├── parse.h
│   ├── exec.h
│   ├── env.h
│   ├── expansions.h
│   ├── gc.h
│   └── utils.h
└── src/
    ├── main.c
    ├── parser/
    │   ├── parse.c
    │   ├── parse_helpers.c
    │   ├── handle_missing_token.c
    │   ├── redirections/
    │   └── expansions/
    ├── exec/
    │   ├── exec.c
    │   ├── exec_cmd.c
    │   ├── exec_pipe.c
    │   ├── exec_redir.c
    │   ├── collect_heredocs.c
    │   ├── exec_heredoc.c
    │   └── builtins/
    ├── env/
    ├── gc/
    ├── libft/
    ├── error_handling/
    └── utils/
```
<br>

### Resources
The following resources were used as primary references throughout the development of this project:

- **Bash manual and reference documentation**, used as the main behavioral reference whenever the subject left room for interpretation.
- **POSIX Shell Command Language specification**, consulted to align parsing and execution logic with standard shell semantics.
- **UNIX manual pages**, in particular:
  `readline`, `fork`,  `waitpid`, `pipe`, `dup`, `dup2`, `execve`,
  `signal`, `exit`, `open`, `close`, `read`, `write`, `access`,
  `chdir`, `getcwd`, `lstat`, `opendir`, `readdir`, `closedir`,
  `isatty`, `perror`, `strerror`

<br>

### Use of AI
AI tools were used as a **supporting resource** during the development of this project.  
They were primarily used to:
- clarify theoretical background and expected shell behavior,
- discuss edge cases and ambiguities in the subject,
- assist with documentation wording and structure.

AI was **not used to directly generate or copy complete implementations** of the project’s core logic. All code was written and integrated by the project authors.
