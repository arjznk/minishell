#include "minishell.h"

void    cmd_type(char *str)
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

t_token *new_token(char *str, t_token_type type)
{
    t_token *new;

    new = malloc(sizeof(t_token));
    if (!new)
        return (NULL);
    new->str = ft_strdup(str);
    new->type = type;
    new->next_token = NULL;
    return (new);
}

char    *find_word(char *str)
{
    char    *dup;
    int i;
    int start;
    int end;

    i = 0;
    start = i;
    while (str[i] && str[i] != ' ' && str[i] != '|' && str[i] != '>' && str[i] != '<')
        i++;
    end = i;
    dup = ft_substr(str, start, end);
    return (dup);
}

void    add_token(t_token **token, t_token *new)
{
    t_token *tmp;

    tmp = *token;
    if (!*token)
        *token = new;
    else
    {
        while (tmp->next_token)
        {
            tmp = tmp->next_token;
        }
    }
    tmp->next_token = new;
}
