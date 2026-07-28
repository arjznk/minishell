/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rijebbar <rijebbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/25 17:48:35 by azenk             #+#    #+#             */
/*   Updated: 2026/07/28 14:52:13 by rijebbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void    expand_var(t_exec *exec)
// {
//     char *line;
//     t_env *tmp;
//     int i;

//     tmp = (*exec->env);
//     line = ft_strchr((*exec->cmd)->args[1], '$');
//     i = 0;
//     while(tmp)
//     {
//         if(ft_strcmp(line, tmp->variable) == 0)
//             printf("%s\n", tmp->value);
//         tmp = tmp->next;
//         i++;
//     }
// }

void	exit_code(t_exec *exec)
{
	if (ft_strcmp((*exec->cmd)->args[1], "$?") == 0)
		printf("%d\n", exec->status);
}

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

// char	*get_env_value(char *var_name, t_env *env)
// {
// 	while (env)
// 	{
// 		if (ft_strcmp(var_name, env->variable) == 0)
// 			return (env->value);
// 		env = env->next;
// 	}
// 	return (ft_strdup(""));
// }

char	*get_env_value(char *var_name, t_env *env)
{
	while (env)
	{
		if (ft_strcmp(var_name, env->variable) == 0)
			return (ft_strdup(env->value));
		// else if (env->next == NULL)
		// 	return (NULL);
		env = env->next;
	}
	return (ft_strdup(""));
}

char	*expand_var2(char *str, int *i, char *result, t_exec *exec)
{
	char	*var_name;
	char	*value;
	char	*new_result;

	if (str[*i + 1] == '?')
	{
		value = ft_itoa(exec->status);
		new_result = ft_strjoin(result, value);
		free(result);
		free(value);
		(*i)++;
		return (new_result);
	}
	if (!str[*i + 1] || str[*i + 1] == ' ')
		return (join_char(result, '$'));
	var_name = get_var_name(str, i);
	value = get_env_value(var_name, *(exec->env));
	if (!value)
	{
		free_for_expand(result, value, var_name);
		return (NULL);
	}
	new_result = ft_strjoin(result, value);
	free_for_expand(result, value, var_name)
;	return (new_result);
}

void	free_for_expand(char *result, char *value, char *var_name)
{
	if(result)
		free(result);
	if(value)
		free(value);
	if(var_name)
		free(var_name);
}
