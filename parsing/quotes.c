/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rijebbar <rijebbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/25 17:48:02 by azenk             #+#    #+#             */
/*   Updated: 2026/07/30 17:52:24 by rijebbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			i++;
			while (str[i] && str[i] != '\'')
				i++;
			if (!str[i])
				return (printf("minishell: syntax error: unclosed quote\n"), 1);
		}
		if (str[i] == '"')
		{
			i++;
			while (str[i] && str[i] != '"')
				i++;
			if (!str[i])
				return (printf("minishell: syntax error: unclosed quote\n"), 1);
		}
		i++;
	}
	return (0);
}

char	*expand_and_remove_quotes(char *str, t_exec *exec)
{
	int		i;
	int		s_quotes;
	int		d_quotes;
	char	*result;

	i = 0;
	d_quotes = 0;
	s_quotes = 0;
	result = ft_strdup("");
	while (str[i])
	{
		if (str[i] == '\'' && d_quotes == 0)
			s_quotes = !s_quotes;
		else if (str[i] == '"' && s_quotes == 0)
			d_quotes = !d_quotes;
		else if (str[i] == '$' && s_quotes == 0){
			
			result = expand_var(str, &i, result, exec);
		}
		else
			result = join_char(result, str[i]);
		i++;
	}
	return (result);
}

char	*join_char(char *result, char c)
{
	char	tmp[2];
	char	*new_result;

	tmp[0] = c;
	tmp[1] = '\0';
	new_result = ft_strjoin(result, tmp);
	if (!new_result)
	{
		free(result);
		return (NULL);
	}
	free(result);
	return (new_result);
}
