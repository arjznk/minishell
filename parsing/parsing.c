#include "../minishell.h"

void    check_syntax(t_token *token)
{
    t_token *tmp;

    if (!token)
        return;
    tmp = token;
    if (tmp->type == T_PIPE)
        printf("Error\n");
    while (tmp)
    {
        if (tmp->type == T_PIPE && (tmp->next_token == NULL || tmp->next_token->type == T_PIPE))
            printf("Error\n");
        if ((tmp->type == T_REDIR_OUT || tmp->type == T_REDIR_IN || tmp->type == T_APPEND || tmp->type == T_HEREDOC) && (tmp->next_token == NULL ||  tmp->next_token->type != T_WORD))
            printf("Error\n");
        tmp = tmp->next_token;
    }
}
