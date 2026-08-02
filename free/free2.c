/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rijebbar <rijebbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/28 16:38:34 by azenk             #+#    #+#             */
/*   Updated: 2026/08/02 20:40:32 by rijebbar         ###   ########.fr       */
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
	if (exec->old_pwd)
		free(exec->old_pwd);
	free_all2(exec);
	close(STDIN_FILENO);
	close(STDERR_FILENO);
	close(STDOUT_FILENO);
	free(exec);
}

void	free_all2(t_exec *exec)
{
	if (exec->saved_stdin_heredoc != -1)
	{
		close(exec->saved_stdin_heredoc);
		exec->saved_stdin_heredoc = -1;
	}
	if (exec->saved_stdin != -1)
	{
		close(exec->saved_stdin);
		exec->saved_stdin = -1;
	}
	if (exec->saved_stdout != -1)
	{
		close(exec->saved_stdout);
		exec->saved_stdout = -1;
	}
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
