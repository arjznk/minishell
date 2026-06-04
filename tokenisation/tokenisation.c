#include "minishell.h"

t_token    *token_type(char *str)
{
    int i;
    t_token *token;

    token = NULL;
    i = 0;
    while (str[i])
    {
        if (str[i] == ' ')
            i++;
        else if (str[i] == '|')
            token_pipe(&token, &i);
        else if (str[i] == '<')
            token_redir_in(&token, &i, str);
        else if (str[i] == '>')
            token_redir_out(&token, &i, str);
        else
            token_word(&token, &i, str);
    }
    return (token);
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

char    *find_word(char *str, int i)
{
    char    *dup;
    int start;
    
    start = i;
    while (str[i] && str[i] != ' ' && str[i] != '|' && str[i] != '>' && str[i] != '<')
        i++;
    dup = ft_substr(str, start ,i - start);
    return (dup);
}

void    add_token(t_token **token, t_token *new)
{
    t_token *tmp;

    tmp = *token;
    if (!*token)
    {
        *token = new;
        return ;
    }
    else
    {
        while (tmp->next_token)
        {
            tmp = tmp->next_token;
        }
    }
    tmp->next_token = new;
}
