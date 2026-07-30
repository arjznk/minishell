/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rijebbar <rijebbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/28 16:45:59 by azenk             #+#    #+#             */
/*   Updated: 2026/07/30 12:46:42 by rijebbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredocs(t_exec *exec)
{
	int	i;

	i = 0;
	g_signal = 0;
	signal(SIGINT, handle_heredoc_sigint);
	signal(SIGQUIT, SIG_IGN);
	rl_event_hook = heredoc_event;
	pipe(exec->heredoc_fd);
	while (i < (*exec->cmd)->nb_heredoc)
	{
		loop_heredoc(exec, i);
		if (g_signal == SIGINT)
			break ;
		i++;
	}
	close(exec->heredoc_fd[1]);
	exec->heredoc_fd[1] = -1;
	rl_event_hook = NULL;
	init_parent_signals();
}

void	loop_heredoc(t_exec *exec, int i)
{
	char	*line;

	while (1)
	{
		line = readline(">");
		if (g_signal == SIGINT)
		{
			exec->status = 130;
			return (free(line));
		}
		if (!line)
		{
			heredoc_error(exec, i, line);
			break ;
		}
		if (ft_strcmp(line, (*exec->cmd)->heredocs_delims[i]) == 0)
		{
			free(line);
			break ;
		}
		if (i == ((*exec->cmd)->nb_heredoc - 1))
			heredoc_write(exec, line);
		else
			free(line);
	}
}

void	heredoc_write(t_exec *exec, char *line)
{
	write(exec->heredoc_fd[1], line, ft_strlen(line));
	write(exec->heredoc_fd[1], "\n", 1);
	free(line);
}

int	found_heredocs(t_exec *exec)
{
	if (exec->tmp->heredoc)
		return (0);
	return (1);
}

void	close_heredoc_files(t_exec *exec)
{
	close(exec->heredoc_fd[0]);
	exec->heredoc_fd[0] = -1;
}
