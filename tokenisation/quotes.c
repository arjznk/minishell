#include "minishell.h"

char    *delete_quotes(char *str)
{
    int len;
    char *s;

    len = ft_strlen(str);
    if ((str[0] == '"' && str[len - 1] == '"') || (str[0] == '\'' && str[len - 1] == '\''))
        s = ft_substr(str, 1, len - 2);
    else
        s = ft_strdup(str);
    return(s);
}

int check_quotes(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == '\'')
        {
            i++;
            while (str[i] && str[i] != '\'')
                i++;
            if (!str[i])
                return (printf("Error quotes\n"), 1);
        }
        if (str[i] == '"')
        {
            i++;
            while (str[i] && str[i] != '"')
                i++;
            if (!str[i])
                return (printf("Error quotes\n"), 1);
        }
        i++;
    }
    return 0;
}
