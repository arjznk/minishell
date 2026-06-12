#include "minishell.h"

t_token    *tokenisation(char *str)
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
    int start;
    
    start = i;
    while (str[i] && str[i] != ' ' && str[i] != '|' && str[i] != '>' && str[i] != '<')
    {
        if (str[i] == '\'')
        {
            i++;
            while (str[i] && str[i] != '\'')
                i++;
        }
        else if (str[i] == '"')
        {
            i++;
            while (str[i] && str[i] != '"')
                i++;
        }
        if (str[i])
            i++;
    }
    return(ft_substr(str, start ,i - start));
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
            tmp = tmp->next_token;
    }
    tmp->next_token = new;
}

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
            {
                printf("Error quotes\n");
                return 1;
            }
        }
        if (str[i] == '"')
        {
            i++;
            while (str[i] && str[i] != '"')
                i++;
            if (!str[i])
            {
                printf("Error quotes\n");
                return 1;
            }
        }
        i++;
    }
    return 0;
}