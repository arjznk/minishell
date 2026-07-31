/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rijebbar <rijebbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/28 15:56:53 by azenk             #+#    #+#             */
/*   Updated: 2026/07/31 18:47:18 by rijebbar         ###   ########.fr       */
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

int	dot_error_return(t_exec *exec, int i, char *cmd)
{
	if (count_dots(exec->tmp->args[i]) == 2)
	{
		if (ft_strcmp("cd", exec->tmp->args[0]) == 0 && ft_strcmp("..",
				exec->tmp->args[1]) == 0)
			return (0);
		else
		{
			return_point(exec, cmd);
			return (1);
		}
	}
	else if (count_dots(exec->tmp->args[i]) > 1)
	{
		return_point(exec, cmd);
		return (1);
	}
	else if (ft_strcmp(cmd, ".") == 0)
	{
		return_point_only(exec, cmd);
		return (1);
	}
	return (0);
}

void	return_point_only(t_exec *exec, char *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(": filename argument required", 2);
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(": usage: . [-p path] filename [arguments]", 2);
	exec->status = 2;
}

void	return_point(t_exec *exec, char *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(": command not found", 2);
	exec->status = 127;
}

int	count_dots(char *cmd)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (cmd[i])
	{
		if (cmd[i] == '.')
			count++;
		i++;
	}
	return (count);
}

int	check_directory(t_exec *exec)
{
	int		i;
	t_cmd	*tmp;

	tmp = *exec->cmd;
	if (!(exec->tmp->args))
		return (0);
	while (tmp)
	{
		i = 0;
		while ((exec->tmp->args[i]))
		{
			if (ft_strcmp("echo", exec->tmp->args[0]) == 0)
				break ;
			if (compar_and_stat(exec, i) == 1)
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

	if (stat(exec->tmp->args[i], &st) == -1)
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
