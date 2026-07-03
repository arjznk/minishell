#include "minishell.h"

void	ft_unset(t_exec *exec)
{
	t_env *tmp;
	t_env *prev;
	t_env *to_free;
	char *key;
	// int i;

	tmp = (*exec->env);
	prev = NULL;
	while(tmp && (*exec->cmd)->args[1])
	{
		// i = 1;
		key = search_and_stop((*exec->cmd)->args[1], '=');
		if(ft_strncmp(tmp->variable, key, ft_strlen(key)) == 0)
		{
			to_free = tmp;
			if(!prev)
				tmp = tmp->next;
			else
				prev->next = tmp->next;
			free(to_free->variable);
    		free(to_free->value);
    		free(to_free);
		}
		prev = tmp;
		tmp = tmp->next;
		// i++;
	}
}

