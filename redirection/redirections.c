/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azenk <azenk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/25 17:47:57 by azenk             #+#    #+#             */
/*   Updated: 2026/07/28 16:57:29 by azenk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirections(t_exec *exec)
{
	if (redir_infile(exec) == 1 || redir_outfile(exec) == 1)
		return (1);
	return (0);
}

int	redir_outfile(t_exec *exec)
{
	if ((*exec->cmd)->outfile && (*exec->cmd)->append == 1)
	{
		exec->redir_fd = open((*exec->cmd)->outfile,
				O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (exec->redir_fd == -1)
		{
			redir_error(exec);
			return (1);
		}
	}
	else if ((*exec->cmd)->outfile && (*exec->cmd)->append == 0)
	{
		exec->redir_fd = open((*exec->cmd)->outfile,
				O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (exec->redir_fd == -1)
		{
			redir_error(exec);
			return (1);
		}
	}
	return (0);
}

int	redir_infile(t_exec *exec)
{
	if ((*exec->cmd)->infile)
	{
		exec->redir_fd = open((*exec->cmd)->infile, O_RDONLY);
		if (exec->redir_fd == -1)
		{
			redir_error(exec);
			return (1);
		}
		close(exec->redir_fd);
	}
	return (0);
}

int	found_outfile(t_exec *exec)
{
	exec->redir_fd = -1;
	if ((*exec->cmd)->outfile)
		return (0);
	return (1);
}

int	found_infile(t_exec *exec)
{
	exec->redir_fd = -1;
	if ((*exec->cmd)->infile)
		return (0);
	return (1);
}
