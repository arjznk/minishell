#include "minishell.h"

void    ft_unset(char *str, t_env **env)
{
    char *line;
    t_env *tmp;
    t_env *prev;
    t_env *to_free;

    char **all = ft_split(str, ' ');
    if(!all)
    return;
    prev = NULL;
    tmp = *env;
    int i;
    while(tmp)
    {
        i = 1;
        while(all[i])
        {
            line = all[i];
            printf("variable dans la liste actuel = %s\n", tmp->variable);
            if(ft_strncmp(tmp->variable, line, ft_strlen(line)) == 0)
            {
                printf("all[i] = %s\n", line);
                to_free = tmp;
                if(prev == NULL)
                    unset_if_first(env, tmp, to_free);
                else
                {
                    printf("to_free = %s\n", to_free->variable);
                    printf("variable de all[i] dans la liste = %s\n", tmp->variable);
                    unset_if_middle(tmp, prev, to_free);
                    // return;
                }
            }
            printf("a\n");
            i++;
            printf("b\n");
        }
        printf("c\n");
        prev = tmp;
        printf("d\n");
        tmp = tmp->next;
        printf("e\n");
    }
}

void   unset_if_first(t_env **env, t_env *tmp, t_env *to_free)
{
    *env = tmp->next;
    free(to_free);
}

void unset_if_middle(t_env *tmp, t_env *prev, t_env *to_free)
{
    printf("prev->next->variable = %s\n", prev->next->variable);
    prev->next = tmp;
    printf("to_free dans unset_if_middle = %s\n", to_free->variable);
    free(to_free->variable);
    free(to_free->value);
    printf("tmp->next->variable = %s\n", tmp->next->variable);
    tmp = tmp->next;
    printf("pas ici\n");
}
