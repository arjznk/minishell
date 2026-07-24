#include "minishell.h"

void	exec_pipe(t_exec *exec)
{
    exec->old_fd = -1;
    exec->status = -1;
    exec->tmp = (*exec->cmd);
    while(exec->tmp)
    {
        pipe(exec->fd);
        if(is_builtins(exec) == 0)
        {
            create_saved_files(exec);
            builtins_pipe(exec);
        }
        else
            fork_pipe(exec);
        if(exec->old_fd != -1)
            close(exec->old_fd);
        exec->old_fd = exec->fd[0];
        close(exec->fd[1]);
        if(found_heredocs(exec) == 0)
            close(exec->heredoc_fd[0]);
        if(!exec->tmp->next_cmd)
            close(exec->fd[0]);
        exec->tmp = exec->tmp->next_cmd; 
    }
    while(waitpid(-1, &exec->status, 0) > 0)
        exec->status = WEXITSTATUS(exec->status);
}

int    redir_pipe(t_exec *exec)
{
    t_path_acces *tmp;

    *exec->cmd = exec->tmp;
    tmp = (*exec->acces_path);
    if(!tmp)
        return (1);
    dup_for_pipe(exec);
    exec_cmd(exec, tmp);
    return (0);
}

void    exec_cmd(t_exec *exec, t_path_acces *tmp)
{
    if(!(exec->tmp->args))
    {
        close_files(exec);
        free_all(exec);
        close(STDOUT_FILENO);
        exit(0);
    }
    if(ft_strchr(exec->tmp->args[0], '/'))
    {
        if(access(exec->tmp->args[0], F_OK) == 0)
            execve(exec->tmp->args[0], exec->tmp->args, exec->envp);
        else
        {
            cmd_error(exec);
            return;
        }
    }
    else
        cmd_only(exec, tmp);
}

void    cmd_only(t_exec *exec, t_path_acces *tmp)
{
    char *line;
	char *tmp_line;

    while(tmp->acces)
    {
        tmp_line = ft_strjoin(tmp->acces, "/");
        line = ft_strjoin(tmp_line, exec->tmp->args[0]);
		free(tmp_line);
        if(access(line, F_OK) == 0)
            execve(line, exec->tmp->args, exec->envp);
        else if(tmp->next == NULL)
        {
            if(access(line, F_OK) != 0)
            {
				free(line);
                cmd_error(exec);
                return;
            }
        }
        else
            tmp = tmp->next;
		free(line);
    }
}

void    create_saved_files(t_exec *exec)
{
    exec->saved_stdout = dup(STDOUT_FILENO);
    exec->saved_stdin = dup(STDIN_FILENO);
}
void    builtins_pipe(t_exec *exec)
{
	if ((*exec->cmd)->heredoc)
		heredocs(exec);
	else if (found_outfile(exec) == 0)
	{
		if (redirections(exec) == 1)
		{
			close_saved_files(exec);
			return ;
		}
		dup2(exec->redir_fd, STDOUT_FILENO);
        close(exec->redir_fd);
	}
	else if (found_infile(exec) == 0)
	{
		if (redirections(exec) == 1)
		{
			close_saved_files(exec);
			return ;
		}
		dup2(exec->redir_fd, STDIN_FILENO);
	}
	else if (exec->tmp->next_cmd)
		dup2(exec->fd[1], STDOUT_FILENO);
	dup_and_close(exec);
}

void	fork_pipe(t_exec *exec)
{
    if(found_heredocs(exec) == 0)
        heredocs(exec);
    if(fork() == 0)
    {
        if (redir_pipe(exec) == 1)
        {
            printf("minishell: %s: no such file or directory\n", (*exec->cmd)->args[0]);
            exec->status = 127;
            close_files(exec);
			free_all(exec);
            exit(127);
        }
        else
            exit(0);
    }
}

void	dup_for_pipe(t_exec *exec)
{
	if ((*exec->cmd)->heredoc)
	{
		dup2(exec->heredoc_fd[0], STDIN_FILENO);
		exec->old_fd = exec->heredoc_fd[0];
	}
	else if (found_outfile(exec) == 0)
	{
		if (redirections(exec) == 1)
			return ;
		dup2(exec->redir_fd, STDOUT_FILENO);
        close(exec->redir_fd);
	}
	else if (found_infile(exec) == 0)
	{
		if (redirections(exec) == 1)
			return ;
		dup2(exec->redir_fd, STDIN_FILENO);
        close(exec->redir_fd);
	}
	if (exec->old_fd != -1)
		dup2(exec->old_fd, STDIN_FILENO);
	if (exec->tmp->next_cmd)
		dup2(exec->fd[1], STDOUT_FILENO);
}
