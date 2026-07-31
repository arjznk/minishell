/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rijebbar <rijebbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/25 17:48:08 by azenk             #+#    #+#             */
/*   Updated: 2026/07/31 16:13:05 by rijebbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_redirection(t_token_type type)
{
	return (type == T_REDIR_IN || type == T_REDIR_OUT || type == T_APPEND
		|| type == T_HEREDOC);
}

int	check_pipe_syntax(t_token *token, t_exec *exec)
{
	if (token->next_token == NULL)
	{
		syntax_error("newline", exec);
		return (1);
	}
	if (token->next_token->type == T_PIPE)
	{
		syntax_error("|", exec);
		return (1);
	}
	return (0);
}

int	check_redir_syntax(t_token *token, t_exec *exec)
{
	if (token->next_token == NULL)
	{
		syntax_error("newline", exec);
		return (1);
	}
	if (token->next_token->type != T_WORD)
	{
		syntax_error(token->next_token->str, exec);
		return (1);
	}
	return (0);
}

int	check_syntax(t_token *token, t_exec *exec)
{
	t_token	*tmp;

	if (!token)
		return (1);
	if (token->type == T_PIPE)
	{
		syntax_error("|", exec);
		return (1);
	}
	tmp = token;
	while (tmp)
	{
		if (tmp->type == T_PIPE && check_pipe_syntax(tmp, exec))
			return (1);
		if (is_redirection(tmp->type) && check_redir_syntax(tmp, exec))
			return (1);
		tmp = tmp->next_token;
	}
	return (0);
}
