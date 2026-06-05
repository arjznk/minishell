#include "minishell.h"

void    ft_unset(char *str, t_env **env)
{
    char *line;

    line = ft_strchr(str, ' ');
    if(!line)
        return;
    if(ft_strncmp(str, "unset", 5) == 0)
    {
        t_env *tmp;
        t_env *prev;
        t_env *to_free;

        (1 && (prev = NULL, tmp = *env));
        while(tmp)
        {
            if(ft_strncmp(tmp->variable, line, ft_strlen(line)) == 0)
            {
                to_free = tmp;
                if(prev == NULL)
                    unset_if_first(env, tmp, to_free);
                else
                    unset_if_middle(tmp, prev, to_free);
            }
            prev = tmp;
            tmp = tmp->next;
        }
    }
}

void   unset_if_first(t_env **env, t_env *tmp, t_env *to_free)
{
    *env = tmp->next;
    free(to_free);
}

void unset_if_middle(t_env *tmp, t_env *prev, t_env *to_free)
{
    prev->next = tmp->next;
    free(to_free);
}
