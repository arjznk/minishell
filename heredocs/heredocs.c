/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rijebbar <rijebbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/28 16:45:59 by azenk             #+#    #+#             */
/*   Updated: 2026/07/29 11:42:37 by rijebbar         ###   ########.fr       */
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
	while (i < exec->tmp->nb_heredoc)
	{
		loop_heredoc(exec, i);
		if (g_signal == SIGINT)
			break ;
		write(1, "aa\n", 2);
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
			write(1, "1\n", 2);
			free(line);
			exec->status = 130;
			return ;
		}
		if (!line)
		{
			write(1, "2\n", 2);
			free(line);
			printf("minishell: warning: here-document at line %d delimited by end-of-file (wanted `%s')\n", exec->count_line, exec->tmp->heredocs_delims[i]);
			break ;
		}
		if (ft_strcmp(line, exec->tmp->heredocs_delims[i]) == 0)
		{
			write(1, "3\n", 2);
			free(line);
			break ;
		}
		if (i == (exec->tmp->nb_heredoc - 1))
		{
			write(1, "4\n", 2);
			heredoc_write(exec, line);
			write(1, "5\n", 2);
		}
		else
		{
			write(1, "6\n", 2);
			free(line);
		}
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
