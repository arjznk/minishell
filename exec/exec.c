#include "minishell.h"

void    init_pipe(t_exec *exec)
{
    exec->old_fd = -1;
	exec->status = 0;
    exec->saved_stdin = -1;
    exec->saved_stdout = -1;
    exec->heredoc_fd[0] = -1;
    exec->heredoc_fd[1] = -1;
    exec->tmp = *exec->cmd;
}

void	exec_pipe(t_exec *exec)
{
    init_pipe(exec);
	while (exec->tmp)
	{
		if (pipe(exec->fd) == -1)
		{
			exec->status = 1;
			return (perror("pipe"));
		}
		if (is_builtins(exec) == 0)
		{
			create_saved_files(exec);
			builtins_pipe(exec);
		}
		else
			fork_pipe(exec);
		if (exec->old_fd != -1)
			close(exec->old_fd);
		exec->old_fd = exec->fd[0];
		close(exec->fd[1]);
		close_exec_pipe(exec);
		exec->tmp = exec->tmp->next_cmd;
	}
	wait_children(exec);
	init_parent_signals();
} 

int    redir_pipe(t_exec *exec)
{
    t_path_acces *tmp;

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





