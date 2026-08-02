/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rijebbar <rijebbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/02 20:45:14 by rijebbar          #+#    #+#             */
/*   Updated: 2026/08/02 20:45:17 by rijebbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_heredoc2(t_exec *exec)
{
	close(exec->heredoc_fd);
	exec->saved_stdin_heredoc = dup(STDIN_FILENO);
}
