/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rijebbar <rijebbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/28 15:56:53 by azenk             #+#    #+#             */
/*   Updated: 2026/07/28 17:40:27 by rijebbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_error(t_exec *exec)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(exec->tmp->args[0], 2);
	ft_putendl_fd(": command not found", 2);
	exec->status = 127;
	close_files(exec);
	if (exec->old_fd != -1)
		close(exec->old_fd);
	free_all(exec);
	exit(127);
}

int	dot_error(t_exec *exec)
{
	char	*cmd;
	int i;
	t_cmd *tmp;

	tmp = *exec->cmd;
	while(tmp)
	{
		i = 0;
		while(exec->tmp->args[i])
		{
			cmd = exec->tmp->args[i];
			if (count_dots(exec->tmp->args[i]) > 1)
			{
				ft_putstr_fd("minishell: ", 2);
				ft_putstr_fd(cmd, 2);
				ft_putendl_fd(": command not found", 2);
				exec->status = 2;
				return (1);
			}
			else if (ft_strcmp(cmd, ".") == 0)
			{
				ft_putstr_fd("minishell: ", 2);
				ft_putstr_fd(cmd, 2);
				ft_putendl_fd(": filename argument required", 2);
				ft_putstr_fd(cmd, 2);
				ft_putendl_fd(": usage: . [-p path] filename [arguments]", 2);
				exec->status = 2;
				return (1);
			}
			i++;
		}
		tmp = tmp->next_cmd;
	}
	return (0);
}

int count_dots(char *cmd)
{
    int i;
    int count;

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

void	syntax_error(char *token, t_exec *exec)
{
	printf("minishell: syntax error near unexpected token '%s'\n", token);
	exec->status = 2;
}

int	check_directory(t_exec *exec)
{
	struct stat	st;
	int i;

	t_cmd *tmp;
	
	tmp = *exec->cmd;
	if (!((*exec->cmd)->args))
		return (0);
	while(tmp)
	{
		i = 0;
		while((exec->tmp->args[i]))
		{
			if (c_strcmp(exec->tmp->args[i], '/') == 0)
			{
				if (stat(exec->tmp->args[i], &st) == -1)
				{
					printf("minishell: %s : %s\n", exec->tmp->args[0],
						strerror(errno));
					exec->status = 127;
					return (1);
				}
				if (S_ISDIR(st.st_mode))
				{
					printf("minishell: %s : Is a directory\n", exec->tmp->args[0]);
					exec->status = 126;
					return (1);
				}
			}
			i++;	
		}
		tmp = tmp->next_cmd;
	}
	if (dot_error(exec) == 1)
		return (1);
	return (0);
}
