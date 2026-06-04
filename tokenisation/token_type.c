#include "../minishell.h"

void    token_pipe(t_token **token, int *i)
{
    t_token *new;

        new = new_token("|", T_PIPE);
        add_token(token, new);
        (*i)++;
}

void    token_redir_in(t_token **token, int *i, char *str)
{
    t_token *new;

    if (str[*i + 1] == '<')
    {
        new = new_token("<<", T_HEREDOC);
        add_token(token, new);
        *i += 2;
    }
    else
    {
        new = new_token("<", T_REDIR_IN);
        add_token(token, new);
        (*i)++;
    }
}

void    token_redir_out(t_token **token, int *i, char *str)
{
    t_token *new;

    if (str[*i + 1] == '>')
    {
        new = new_token(">>", T_APPEND);
        add_token(token, new);
        *i += 2;
    }
    else
    {
        new = new_token(">", T_REDIR_OUT);
        add_token(token, new);
        (*i)++;
    }
}

void    token_word(t_token **token, int *i, char *str)
{
    t_token *new;
    char *word;

    word = find_word(str, *i);
    new = new_token(word, T_WORD);
    add_token(token, new);
    free(word);
    while (str[*i] && str[*i] != ' ' && str[*i] != '|' && str[*i] != '<' && str[*i] != '>')
        (*i)++;
}