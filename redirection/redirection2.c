/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rijebbar <rijebbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/28 17:02:06 by azenk             #+#    #+#             */
/*   Updated: 2026/07/30 11:25:59 by rijebbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redir_error(t_exec *exec)
{
	if(exec->tmp->infile)
		printf("minishell: %s: %s\n", exec->tmp->infile, strerror(errno));
	else if(exec->tmp->outfile && exec->tmp->append == 0)
		printf("minishell: %s: %s\n", exec->tmp->outfile, strerror(errno));
	else if(exec->tmp->outfile && exec->tmp->append == 1)
		printf("minishell: %s: %s\n", exec->tmp->outfile, strerror(errno));
	exec->status = 1;
}
