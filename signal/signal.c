/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azenk <azenk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/25 17:47:52 by azenk             #+#    #+#             */
/*   Updated: 2026/07/25 17:47:53 by azenk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	handle_sigint(int sig)
// {
// 	(void)sig;
// 	printf("\n");
// 	rl_on_new_line();
// 	rl_replace_line("", 0);
// 	rl_redisplay();
// }

// void	init_signals(void)
// {
// 	signal(SIGINT, handle_sigint);
// 	signal(SIGQUIT, SIG_IGN);

// }

// void	handle_sigquit(int sig)
// {
// 	(void)sig;

// 	printf("Quit (core dumped)\n");
// }

void	handle_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
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

// void	handle_child_status(t_exec *exec, int status)
// {
// 	if (WIFSIGNALED(status))
// 	{
// 		if (WTERMSIG(status) == SIGQUIT)
// 			ft_putendl_fd("Quit (core dumped)", 2);
// 		else if (WTERMSIG(status) == SIGINT)
// 			write(1, "\n", 1);
// 		exec->status = 128 + WTERMSIG(status);
// 	}
// 	else if (WIFEXITED(status))
// 		exec->status = WEXITSTATUS(status);
// }

// void	handle_child_status(t_exec *exec, int status)
// {
// 	if (WIFSIGNALED(status))
// 		exec->status = 128 + WTERMSIG(status);
// 	else if (WIFEXITED(status))
// 		exec->status = WEXITSTATUS(status);
// }

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
				write(1, "\n", 1);
			exec->status = 128 + WTERMSIG(status);
		}
		else if (WIFEXITED(status))
			exec->status = WEXITSTATUS(status);
	}
}

void	ignore_parent_signals(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}