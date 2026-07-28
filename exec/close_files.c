#include "minishell.h"

void    create_saved_files(t_exec *exec)
{
    exec->saved_stdout = dup(STDOUT_FILENO);
    exec->saved_stdin = dup(STDIN_FILENO);
}

void    close_exec_pipe(t_exec *exec)
{
    if (found_heredocs(exec) == 0)
	{
        close(exec->heredoc_fd[0]);
        exec->heredoc_fd[0] = -1;
    }
	if (!exec->tmp->next_cmd)
		close(exec->fd[0]);
}

void	close_files(t_exec *exec)
{
    if(exec->fd[0] != -1)
        close(exec->fd[0]);
    if(exec->fd[1] != -1)
        close(exec->fd[1]);
    if(exec->tmp->heredoc && exec->heredoc_fd[0] != -1)
        close(exec->heredoc_fd[0]);
}
void	close_saved_files(t_exec *exec)
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
}