#include "minishell.h"

void    ft_exit(char *str)
{
    char *nb;
    char *line;

    
    if(ft_strncmp(str, "exit", 4) == 0)
    {
        nb = ft_strchr(str, ' ');
        line = search_and_stop(str, 't');
        if((line && !nb) || (line && ft_isdigit(nb) == 0))
        {
            printf("exit\n");
            exit(0);
        }
        if(line && ft_isdigit(nb) == 1)
        {
            printf("exit\nbash: exit: g: numeric argument required\n");
            exit(0);
        }

    }  
}

// exit + nombre = exit code + nb et prochaine cmd = echo $? -> contient le nb
// exit + str = exit code 2 et prochaine cmd = echo $? -> contient 2
//exit seul -> exit