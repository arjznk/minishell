#include "minishell.h"

void    ft_unset(char *str, t_env **env)
{
    char *line;
    t_env *tmp;
    t_env *prev;
    t_env *to_free;
    int i;
    char **all;

    (1 && (all = ft_split(str, ' '), prev = NULL, tmp = *env));
    if(!all)
        return;
    while(tmp)
    {
        i = 1;
        while(all[i])
        {
            line = all[i];
            if(ft_strncmp(tmp->variable, line, ft_strlen(line)) == 0)
            {
                to_free = tmp;
                if(prev == NULL)
                    unset_if_first(env, tmp, to_free);
                else
                {
                    t_env *next = tmp->next;
                    unset_if_middle(prev, to_free);
                    prev = tmp;
                    tmp = next;
                }
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

void unset_if_middle(t_env *prev, t_env *to_free)
{
    prev->next = to_free->next;
    free(to_free->variable);
    free(to_free->value);
    free(to_free);
}
