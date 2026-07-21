#include "../minishell.h"

int	check_syntax(t_token *token, t_exec *exec)
{
	t_token	*tmp;

    if (!token)
        return (1);
    tmp = token;
    if (tmp->type == T_PIPE)
    {
        syntax_error("|", exec);
        return (exec->status = 2, 1);
    }
    while (tmp)
	{
		if (tmp->type == T_PIPE)
		{
			if (tmp->next_token == NULL)
			{
				syntax_error("newline", exec);
				return (1);
			}
			if (tmp->next_token->type == T_PIPE)
			{
				syntax_error("|", exec);
				return (1);
			}
		}
		if (tmp->type == T_REDIR_IN
			|| tmp->type == T_REDIR_OUT
			|| tmp->type == T_APPEND
			|| tmp->type == T_HEREDOC)
		{
			if (tmp->next_token == NULL)
			{
				syntax_error("newline", exec);
				return (1);
			}
			if (tmp->next_token->type != T_WORD)
			{
				syntax_error(tmp->next_token->str, exec);
				return (1);
			}
		}
		tmp = tmp->next_token;
	}
	return (0);
}
