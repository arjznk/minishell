/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rijebbar <rijebbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 16:38:34 by rijebbar          #+#    #+#             */
/*   Updated: 2026/07/31 15:19:40 by rijebbar         ###   ########.fr       */
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

int 	heredoc_main(t_exec *exec)
{
	if (found_heredocs(exec) == 0)
	{
		if(save_heredoc(exec) == 0)
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