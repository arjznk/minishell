/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rijebbar <rijebbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/28 16:34:33 by azenk             #+#    #+#             */
/*   Updated: 2026/08/02 18:24:51 by rijebbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_saved_files(t_exec *exec)
{
	exec->saved_stdout = dup(STDOUT_FILENO);
	exec->saved_stdin = dup(STDIN_FILENO);
}

void	dup_close_heredoc(t_exec *exec)
{
	if (exec->saved_stdin_heredoc != -1)
	{
		dup2(exec->saved_stdin_heredoc, STDIN_FILENO);
			exec->saved_stdin_heredoc);
		close(exec->saved_stdin_heredoc);
		exec->saved_stdin_heredoc = -1;
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
	close(exec->saved_stdin);
	close(exec->saved_stdout);
}

void	dup_and_close(t_exec *exec)
{
	execute_builtins(exec);
	dup2(exec->saved_stdout, STDOUT_FILENO);
	dup2(exec->saved_stdin, STDIN_FILENO);
	close_saved_files(exec);
}
