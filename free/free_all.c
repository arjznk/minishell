/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rijebbar <rijebbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/25 17:48:24 by azenk             #+#    #+#             */
/*   Updated: 2026/08/02 18:37:37 by rijebbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_node_token(t_token **list)
{
	t_token	*tmp;

	if (!list)
		return ;
	while (*list)
	{
		tmp = (*list)->next_token;
		free((*list)->str);
		free(*list);
		*list = tmp;
	}
	*list = NULL;
}

void	free_node_cmd(t_cmd **list)
{
	t_cmd	*tmp;

	if (!list)
		return ;
	while (*list)
	{
		tmp = (*list)->next_cmd;
		if ((*list)->args)
			free_tab((*list)->args);
		free((*list)->infile);
		free((*list)->outfile);
		free((*list)->heredoc);
		if ((*list)->heredocs_delims)
			free_tab((*list)->heredocs_delims);
		free(*list);
		*list = tmp;
	}
	*list = NULL;
}

void	free_node_path(t_path_acces **list)
{
	t_path_acces	*tmp;

	if (!list)
		return ;
	while (*list)
	{
		tmp = (*list)->next;
		free((*list)->acces);
		free(*list);
		*list = tmp;
	}
	*list = NULL;
}

void	free_parsing(t_exec *exec)
{
	if (exec->tokens)
		free_node_token(exec->tokens);
	if (exec->tmp_tokens)
		free_tmp_token(exec->tmp_tokens);
	if (exec->cmd)
	{
		free_node_cmd(exec->cmd);
		exec->tmp = NULL;
	}
}

void	free_tmp_token(t_token *list)
{
	t_token	*tmp;

	if (!list)
		return ;
	while (list)
	{
		tmp = list->next_token;
		free(list->str);
		free(list);
		list = tmp;
	}
	list = NULL;
}
