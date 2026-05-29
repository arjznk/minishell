#include "minishell.h"

void	print_list(t_env **env)
{
	t_env	*tmp;

	tmp = *env;
	if (!tmp)
		return ;
	while (tmp != NULL)
	{
		printf("%s\n", tmp->value);
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

int is_letter(char *str)
{
    int i;

    i = 0;
    while(str[i])
    {
        if(!(str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z'))
            return(1);
        i++;
    }
    return(0);
}

