/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rijebbar <rijebbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/28 16:45:59 by azenk             #+#    #+#             */
/*   Updated: 2026/08/02 18:19:06 by rijebbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	save_heredoc(t_exec *exec)
{
	exec->saved = "/tmp/heredoc";
	exec->heredoc_fd = open(exec->saved, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (exec->heredoc_fd == -1)
	{
		strerror(errno);
		return (1);
	}
	return (0);
}

void	heredocs(t_exec *exec)
{
	int	i;

	i = 0;
	g_signal = 0;

	signal(SIGINT, handle_heredoc_sigint);
	signal(SIGQUIT, SIG_IGN);
	rl_event_hook = heredoc_event;
	while (i < (*exec->cmd)->nb_heredoc)
	{
		loop_heredoc(exec, i);
		if (g_signal == SIGINT)
			break ;
		i++;
	}
	close(exec->heredoc_fd);
	exec->saved_stdin_heredoc = dup(STDIN_FILENO);
	exec->heredoc_fd = open(exec->saved, O_RDONLY, 0644);
	dup2(exec->heredoc_fd, STDIN_FILENO);
	close(exec->heredoc_fd);
	unlink(exec->saved);
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
	t_env	*tmp;
	char	*temp;

	tmp = (*exec->env);
	if (line[0] == '$')
	{
		while (tmp)
		{
			temp = ft_strchr(line, '$');
			if (!temp)
				break ;
			if (ft_strcmp(temp, tmp->variable) == 0)
			{
				line = get_env_value(temp, tmp);
				break ;
			}
			tmp = tmp->next;
		}
	}
	write(exec->heredoc_fd, line, ft_strlen(line));
	write(exec->heredoc_fd, "\n", 1);
	free(line);
}
int	found_heredocs(t_exec *exec)
{
	t_cmd	*tmp;

	tmp = *exec->cmd;
	while (tmp)
	{
		if (tmp->heredoc || tmp->heredocs_delims)
			return (0);
		tmp = tmp->next_cmd;
	}
	return (1);
}
