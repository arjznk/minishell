/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rijebbar <rijebbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/25 17:48:35 by azenk             #+#    #+#             */
/*   Updated: 2026/08/02 20:32:47 by rijebbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_var_name(char *str, int *i)
{
	int	start;

	(*i)++;
	start = *i;
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;
	(*i)--;
	return (ft_substr(str, start, *i - start + 1));
}

char	*get_env_value(char *var_name, t_env *env)
{
	while (env)
	{
		if (ft_strcmp(var_name, env->variable) == 0)
			return (ft_strdup(env->value));
		env = env->next;
	}
	return (ft_strdup(""));
}

char	*expand_var(char *str, int *i, char *result, t_exec *exec)
{
	if (str[*i + 1] == '?')
	{
		expand_var2(exec, result);
		(*i)++;
		return (exec->new_result);
	}
	if (str[*i + 1] == '$')
	{
		expand_var3(exec, result);
		(*i)++;
		return (exec->new_result);
	}
	if (!str[*i + 1] || str[*i + 1] == ' ')
		return (join_char(result, '$'));
	exec->var_name = get_var_name(str, i);
	exec->value = get_env_value(exec->var_name, *(exec->env));
	if (!exec->value)
		return (free_for_expand(result, exec->value, exec->var_name), NULL);
	exec->new_result = ft_strjoin(result, exec->value);
	free_for_expand(result, exec->value, exec->var_name);
	return (exec->new_result);
}

void	free_for_expand(char *result, char *value, char *var_name)
{
	if (result)
		free(result);
	if (value)
		free(value);
	if (var_name)
		free(var_name);
}
