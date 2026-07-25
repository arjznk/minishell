/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azenk <azenk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/25 17:47:35 by azenk             #+#    #+#             */
/*   Updated: 2026/07/25 17:52:47 by azenk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	token_pipe(t_token **token, int *i)
{
	t_token	*new;

	new = new_token("|", T_PIPE);
	add_token(token, new);
	(*i)++;
}

void	token_redir_in(t_token **token, int *i, char *str)
{
	t_token	*new;

	if (str[*i + 1] == '<')
	{
		new = new_token("<<", T_HEREDOC);
		add_token(token, new);
		*i += 2;
	}
	else
	{
		new = new_token("<", T_REDIR_IN);
		add_token(token, new);
		(*i)++;
	}
}

void	token_redir_out(t_token **token, int *i, char *str)
{
	t_token	*new;

	if (str[*i + 1] == '>')
	{
		new = new_token(">>", T_APPEND);
		add_token(token, new);
		*i += 2;
	}
	else
	{
		new = new_token(">", T_REDIR_OUT);
		add_token(token, new);
		(*i)++;
	}
}

void	token_word(t_token **token, int *i, char *str)
{
	t_token	*new;
	char	*word;

	// char *clean;
	word = find_word(str, *i);
	// clean = delete_quotes(word);
	new = new_token(word, T_WORD);
	add_token(token, new);
	*i += ft_strlen(word);
	free(word);
}


char	**heredocs_delims(t_token *token, int count)
{
	char **tab;
	t_token *tmp;
	int i;

	tab = malloc(sizeof(char *) * (count + 1));
	if (!tab)
		return (NULL);
	tmp = token;
	i = 0;
	while (tmp)
	{
		if (tmp->type == T_HEREDOC && tmp->next_token)
		{
			tab[i] = ft_strdup(tmp->next_token->str);
			i++;
		}
		tmp = tmp->next_token;
	}
	tab[i] = NULL;
	return (tab);
}