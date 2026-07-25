/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azenk <azenk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/25 17:48:19 by azenk             #+#    #+#             */
/*   Updated: 2026/07/25 17:48:20 by azenk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredocs(t_exec *exec)
{
	char	*line;

	if (exec->tmp->heredoc)
	{
		pipe(exec->heredoc_fd);
		while (1)
		{
			line = readline(">");
			if (!line)
			{
				free(line);
				break ;
			}
			if (ft_strcmp(line, exec->tmp->heredoc) == 0)
			{
				free(line);
				break ;
			}
			write(exec->heredoc_fd[1], line, ft_strlen(line));
			write(exec->heredoc_fd[1], "\n", 1);
			free(line);
		}
		close(exec->heredoc_fd[1]);
	}
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
}
