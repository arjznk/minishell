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
            printf("exit\nbash: exit: %s: numeric argument required\n", nb);
            exit(2);
        }
    }

}

// exit + nombre = exit code + nb et prochaine cmd = echo $? -> contient le nb
// exit + str = exit code 2 et prochaine cmd = echo $? -> contient 2
//exit seul -> exit
//code de sortie stockes sur 8 bits, entre 0 et 255
//exemple : si exit 6789 -> echo $? -> 133 car 6789 / 256 = 133
// code :
/*
0 = succes
1 = erreur generique, command qui echou sans raison precise
2 = mauvaise utilisation (mauvais arg, fichier introuvable)
126 = commande trouvee mais non executable
127 = commande introuvable
128 +N = processus tue par le signal N
130 = interrompu par ctrl C (signal 2)

donc si nb > 255 alors on fait la division sinon. print le nb 
*/
