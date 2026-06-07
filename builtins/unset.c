#include "minishell.h"

void    ft_unset(char *str, t_env **env)
{
    // char *line;
    t_env *tmp;
    t_env *prev;
    t_env *to_free;

    // line = ft_strchr(str, ' ');
    char **all = ft_split(str, ' ');
    if(!all)
        return;
    prev = NULL;
    tmp = *env;
    int i = 1;
    while(tmp)
    {
        while(all[i])
        {
            if(ft_strncmp(tmp->variable, all[i], ft_strlen(all[i])) == 0)
            {
                to_free = tmp;
                if(prev == NULL)
                    unset_if_first(env, tmp, to_free);
                else
                    unset_if_middle(tmp, prev, to_free);
            }
            i++;
        }
        prev = tmp;
        tmp = tmp->next;
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
