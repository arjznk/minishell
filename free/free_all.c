#include "minishell.h"

void free_all(t_exec *exec)
{
	if(exec->env)
		free_node_env(exec->env);
	if(exec->path)
	{
		free_tab(exec->path->path_access);
		// free(exec->path)
	}
	if(exec->line)
		free(exec->line);
	if(exec->tokens)
		free_node_token(exec->tokens);
	if(exec->cmd)
		free_node_cmd(exec->cmd);
}

void	free_tab(char **tab)
{
	int	i; 

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
		free_tab((*list)->args);
		free((*list)->infile);
		free((*list)->outfile);
		free((*list)->heredoc);
		free(*list);
	    *list = tmp;
	}
	*list = NULL;
}
