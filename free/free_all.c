#include "minishell.h"

void free_all(t_exec *exec)
{
	if(exec->env)
		free_node_env(exec->env);
	if(exec->path)
	{
		free_tab(exec->path->path_access);
		free(exec->path);
	}
	if(exec->line)
		free(exec->line);
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

