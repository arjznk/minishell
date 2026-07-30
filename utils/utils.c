/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rijebbar <rijebbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 12:41:45 by rijebbar          #+#    #+#             */
/*   Updated: 2026/07/30 12:52:49 by rijebbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_token(t_token **token)
{
	t_token	*tmp;

	tmp = *token;
	if (!tmp)
		return ;
	while (tmp)
	{
		printf("%s\n", tmp->str);
		tmp = tmp->next_token;
	}
}

char	*search_and_stop(char *str, char c)
{
	int		i;
	char	*dest;

	i = 0;
	dest = malloc(sizeof(char) * ft_strlen(str) + 1);
	if (!dest)
		return (NULL);
	while (str[i] && str[i] != c)
	{
		dest[i] = str[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*str_between(char *str, char c)
{
	char	*line;

	line = ft_strchr(str, c);
	line = search_and_stop(line, c);
	return (line);
}

int	c_strcmp(char *str, char b)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == b)
			return (0);
		i++;
	}
	return (1);
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
