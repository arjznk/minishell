#include "minishell.h"

void    ft_export(char *str, t_env **env)
{
    char *line;
    t_env *newnode;

    line = ft_strchr(str, ' ');
    newnode = malloc(sizeof(t_env));
    if(ft_strncmp(str, "export", 6) == 0)
    {
        newnode->variable = search_and_stop(line, '=');
        newnode->value = ft_strchr(line, '=');
        ft_lstadd_front(env, newnode);
    }
}
