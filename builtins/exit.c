#include "minishell.h"

void    ft_exit(char *str)
{
    char *nb;
    char *line;

    if(ft_strncmp(str, "exit", 4) == 0)
    {
        nb = ft_strchr(str, ' ');
        line = search_and_stop(str, 't');
        if(line && !nb)
        {
            printf("exit\n");
            exit(0);
        }
        else if(line && ft_isdigit(nb) == 1)
        {
            printf("exit\nminishell: exit: %s: numeric argument required\n", nb);
            exit(2);
        }
        else
            ft_exit_code(line, nb);
    }
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
// code :
/*
0 = succes
1 = erreur generique, command qui echou sans raison precise
2 = mauvaise utilisation (mauvais arg, fichier introuvable)
126 = commande trouvee mais non executable
127 = commande introuvable
128 +N = processus tue par le signal N
130 = interrompu par ctrl C (signal 2)
*/
