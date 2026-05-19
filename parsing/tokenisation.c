#include "minishell.h"

void    token_type(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == ' ')
            i++;
        else if (str[i] == '|' || str[i] == '<' || str[i] == '>')
        {
            printf("T_REDIR\n");
            i++;
        }
        else
        {
            printf("T_WORD\n");
            while (str[i] && str[i] != ' ' && str[i] != '|' && str[i] != '<' && str[i] != '>')
                i++;
        }
    }
}


