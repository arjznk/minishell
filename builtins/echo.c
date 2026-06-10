#include "minishell.h"


void    ft_echo(char *str)
{
    if(ft_strncmp(str, "echo -n", 7) == 0)
        ft_echo_n(str);
    else
        echo_simple_quote(str);
}

void    echo_simple_quote(char *str)
{
    char *line;
    int i;

    i = 0;
    line = ft_strchr(str, ' ');
    if(ft_strncmp(str, "echo", 4) == 0)
    {
        while(line[i])
        {
            while(line[i] == '\'' || line[i] == (char)'"')
                i++;
            write(1, &line[i++], 1);
        }
        printf("\n");
    }
}

void   ft_echo_n(char *str)
{
    char *line;
    int i;

    i = 0;
    line = ft_strchr_echo(str, 'n');
    while(line[i])
    {
        while(line[i] == '\'' || line[i] == (char)'"')
            i++;
        write(1, &line[i++], 1);
    }
}

