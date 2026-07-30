/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rijebbar <rijebbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/25 17:47:57 by azenk             #+#    #+#             */
/*   Updated: 2026/07/30 11:23:58 by rijebbar         ###   ########.fr       */
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
	if (exec->tmp->append == 1)
	{
		if ((exec->redir_fd = open(exec->tmp->outfile,
					O_CREAT | O_WRONLY | O_APPEND, 0644)) == -1)
		{
			redir_error(exec);
			return (1);
		}
	}
	else if (exec->tmp->outfile && exec->tmp->append == 0)
	{
		if ((exec->redir_fd = open(exec->tmp->outfile,
					O_CREAT | O_WRONLY | O_TRUNC, 0644)) == -1)
		{
			redir_error(exec);
			return (1);
		}
	}
	return (0);
}

int	redir_infile(t_exec *exec)
{
	if (exec->tmp->infile && exec->tmp->append == 0)
	{
		if ((exec->redir_fd = open(exec->tmp->infile, O_RDONLY)) == -1)
		{
			redir_error(exec);
			return (1);
		}
	}
	return (0);
}

int	found_outfile(t_exec *exec)
{
	exec->redir_fd = -1;
	if (exec->tmp->outfile || exec->tmp->append)
		return (0);
	return (1);
}

int	found_infile(t_exec *exec)
{
	exec->redir_fd = -1;
	if (exec->tmp->infile)
		return (0);
	return (1);
}
