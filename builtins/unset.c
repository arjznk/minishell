#include "minishell.h"

void    ft_unset(char *str, t_env **env)
{
    char *line;

    line = ft_strchr(str, ' ');
    if(ft_strncmp(str, "unset", 5) == 0)
    {
        t_env *tmp;

        tmp = *env;
        while(tmp)
        {
            if((tmp->variable == line))
            {
                tmp = (*env)->next;
                free(*env);
            }
            tmp = tmp->next;
        }
    }
}