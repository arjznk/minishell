#include "minishell.h"

void    redirections(t_exec *exec)
{
    if(found_redir(exec) == 0)
    {
        if(ft_strcmp((*exec->cmd)->args[1], ))
    }
}

int     found_redir(t_exec *exec)
{
    if((*exec->cmd)->outfile)
        return (0);
    return(1);
}
