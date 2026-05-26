#include "minishell.h"

void    ft_echo(char *str)
{

    if(ft_echo_n(str) == 0)
        return;
    else if (echo_simple_quote(str) == 0)
        return;
    else if (echo_double_quote(str) == 0)
        return;
}

int    echo_simple_quote(char *str)
{
    char *line;

    line = ft_strchr(str, ' ');
    if(ft_strncmp(str, "echo", 4) == 0)
    {
        if ((c_strcmp(line, '\'') == 0) && (c_strrcmp(line, '\'') == 0))
            line = str_between(line, '\'');
        if(c_strcmp(line, '\'') == 0)
            line = ft_strchr(line, '\'');
        if(c_strrcmp(line, '\'') == 0)
            line = search_and_stop(line, '\'');
        printf("%s\n", line);
        return (0);
    }
    return (1);
}

int    echo_double_quote(char *str)
{
    char *line;

    line = ft_strchr(str, ' ');
    if(ft_strncmp(str, "echo", 4) == 0)
    {
        if ((c_strcmp(line, (char)'"') == 0) && (c_strrcmp(line, (char)'"') == 0))
            line = str_between(line, (char)'"');
        if(c_strcmp(line, (char)'"') == 0)
            line = ft_strchr(line, (char)'"');
        if(c_strrcmp(line, (char)'"') == 0)
            line = search_and_stop(line, (char)'"');
        printf("dans double %s\n", line);
        return (0);
    }
    return (1);
    
}

int    ft_echo_n(char *str)
{
    char *line;
    
    line = ft_strchr_echo(str, 'n');
    if(ft_strncmp(str, "echo -n", 7) == 0)
    {
        // printf("dans ft_echo_n : %s\n", line);
        if(c_strcmp(line, (char)'"') == 0)
            line = str_between(line, (char)'"');
        else if(c_strcmp(line, '\'') == 0)
            line = str_between(line, '\'');
        else if ((c_strcmp(line, (char)'"') == 1 && c_strcmp(line, '\'') == 1))
        {
            printf("%s", line);
            return (0);
        }

        // printf("dans ft_echo_n : %s\n", line);
        printf("%s", line);
        return(0);
    }
    return (1);
}
