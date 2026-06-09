#include "minishell.h"

void    ft_unset(char *str, t_env **env)
{
    int i;
    char **all;

	all = ft_split(str, ' ');
	i = 0;
    if (!all)
		return;
	while(all[i])
	{
		unset_env(all[i], env);
		i++;
	}
}

void	unset_env(char *line, t_env **env)
{
	t_env *tmp;
	t_env *prev;
	t_env *to_free;

	tmp = *env;
	prev = NULL;
	while(tmp)
	{
		if(ft_strncmp(tmp->variable, line, ft_strlen(line)) == 0)
		{
			to_free = tmp;
			if(!prev)
				*env = tmp->next;
			else
				prev->next = tmp->next;
			free(to_free->variable);
    		free(to_free->value);
    		free(to_free);
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

