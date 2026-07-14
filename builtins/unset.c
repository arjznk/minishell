#include "minishell.h"

void	ft_unset(t_exec *exec)
{
	t_env *tmp;
	t_env *prev;
	char *key;
	int i;

	i = 1;
	while((*exec->cmd)->args[i])
	{
		tmp = (*exec->env);
		prev = NULL;
		key = search_and_stop((*exec->cmd)->args[i], '=');
		while(tmp)
		{
			if(ft_strcmp(tmp->variable, "PATH") == 0)
			{
				free_path(exec);
				free_unset(exec, prev, tmp);
				return;
			}
			if(ft_strcmp(tmp->variable, key) == 0)
				free_unset(exec, prev, tmp);
			prev = tmp;
			tmp = tmp->next;
		}
		i++;
	}
}

void	free_path(t_exec *exec)
{
	free_node_path(exec->acces_path);
	free_tab(exec->path->path_acces);
	
}

void	free_unset(t_exec *exec, t_env *prev, t_env *tmp)
{
	t_env *to_free;

	to_free = tmp;
	if(!prev)
		(*exec->env) = tmp->next;
	else
		prev->next = tmp->next;
	free(to_free->variable);
	free(to_free->value);
	free(to_free);
}
