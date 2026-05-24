#include "minishell.h"

void    ft_echo(char *str)
{
    char *line; 

    line = ft_strchr(str, ' ');
    if(ft_strncmp(str, "echo", 4) == 0)
    {
        if(c_strcmp(line, (char)'"') == 0)
            line = str_between(line, (char)'"');
        printf("%s\n", line);   
    }

}

void    echo_for_exit(char *str, int nb)
{
    char *line;

    line = ft_strchr(str, ' ');
    if(ft_strncmp(str, "echo", 4) == 0)
    {
        if(ft_strncmp(line, "$?", 2) == 0)
        {
            if(nb > 255)
                printf("%d\n", nb / 256);
            else
                printf("%d\n", nb);
            if((nb >= 'a' && nb <= 'z') || (nb >= 'A' && nb <= 'Z'))
                printf("2\n");
        }
    }
}

