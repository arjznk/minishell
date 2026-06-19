#include "minishell.h"

void    ft_exit(t_exec *exec)
{
    char *nb;
    char *cmd;

    nb = (*exec->cmd)->args[1];
    cmd = (*exec->cmd)->args[0];
    if(ft_strcmp(cmd, "exit") == 0)
    {
        if(cmd && !nb)
        {
            printf("exit\n");
            exit(0);
        }
        else if(cmd && ft_isdigit(nb) == 1)
        {
            printf("exit\nminishell: exit: %s: numeric argument required\n", nb);
            exit(2);
        }
        else
            ft_exit_code(cmd, nb);
    }
    else
        printf("minishell: %s: command not found\n", cmd);
}

void    ft_exit_code(char *line, char *nb)
{
    long nbr;
    
    if((line && ft_isdigit(nb) == 0))
    {
        nbr = ft_atoi(nb);
        if(nbr > INT_MAX || nbr < INT_MIN)
        {
            printf("exit\nminishell: exit: %ld: numeric argument required\n", nbr);
            exit(2);
        }
        if(nbr > 255)
        {
            printf("exit\n");
            exit(nbr % 256);
        }
        else
        {
            printf("exit\n");
            exit(nbr);
        }    
    }
}

