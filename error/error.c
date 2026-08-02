/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rijebbar <rijebbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/28 15:56:53 by azenk             #+#    #+#             */
/*   Updated: 2026/08/02 16:27:24 by rijebbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	dot_error(t_exec *exec)
{
	char	*cmd;
	int		i;
	t_cmd	*tmp;

	tmp = *exec->cmd;
	while (tmp)
	{
		exec->tmp = tmp;
		i = 0;
		while (exec->tmp->args[i])
		{
			cmd = exec->tmp->args[i];
			if (dot_error_return(exec, i, cmd))
				return (1);
			i++;
		}
		tmp = tmp->next_cmd;
	}
	return (0);
}

int	check_directory(t_exec *exec)
{
	int		i;
	t_cmd	*tmp;

	tmp = *exec->cmd;
	if (!(exec->tmp->args) && !(exec->tmp->heredoc))
		return (0);
	while (tmp)
	{
		exec->tmp = tmp;
		i = 0;
		if(!(exec->tmp->args))
			return (0);
		while ((exec->tmp->args[i]))
		{
			if(is_builtins(exec) == 0)
				return (0);
			else if (compar_and_stat(exec, i) == 1)
				return (1);
			i++;
		}
		tmp = tmp->next_cmd;
	}
	if (dot_error(exec) == 1)
		return (1);
	return (0);
}

int	compar_and_stat(t_exec *exec, int i)
{
	if (compar_char(exec->tmp->args[i][0], '/') == 0
		&& is_letter(exec->tmp->args[i][0]) == 1)
	{
		if (stat_directory(exec, i) == 1)
			return (1);
	}
	return (0);
}

int	stat_directory(t_exec *exec, int i)
{
	struct stat	st;

	(void)i;
	if (stat(exec->tmp->args[0], &st) == -1)
	{
		printf("minishell: %s : %s\n", exec->tmp->args[0], strerror(errno));
		exec->status = 127;
		return (1);
	}
	if (S_ISDIR(st.st_mode))
	{
		printf("minishell: %s : Is a directory\n", exec->tmp->args[0]);
		exec->status = 126;
		return (1);
	}
	return (0);
}
