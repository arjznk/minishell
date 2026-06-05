#include "minishell.h"

void    ft_env(char *str, t_env **env)
{
	char *line;

	line = ft_strchr(str, ' ');
    if (ft_strncmp(str, "env", 3) == 0)
    {
		if(line)
		{
			printf("env: ‘%s’: No such file or directory\n", line);
			return;
		}
		print_env(env);
	}
		
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
