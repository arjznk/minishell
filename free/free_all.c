/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rijebbar <rijebbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/25 17:48:24 by azenk             #+#    #+#             */
/*   Updated: 2026/07/28 14:32:31 by rijebbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_all(t_exec *exec)
{
	if (exec->line)
		free(exec->line);
	if (exec->env)
	{
		if (exec->path->path_acces)
			free_tab(exec->path->path_acces);
		free_node_env(exec->env);
	}
	if (exec->path)
		free(exec->path);
	if (exec->acces_path)
		free_node_path(exec->acces_path);
	free_parsing(exec);
	free(exec);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
}

void	free_cmd_tokens(t_exec *exec)
{
	if (exec->tokens && (*exec->tokens))
		free_node_token(exec->tokens);
	if (exec->cmd && (*exec->cmd))
		free_node_cmd(exec->cmd);
}

void	free_tab(char **tab)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_node_env(t_env **list)
{
	t_env	*tmp;

	if (!list)
		return ;
	while (*list)
	{
		tmp = (*list)->next;
		free((*list)->variable);
		free((*list)->value);
		free(*list);
		*list = tmp;
	}
	*list = NULL;
}

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
		if((*list)->heredocs_delims)
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
	t_token *tmp;

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