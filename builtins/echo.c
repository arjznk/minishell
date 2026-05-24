#include "minishell.h"

void    ft_echo(char *str)
{
    char *line; 

    line = ft_strchr(str, ' ');
    if(ft_echo_n(str) == 0 || echo_quote(str) == 0)
        return;
    if(ft_strncmp(str, "echo", 4) == 0)
    {
        if(c_strcmp(line, (char)'"') == 0)
        {
            // printf("line dans echo : %s\n", line);
            line = str_between(line, (char)'"');
            // printf("line dans str_between : %s\n", line);
            printf("%s\n", line);
            return;
        }
        else if(c_strcmp(line, '\'') == 0)
            line = str_between(line, '\'');  
        printf("%s\n", line);
    }

}
int    ft_echo_n(char *str)
{
    char *line;

    line = ft_strchr_echo(str, 'n');
    if(ft_strncmp(str, "echo -n", 7) == 0)
    {
        if(c_strcmp(line, (char)'"') == 0)
        {
            line = str_between(line, (char)'"');
            printf("%s", line);
            return (0);
        }
        else if(c_strcmp(line, '\'') == 0)
            line = str_between(line, '\''); 
        printf("%s", line);
        return(0);
    }
    return (1);
}

int     echo_quote(char *str)
{
    char *line;
    char *newline;

    line = ft_strchr(str, ' ');
    if(ft_strncmp(str, "echo", 4) == 0)
    {
        if(c_strrcmp(line, (char)'"') == 0)
        {
            newline = search_and_stop(line, '"');
            printf("%s\n", newline);    
            return (0);
        }
        else if (c_strcmp(line, '\'') == 0)
        {
            newline = search_and_stop(line, '\'');
            printf("%s\n", newline);
            return (0);
        }
    }
    return (1);
}


