/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azenk <azenk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/25 17:49:12 by azenk             #+#    #+#             */
/*   Updated: 2026/07/25 17:49:13 by azenk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_exec *exec)
{
	char	*line;

	line = exec->tmp->args[1];
	if (line)
	{
		printf("env: ‘%s’: No such file or directory\n", line);
		exec->status = 127;
		return ;
	}
	print_env((exec->env));
	exec->status = 0;
}

void	print_env(t_env **env)
{
	t_env	*tmp;

	tmp = *env;
	if (!tmp)
		return ;
	while (tmp != NULL)
	{
		if ((tmp->value == NULL) && (ft_strcmp(tmp->variable, "=") == 0))
			printf("%s=\n", tmp->variable);
		else if (tmp->value && tmp->variable)
			printf("%s=%s\n", tmp->variable, tmp->value);
		else
			break ;
		tmp = tmp->next;
	}
}
