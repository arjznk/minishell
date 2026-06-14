#include "minishell.h"

void    ft_env(char *str, t_env **env)
{
	char *line;

	line = ft_strchr(str, ' ');
	if(line)
	{
		printf("env: ‘%s’: No such file or directory\n", line);
		return;
	}
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
		if((tmp->value == NULL) && (ft_strcmp(tmp->variable, "=") == 0))
            printf("%s=\n", tmp->variable);
		else if(tmp->value && tmp->variable)
			printf("%s=%s\n", tmp->variable, tmp->value);
		else
			break;
		tmp = tmp->next;
	}
}
