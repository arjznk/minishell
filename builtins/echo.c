/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rijebbar <rijebbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/25 17:49:08 by azenk             #+#    #+#             */
/*   Updated: 2026/08/02 19:47:59 by rijebbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(t_exec *exec)
{
	char	*cmd1;

	cmd1 = exec->tmp->args[0];
	if (ft_strcmp(cmd1, "echo") != 0)
	{
		printf("minishell: %s: command not found\n", cmd1);
		exec->status = 127;
		return ;
	}
	echo(exec);
	exec->status = 0;
}

void	echo(t_exec *exec)
{
	char	**line;
	int		i;
	int		newline;

	i = 1;
	newline = 1;
	line = exec->tmp->args;
	while (line[i] && check_n_valid(line[i]) == 1)
	{
		newline = 0;
		i++;
	}
	while (line[i])
	{
		write(STDOUT_FILENO, line[i], ft_strlen(line[i]));
		if (line[i + 1])
			write(STDOUT_FILENO, " ", 1);
		i++;
	}
	if (newline)
		write(STDOUT_FILENO, "\n", 1);
}

void	echo_n(t_exec *exec)
{
	echo(exec);
}

int	check_n_valid(char *line)
{
	int	i;

	if (!line || line[0] != '-' || line[1] == '\0')
		return (0);
	i = 1;
	while (line[i])
	{
		if (line[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}
