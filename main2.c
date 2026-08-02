/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rijebbar <rijebbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 16:38:34 by rijebbar          #+#    #+#             */
/*   Updated: 2026/08/02 20:52:25 by rijebbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	readline_loop(t_exec *exec)
{
	char	*line;

	line = readline("minishell> ");
	if (!line)
	{
		printf("exit\n");
		free_all(exec);
		return (1);
	}
	exec->count_line++;
	if (line)
		add_history(line);
	exec->line = line;
	return (0);
}

int	heredoc_main(t_exec *exec)
{
	if (found_heredocs(exec) == 0)
	{
		if (save_heredoc(exec) == 0)
		{
			heredocs(exec);
			if (g_signal == SIGINT)
				return (0);
		}
		else
			return (1);
	}
	return (0);
}

void	init_for_exec(t_exec *exec)
{
	exec->saved_stdin_heredoc = -1;
	exec->saved_stdin = -1;
	exec->saved_stdout = -1;
	exec->heredoc_fd = -1;
	exec->fd[0] = -1;
	exec->fd[1] = -1;
	exec->old_fd = -1;
	exec->redir_fd = -1;
}

void	exec_saved_std(t_exec *exec)
{
	if (exec->saved_stdin_heredoc != -1)
		dup_close_heredoc(exec);
}

void	exec_heredoc_tmp(t_exec *exec)
{
	exec->tmp = *exec->cmd;
	init_heredocs(exec);
}
