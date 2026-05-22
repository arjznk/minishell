#include "minishell.h"

int free_all(t_path *path)
{
    // free list env + list token 
    // free tableau path_access
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

void	free_node(t_list **list)
{
	t_list	*tmp;

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