#include "minishell.h"

void	ft_unset(t_exec *exec)
{
	char	*key;
	int		i;

	i = 1;
	while(exec->tmp->args[i])
	{
		key = search_and_stop(exec->tmp->args[i], '=');
		if(ft_strcmp(key, "PATH") == 0)
			free_path(exec);
		unset_var(exec, key);
		free(key);
		i++;
	}
}

void	unset_var(t_exec *exec, char *key)
{
	t_env	*tmp;
	t_env	*prev;

	tmp = (*exec->env);
	prev = NULL;
	while(tmp)
	{
		if(ft_strcmp(tmp->variable, key) == 0)
		{
			free_unset(exec, prev, tmp);
			break;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

void	free_path(t_exec *exec)
{
	free_node_path(exec->acces_path);
	free_tab(exec->path->path_acces);
	exec->path->path_acces = NULL;
}

void	free_unset(t_exec *exec, t_env *prev, t_env *tmp)
{
	t_env	*to_free;

	to_free = tmp;
	if (!prev)
		(*exec->env) = tmp->next;
	else
		prev->next = tmp->next;
	free(to_free->variable);
	free(to_free->value);
	free(to_free);
}
