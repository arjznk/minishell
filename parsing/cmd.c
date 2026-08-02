/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rijebbar <rijebbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/25 17:48:12 by azenk             #+#    #+#             */
/*   Updated: 2026/08/02 19:41:03 by rijebbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd	*new_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	memset(cmd, 0, sizeof(t_cmd));
	cmd->args = NULL;
	cmd->append = 0;
	cmd->heredoc = NULL;
	cmd->infile = NULL;
	cmd->outfile = NULL;
	cmd->next_cmd = NULL;
	cmd->heredocs_delims = NULL;
	return (cmd);
}

void	add_cmd(t_cmd **cmds, t_cmd *new)
{
	t_cmd	*tmp;

	tmp = *cmds;
	if (!*cmds)
	{
		*cmds = new;
		return ;
	}
	else
	{
		while (tmp->next_cmd)
			tmp = tmp->next_cmd;
	}
	tmp->next_cmd = new;
}

static void	parse_redirection(t_cmd *current, t_token **tmp)
{
	if ((*tmp)->type == T_REDIR_IN)
	{
		free(current->infile);
		current->infile = ft_strdup((*tmp)->next_token->str);
	}
	else if ((*tmp)->type == T_REDIR_OUT)
	{
		free(current->outfile);
		current->outfile = ft_strdup((*tmp)->next_token->str);
	}
	else if ((*tmp)->type == T_APPEND)
	{
		free(current->outfile);
		current->outfile = ft_strdup((*tmp)->next_token->str);
		current->append = 1;
	}
	else if ((*tmp)->type == T_HEREDOC)
	{
		free(current->heredoc);
		current->heredoc = ft_strdup((*tmp)->next_token->str);
	}
	*tmp = (*tmp)->next_token;
}

t_cmd	*parse_cmd(t_token *tokens)
{
	t_cmd	*new;
	t_cmd	*cmds;
	t_cmd	*current;

	cmds = NULL;
	new = new_cmd();
	add_cmd(&cmds, new);
	current = new;
	while (tokens)
	{
		if (tokens->type == T_PIPE)
		{
			new = new_cmd();
			add_cmd(&cmds, new);
			current = new;
		}
		else if (tokens->type == T_WORD)
			add_args(current, tokens->str);
		else
			parse_redirection(current, &tokens);
		tokens = tokens->next_token;
	}
	return (cmds);
}

void	add_args(t_cmd *current, char *str)
{
	char	**args;
	char	**old;
	int		i;
	int		j;

	if (!str)
		return ;
	i = 0;
	j = 0;
	while (current->args && current->args[i])
		i++;
	args = malloc(sizeof(char *) * (i + 2));
	if (!args)
		return ;
	while (j < i)
	{
		args[j] = current->args[j];
		j++;
	}
	args[i] = ft_strdup(str);
	args[i + 1] = NULL;
	old = current->args;
	current->args = args;
	free(old);
}
