/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azenk <azenk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/28 17:02:06 by azenk             #+#    #+#             */
/*   Updated: 2026/07/28 17:02:29 by azenk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redir_error(t_exec *exec)
{
	if ((*exec->cmd)->infile)
		printf("minishell: %s: %s\n", (*exec->cmd)->infile, strerror(errno));
	else if ((*exec->cmd)->outfile)
		printf("minishell: %s: %s\n", (*exec->cmd)->outfile, strerror(errno));
	exec->status = 1;
}
