*This project has been created as part of the 42 curriculum by rijebbar, azenk*


### Description
- minishell is a small shell project made for the 42 curriculum.  
- Goal: implement a minimal POSIX-like shell that supports tokenization, parsing, redirections, pipes, builtins (cd, echo, pwd, export, unset, env, exit), heredocs, signals, and command execution via execve.  
- This repo contains our student implementation.

### Instructions
- Requirements: gcc, make, and the usual Unix development environment.
- Quick compile:
- run: make
- This builds the minishell binary in the project root (or as specified by your Makefile).
- Run:
- ./minishell
- Use the prompt: run commands as you would in a normal shell. Example: ls -la | grep foo > out.txt
- Notes:
- We use readline for the prompt. If readline is missing, adjust the Makefile or install the library.
- To quit: type exit or press Ctrl-D.


How to test :
- Start the shell and run a few builtin and external commands.
- Try multiple pipes, redirections, and heredocs.
- Use valgrind to check for leaks/fd leaks when running commands that create temporary files / heredocs:
- valgrind --leak-check=full --track-fds=yes ./minishell


### Resources
- POSIX and shell references:
- POSIX specification (sh): https://pubs.opengroup.org/onlinepubs/9699919799/
- GNU bash manual: https://www.gnu.org/software/bash/manual/
- readme/rl documentation: readline manual pages
- Tutorials / help we consulted:
- Various online articles about implementing a shell in C (search terms: "implementing a shell in C", "heredoc in C", "dup2 pipe execve example")


