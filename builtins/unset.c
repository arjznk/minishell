#include "minishell.h"

void 	ft_unset(char *str, t_env **env)
{
	char *line;

	line = ft_strchr(str, ' ');
	if(ft_strncmp(str, "unset", 5) == 0)
	{
		t_env *tmp;
		t_env *
		tmp = *env;
		while(tmp)
		{
			if(ft_strncmp(tmp->variable, line, ft_strlen(line)) == 0)
			{
				if(prev == )
				tmp = (*env)->next;
				free(*env);
			}
			tmp->next = tmp;
		}
	}
}