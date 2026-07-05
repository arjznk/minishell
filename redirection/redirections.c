#include "minishell.h"

void    redirections(t_exec *exec)
{
	if((*exec->cmd)->outfile && (*exec->cmd)->append == 1)
	{
		if ((exec->redir_fd = open((*exec->cmd)->outfile, O_CREAT | O_WRONLY | O_APPEND, 0644)) == -1)
		{
			printf("minishell: %s: %s\n", (*exec->cmd)->outfile, strerror(errno));
			exec->status = 127;
			return;
		}
	}
	else if((*exec->cmd)->outfile && (*exec->cmd)->append == 0)
	{
		if ((exec->redir_fd = open((*exec->cmd)->outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644)) == -1)
		{
			printf("minishell: %s: %s\n", (*exec->cmd)->outfile, strerror(errno));
			exec->status = 127;
			return;
		}
	}
}

int     found_redir(t_exec *exec)
{
    if((*exec->cmd)->outfile)
        return (0);
    return(1);
}
