#include "minishell.h"

void    cmd_error(t_exec *exec)
{
    printf("minishell: %s: command not found\n", (*exec->cmd)->args[0]);
    exec->status = 127;
    exit(127);
}

void    close_files(int fd[2])
{
    close(fd[0]);
    close(fd[1]);
}
