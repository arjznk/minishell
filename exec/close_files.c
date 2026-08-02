#include "minishell.h"

void	create_saved_files(t_exec *exec)
{
	exec->saved_stdout = dup(STDOUT_FILENO);
	if (exec->saved_stdin_heredoc != -1)
		exec->saved_stdin = dup(exec->saved_stdin_heredoc);
	else
		exec->saved_stdin = dup(STDIN_FILENO);
}

void	dup_close_heredoc(t_exec *exec)
{
	if (exec->saved_stdin_heredoc != -1)
	{
		dup2(exec->saved_stdin_heredoc, STDIN_FILENO);
		close(exec->saved_stdin_heredoc);
		exec->saved_stdin_heredoc = -1;
	}
	if (exec->heredoc_fd != -1)
	{
		close(exec->heredoc_fd);
		exec->heredoc_fd = -1;
	}
}

void	close_files(t_exec *exec)
{
	if (exec->fd[0] != -1)
		close(exec->fd[0]);
	if (exec->fd[1] != -1)
		close(exec->fd[1]);
	if (exec->old_fd != -1)
	{
		close(exec->old_fd);
		exec->old_fd = -1;
	}
}

void	close_saved_files(t_exec *exec)
{
	if (exec->saved_stdin != -1)
	{
		close(exec->saved_stdin);
		exec->saved_stdin = -1;
	}
	if (exec->saved_stdout != -1)
	{
		close(exec->saved_stdout);
		exec->saved_stdout = -1;
	}
}

void	dup_and_close(t_exec *exec)
{
	execute_builtins(exec);
	dup2(exec->saved_stdout, STDOUT_FILENO);
	dup2(exec->saved_stdin, STDIN_FILENO);
	close_saved_files(exec);
}