#include "minishell.h"

// char    *delete_quotes(char *str)
// {
//     int len;
//     char *s;

//     len = ft_strlen(str);
//     if ((str[0] == '"' && str[len - 1] == '"') || (str[0] == '\'' && str[len - 1] == '\''))
//         s = ft_substr(str, 1, len - 2);
//     else
//         s = ft_strdup(str);
//     return(s);
// }

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

char    *expand_and_remove_quotes(char *str, t_exec *exec)
{
    int i;
    int s_quotes;
    int d_quotes;
    char *result;

    i = 0;
    d_quotes = 0;
    s_quotes = 0;
    result = ft_strdup("");

    while (str[i])
    {
        if (str[i] == '\'' && d_quotes == 0)
            s_quotes = !s_quotes;
        else if (str[i] == '"' && s_quotes == 0)
            d_quotes = !d_quotes;
        else if (str[i] == '$' && s_quotes == 0)
            result = expand_var2(str, &i, result, exec);
        else
            result = join_char(result, str[i]);
        i++;
    }
    return(result);
}

char    *join_char(char *result, char c)
{
    char    tmp[2];
    char    *new_result;

    tmp[0] = c;
    tmp[1] = '\0';
    new_result = ft_strjoin(result, tmp);
    free(result);
    return (new_result);
}