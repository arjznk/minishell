#include "minishell.h"

void    check_syntax(t_token *token)
{
    t_token *tmp;

    tmp = token;
    if (tmp->type == T_PIPE)
        printf("Error");
    while (tmp)
    {
        if (tmp->type == T_PIPE && (tmp->next_token->type == T_PIPE || tmp->next_token == NULL))
            printf("Error");
        if (tmp->type == T_REDIR_OUT && (tmp->next_token->type != T_WORD ||  tmp->next_token == NULL))
            printf("Error");
        tmp = tmp->next_token;
    }
}
