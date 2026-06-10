#include "minishell.h"

void    ft_env(char *str, t_env **env)
{
    if (ft_strncmp(str, "env", 3) == 0)
        print_env(env);
}

void	print_env(t_env **env)
{
	t_env	*tmp;

	tmp = *env;
	if (!tmp)
		return ;
	while (tmp != NULL)
	{
		printf("%s=%s\n", tmp->variable, tmp->value);
		tmp = tmp->next;
	}
}
