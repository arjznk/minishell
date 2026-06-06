#include "minishell.h"

void	print_list(t_env **env)
{
	t_env	*tmp;

	tmp = *env;
	if (!tmp)
		return ;
	while (tmp != NULL)
	{
		printf("%s\n", tmp->variable);
		tmp = tmp->next;
	}
}

char *search_and_stop(char *str, char c)
{
    int i;
    char *dest;
    
    i = 0;
    dest = malloc(sizeof(char) * ft_strlen(str));
    if(!dest)
        return NULL;
    while(str[i] && str[i] != c)
    {
        dest[i] = str[i];
        i++;
    }
    dest[i] = '\0';
    return (dest);
}

char    *str_between(char *str, char c)
{
    char *line;

    line = ft_strchr(str, c);
    line = search_and_stop(line, c);
    return(line);
}

int c_strcmp(char *str, char b)
{
    int i;
    
    i = 0;
    while(str[i])
    {
        if(str[i] == b)
            return (0);
        i++;
    }
    return (1);
}

void    sort_str(t_env **env)
{
    t_env *tmp;
	char *tmp_var;
	char *tmp_val;
	int swap;

	swap = 1;
    while(swap)
    {
		swap = 0;
		tmp = *env;
		while(tmp && tmp->next)
        {
            if(ft_strcmp(tmp->variable, tmp->next->variable) > 0)
            {
				tmp_var = tmp->variable;
				tmp->variable = tmp->next->variable;
				tmp->next->variable = tmp_var;
				tmp_val = tmp->value;
				tmp->value = tmp->next->value;
				tmp->next->value = tmp_val;
				swap = 1;
            }
			tmp = tmp->next;
        }
    }
}

