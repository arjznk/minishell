/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rijebbar <rijebbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/28 16:29:35 by azenk             #+#    #+#             */
/*   Updated: 2026/08/01 19:26:07 by rijebbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fork_pipe(t_exec *exec)
{
	if (!(exec->tmp->args))
	{
		close_files(exec);
		return ;
	}
	ignore_parent_signals();
	exec->pid = fork();
	if (exec->pid == -1)
	{
		exec->status = 1;
		return (perror("fork"));
	}
	if (exec->pid == 0)
	{
		init_child_signals();
		if (redir_pipe(exec) == 1)
		{
			return_fork_pipe(exec);
			exit(127);
		}
	}
}

void	return_fork_pipe(t_exec *exec)
{
	char	*line;
	char	*tmp;

	if (exec->tmp && exec->tmp->args && exec->tmp->args[0])
	{
		tmp = ft_strjoin("minishell: ", exec->tmp->args[0]);
		line = ft_strjoin(tmp, ": no such file or directory\n");
		free(tmp);
		write(2, line, ft_strlen(line));
		free(line);
		exec->status = 127;
	}
	close_files(exec);
	free_all(exec);
}

void	dup_for_pipe(t_exec *exec)
{
	if (found_outfile(exec) == 0)
	{
		if (redirections(exec) == 1)
			exit(1);
		dup2(exec->redir_fd, STDOUT_FILENO);
		close(exec->redir_fd);
	}
	else if (found_infile(exec) == 0)
	{
		if (redirections(exec) == 1)
			exit(1);
		dup2(exec->redir_fd, STDIN_FILENO);
		close(exec->redir_fd);
	}
	if (exec->old_fd != -1)
	{
		if (dup2(exec->old_fd, STDIN_FILENO) == -1)
			exit(1);
	}
	if (exec->tmp->next_cmd)
		dup2(exec->fd[1], STDOUT_FILENO);
}

void	builtins_pipe(t_exec *exec)
{
	if (found_outfile(exec) == 0)
	{
		if (redirections(exec) == 1)
			return (close_saved_files(exec));
		dup2(exec->redir_fd, STDOUT_FILENO);
		close(exec->redir_fd);
	}
	else if (found_infile(exec) == 0)
	{
		if (redirections(exec) == 1)
			return ((close_saved_files(exec)));
		dup2(exec->redir_fd, STDIN_FILENO);
	}
	else if (exec->tmp->next_cmd)
		dup2(exec->fd[1], STDOUT_FILENO);
	dup_and_close(exec);
}
