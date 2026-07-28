/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rijebbar <rijebbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/25 17:49:21 by azenk             #+#    #+#             */
/*   Updated: 2026/07/28 15:21:47 by rijebbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_export(t_exec *exec)
{
	char	*cmd;

	cmd = exec->tmp->args[0];
	if (exec->tmp->args[0] && exec->tmp->args[1] == NULL)
		export_only((exec));
	else if (export_error(exec) != 0 && exec->tmp->args[1])
		return ;
	else if (ft_strcmp(cmd, "export") == 0)
	{
		export_w_error(exec);
		exec->status = 0;
	}
}

int	export_error(t_exec *exec)
{
	int		i;
	char	*var;

	i = 0;
	var = search_and_stop(exec->tmp->args[1], '=');
	if(!var[0] || (ft_isalpha(var[0])== 0 && var[0] != '_'))
	{
		return_export(exec, var);
		return (1);
	}
	i = 1;
	while ((var[i]))
	{
		if(ft_isalnum(var[i]) == 0 && var[i] != '_')
		{
			return_export(exec, var);
			return (1);
		}
		i++;
	}
	free(var);
	return (0);
}

void	return_export(t_exec *exec, char *var)
{
	ft_putstr_fd("minishell: export ", 2);
    ft_putstr_fd(exec->tmp->args[1], 2);
    ft_putendl_fd(": not a valid identifier", 2);
	if(var)
		free(var);
	exec->status = 1;
}

void	export_w_error(t_exec *exec)
{
	t_env	*tp;
	char	*temp;
	int		found;
	int		i;

	i = 1;
	while (exec->tmp->args[i])
	{
		temp = search_and_stop(exec->tmp->args[i], '=');
		tp = (*exec->env);
		found = 0;
		while (tp)
		{
			if (ft_strcmp(temp, tp->variable) == 0)
			{
				exist_var(exec, i, tp, temp);
				found = 1;
				break ;
			}
			tp = tp->next;
		}
		if (!found)
			add_to_env(exec, i, temp);
		i++;
	}
}

void	exist_var(t_exec *exec, int i, t_env *tp, char *temp)
{
	char	*tmp;

	(void)temp;
	tmp = ft_strchr(exec->tmp->args[i], '=');
	if (tmp != NULL)
	{
		free(tp->value);
		tp->value = ft_strdup(tmp);
	}
}

void	export_only(t_exec *exec)
{
	t_env	*tmp;

	sort_str((exec->env));
	tmp = (*exec->env);
	while (tmp)
	{
		if (tmp->value == NULL)
			printf("export %s\n", tmp->variable);
		else
			printf("export %s=\"%s\"\n", tmp->variable, tmp->value);
		tmp = tmp->next;
	}
	exec->status = 0;
}

