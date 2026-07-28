/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azenk <azenk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/28 15:36:44 by azenk             #+#    #+#             */
/*   Updated: 2026/07/28 15:36:49 by azenk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ignore_parent_signals(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	wait_children(t_exec *exec)
{
	int	status;
	int	quit_printed;

	quit_printed = 0;
	while (waitpid(-1, &status, 0) > 0)
	{
		if (WIFSIGNALED(status))
		{
			if (WTERMSIG(status) == SIGQUIT && quit_printed == 0)
			{
				ft_putendl_fd("Quit (core dumped)", 2);
				quit_printed = 1;
			}
			else if (WTERMSIG(status) == SIGINT)
				printf("\n");
			exec->status = 128 + WTERMSIG(status);
		}
		else if (WIFEXITED(status))
			exec->status = WEXITSTATUS(status);
	}
}

void	init_parent_signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	init_child_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
