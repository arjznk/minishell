#include "minishell.h"

void free_all(char *line, t_path *path, t_env **env)
{
	// (void)path;
   free_node_env(env);
//    free_node_path(path);
	free(path);
   free(line);
   exit(0);
}

void	free_tab(long *tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free((void *)tab[i]);
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
		free(*list);
	    (*list)->next = tmp;
	}
	*list = NULL;
}
void	free_node_path(t_path_access **list)
{
	t_path_access	*tmp;

	if (!list)
		return ;
	while (*list)
	{
		tmp = (*list)->next;
		free(*list);
	    (*list)->next = tmp;
	}
	*list = NULL;
}
