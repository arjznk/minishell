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

