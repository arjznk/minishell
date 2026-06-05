#include "minishell.h"

void    ft_echo(char *str)
{
    if(ft_strncmp(str, "echo -n", 7) == 0)
        echo_n(str);
    else
        echo_quote(str);
}

void    echo_quote(char *str)
{
    char *line;
    int i;

    i = 0;
    line = ft_strchr(str, ' ');
    if(line == NULL)
    {
        printf("\n");
        return;
    }
    while(line[i])
    {
        while(line[i] == '\'' || line[i] == (char)'"')
            i++;
        write(1, &line[i++], 1);
    }
    printf("\n");
}

void   echo_n(char *str)
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

