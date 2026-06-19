#include "minishell.h"

void    expand_var(t_exec *exec)
{
    char *line;
    t_env *tmp;
    int i;

    tmp = (*exec->env);
    line = ft_strchr((*exec->cmd)->args[1], '$');
    i = 0;
    while(tmp)
    {
        if(ft_strcmp(line, tmp->variable) == 0)
            printf("%s\n", tmp->value);
        tmp = tmp->next;
        i++;
    }
}

void    exit_code(t_exec *exec)
{
    if(ft_strcmp((*exec->cmd)->args[1], "$?") == 0)
        printf("%d\n", exec->status);
}

/*
expand de base avec variable ex : $USER fonctionne
mais avec quote non  
*/