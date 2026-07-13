#include "minishell.h"

void    cmd_error(t_exec *exec)
{
    printf("minishell: %s: command not found\n", (*exec->cmd)->args[0]);
    exec->status = 127;
    close_files(exec);
    if(exec->old_fd != -1)
        close(exec->old_fd);
    free_all(exec);
    exit(127);
}

void    close_files(t_exec *exec)
{
    close(exec->fd[0]);
    close(exec->fd[1]);
    if((*exec->cmd)->heredoc)
    {
        close(exec->heredoc_fd[0]);
        close(exec->heredoc_fd[1]);
    }
}
void    close_saved_files(t_exec *exec)
{
    close(exec->saved_stdin);
    close(exec->saved_stdout);
}

void    dup_and_close(t_exec *exec)
{
    execute_builtins(exec);
    dup2(exec->saved_stdout, STDOUT_FILENO);
    dup2(exec->saved_stdin, STDIN_FILENO);
    close_saved_files(exec);
    if((*exec->cmd)->infile || (*exec->cmd)->outfile)
        close(exec->redir_fd);
}
