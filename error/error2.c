/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rijebbar <rijebbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 12:47:54 by rijebbar          #+#    #+#             */
/*   Updated: 2026/08/02 15:26:27 by rijebbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_error(t_exec *exec, int i, char *line)
{
	free(line);
	ft_putstr_fd("minishell: warning: here-document at line ", 2);
	ft_putnbr_fd(exec->count_line, 2);
	ft_putstr_fd(" delimited by end-of-file (wanted `", 2);
	ft_putstr_fd((*exec->cmd)->heredocs_delims[i], 2);
	ft_putendl_fd("')", 2);
}

void	cmd_error(t_exec *exec)
{
	char	*line;
	char	*tmp;

	tmp = ft_strjoin("minishell: ", exec->tmp->args[0]);
	line = ft_strjoin(tmp, ": command not found\n");
	free(tmp);
	write(2, line, ft_strlen(line));
	free(line);
	exec->status = 127;
	close_files(exec);
	dup_close_heredoc(exec);
	if (exec->old_fd != -1)
		close(exec->old_fd);
	free_all(exec);
	exit(127);
}

void	syntax_error(char *token, t_exec *exec)
{
	printf("minishell: syntax error near unexpected token '%s'\n", token);
	exec->status = 2;
}
