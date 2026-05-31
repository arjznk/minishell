#include "minishell.h"

t_token    *token_type(char *str)
{
    int i;
    t_token *new;
    t_token *token;
    char *word;

    token = NULL;

    i = 0;
    while (str[i])
    {
        if (str[i] == ' ')
            i++;
        else if (str[i] == '|')
        {
            new = new_token("|", T_PIPE);
            add_token(&token, new);
            i++;
        }
        else if (str[i] == '<')
        {
            if (str[i + 1] == '<')
            {
               new = new_token("<<", T_HEREDOC);
               add_token(&token, new);
               i += 2;
            }
            else
            {
                new = new_token("<", T_REDIR_IN);
                add_token(&token, new);
                i++;
            }
        }
        else if (str[i] == '>')
        {
            if (str[i + 1] == '>')
            {
                new = new_token(">>", T_APPEND);
                add_token(&token, new);
                i += 2;
            }
            else
            {
                new = new_token(">", T_REDIR_OUT);
                add_token(&token, new);
                i++;
            }
        }
        else 
        {
            word = find_word(str, i);
            new = new_token(word, T_WORD);
            add_token(&token, new);
            while (str[i] && str[i] != ' ' && str[i] != '|' && str[i] != '<' && str[i] != '>')
                i++;
        }
    }
    return(token);
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

    if (!*token)
    {
        *token = new;
        return;
    }
    tmp = *token;
    while (tmp->next_token)
        tmp = tmp->next_token;
    tmp->next_token = new;
}
