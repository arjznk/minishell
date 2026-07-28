/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rijebbar <rijebbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/25 17:47:07 by azenk             #+#    #+#             */
/*   Updated: 2026/07/28 15:15:11 by rijebbar         ###   ########.fr       */
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

// void	print_cmds(t_cmd *cmds)
// {
// 	t_cmd	*tmp;
// 	int		i;

// 	i = 0;
// 	tmp = cmds;
// 	while (tmp)
// 	{
// 		printf("CMD\n");
// 		i = 0;
// 		if (tmp->args)
// 		{
// 			while (tmp->args[i])
// 			{
// 				printf(" args %s\n", tmp->args[i]);
// 				i++;
// 			}
// 		}
// 		if (tmp->infile)
// 			printf("INFILE = %s\n", tmp->infile);
// 		if (tmp->outfile)
// 			printf("OUTFILE = %s\n", tmp->outfile);
// 		if (tmp->heredoc)
// 			printf("HEREDOC = %s\n", tmp->heredoc);
// 		printf("APPEND = %d\n", tmp->append);
// 		tmp = tmp->next_cmd;
// 	}
// }

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
