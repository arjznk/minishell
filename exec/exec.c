/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rijebbar <rijebbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/25 17:48:46 by azenk             #+#    #+#             */
/*   Updated: 2026/08/01 20:00:35 by rijebbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_pipe(t_exec *exec)
{
	exec->old_fd = -1;
	exec->status = 0;
	exec->saved_stdin = -1;
	exec->saved_stdout = -1;
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
			builtins_exec(exec);
		else
			fork_pipe(exec);
		if (exec->old_fd != -1)
			close(exec->old_fd);
		// if (exec->tmp->heredoc && exec->tmp->args)
    	// 	exec->old_fd = exec->heredoc_fd;
		// else
    		exec->old_fd = exec->fd[0];
		if(exec->fd[1] != -1)
			close(exec->fd[1]);
		exec->tmp = exec->tmp->next_cmd;
	}
	if (exec->old_fd != -1)
		close(exec->old_fd);
	signal_exec(exec);
}

int	redir_pipe(t_exec *exec)
{
	t_path_acces	*tmp;

	tmp = (*exec->acces_path);
	if (!tmp)
		return (1);
	dup_for_pipe(exec);
	exec_cmd(exec, tmp);
	return (0);
}

void	exec_cmd(t_exec *exec, t_path_acces *tmp)
{
	if (ft_strchr(exec->tmp->args[0], '/'))
	{
		if (access(exec->tmp->args[0], F_OK) == 0)
			execve(exec->tmp->args[0], exec->tmp->args, exec->envp);
		else
		{
			cmd_error(exec);
			return ;
		}
	}
	else
		cmd_only(exec, tmp);
}

void	cmd_only(t_exec *exec, t_path_acces *tmp)
{
	char	*line;
	char	*tmp_line;

	if (exec->tmp->args[0][0] == '\0')
		cmd_error(exec);
	while (tmp->acces)
	{
		tmp_line = ft_strjoin(tmp->acces, "/");
		line = ft_strjoin(tmp_line, exec->tmp->args[0]);
		free(tmp_line);
		if (access(line, F_OK) == 0)
			execve(line, exec->tmp->args, exec->envp);
		else if (tmp->next == NULL)
		{
			if (access(line, F_OK) != 0)
			{
				free(line);
				cmd_error(exec);
				return ;
			}
		}
		else
			tmp = tmp->next;
		free(line);
	}
}
