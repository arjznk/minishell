/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rijebbar <rijebbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/28 16:29:35 by azenk             #+#    #+#             */
/*   Updated: 2026/07/28 18:00:23 by rijebbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fork_pipe(t_exec *exec)
{
	pid_t	pid;

	if (found_heredocs(exec) == 0)
	{
		heredocs(exec);
		if (g_signal == SIGINT)
			return ;
	}
	ignore_parent_signals();
	pid = fork();
	if (pid == -1)
	{
		exec->status = 1;
		return (perror("fork"));
	}
	if (pid == 0)
	{
		init_child_signals();
		if (redir_pipe(exec) == 1)
		{
			ft_putstr_fd("minishell: ", 2);
			if (exec->tmp && exec->tmp->args && exec->tmp->args[0])
				ft_putstr_fd(exec->tmp->args[0], 2);
			ft_putendl_fd(": no such file or directory", 2);
			close_files(exec);
			free_all(exec);
			exit(127);
		}
	}
}

void	dup_for_pipe(t_exec *exec)
{
	if (exec->tmp->heredoc)
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


void	builtins_pipe(t_exec *exec)
{
	if ((*exec->cmd)->heredoc)
	{
		heredocs(exec);
		if (g_signal == SIGINT)
			return ;
	}
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
			return ((close_saved_files(exec)));
		dup2(exec->redir_fd, STDIN_FILENO);
	}
	else if (exec->tmp->next_cmd)
		dup2(exec->fd[1], STDOUT_FILENO);
	dup_and_close(exec);
}
